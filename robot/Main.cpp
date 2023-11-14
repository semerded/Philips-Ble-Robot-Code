#include "app_conf.h"
#include "generated/Version.h"
#include "hal/interfaces/Gpio.hpp"
#include "hal/interfaces/MacAddress.hpp"
#include "hal_st/instantiations/NucleoTracerInfrastructure.hpp"
#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/middlewares/ble_middleware/TracingGapPeripheralSt.hpp"
#include "hal_st/middlewares/ble_middleware/TracingGattServerSt.hpp"
#include "hal_st/middlewares/ble_middleware/TracingSystemTransportLayer.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoWB55RG.hpp"
#include "hal_st/stm32fxxx/UniqueDeviceId.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/ByteRange.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/Optional.hpp"
#include "robot/PwmDriverImpl.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_services/BleUi.hpp"
#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "robot_services/RobotServiceDefinition.hpp"
#include "robot_services/ShiftRegisterDriverImpl.hpp"
#include "robot_services/TracingBasicCarControl.hpp"
#include "services/ble/BondStorageSynchronizer.hpp"
#include "services/tracer/GlobalTracer.hpp"
#include "services/util/DebugLed.hpp"
#include <array>
#include <chrono>
#include <sys/_stdint.h>
#include <sys/types.h>

extern "C" void IPCC_C1_RX_IRQHandler(void)
{
    HW_IPCC_Rx_Handler();
}

extern "C" void IPCC_C1_TX_IRQHandler(void)
{
    HW_IPCC_Tx_Handler();
}

void ConfigurePeripheralCommonClock()
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS | RCC_PERIPHCLK_RFWAKEUP;
    PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
    PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
    PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
}

void ConfigureSystemPower()
{
    // Initialize the CPU2 reset value before starting CPU2 with C2BOOT */
    LL_C2_PWR_SetPowerMode(LL_PWR_MODE_SHUTDOWN);
}

void ConfigureSystemAndPeripherals()
{
    // The OPTVERR flag is wrongly set at power on. It shall be cleared before using any HAL_FLASH_xxx() api
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

    ConfigurePeripheralCommonClock();

    // Enable IPCC(36), HSEM(38) wakeup interrupts on CPU1
    LL_EXTI_EnableIT_32_63(LL_EXTI_LINE_36 & LL_EXTI_LINE_38);

    ConfigureSystemPower();
}

hal::MacAddress CreateUniqueMacAddress()
{
    hal::MacAddress address;
    auto uniqueDeviceId = hal::UniqueDeviceId();

    for (int i = 0; i != std::tuple_size<hal::MacAddress>::value - 3; ++i)
        address[i] = uniqueDeviceId[i];

    address[3] = 0xBE;
    address[4] = 0xEE;
    address[5] = 0xEF;

    return address;
}

void PrintModuleInfoBanner(services::Tracer& tracer, const hal::MacAddress& macAddress)
{
    tracer.Trace() << "\r\n--------- BLE MODULE INFO -----------------------"
                   << "\r\nSoftware version  : " << robot::generated::VERSION_FULL
                   << "\r\nBLE Address       : " << infra::AsLittleEndianMacAddress(macAddress)
                   << "\r\n-------------------------------------------------";
}

void AddAdStructure(infra::BoundedVector<uint8_t>& buffer, uint8_t dataType, infra::ConstByteRange data)
{
    buffer.emplace_back(data.size() + 1);
    buffer.emplace_back(dataType);
    buffer.insert(buffer.end(), data.begin(), data.end());
}

class ConfigurationStoreInterfaceStub
    : public services::ConfigurationStoreInterface
{
public:
    uint32_t Write() override
    {
        return 0;
    }

    void Unlocked() override
    {}
};

class BondStorageSynchronizerStub
    : public services::BondStorageSynchronizer
{
public:
    void UpdateBondedDevice(hal::MacAddress address) override
    {}

    void RemoveBond(hal::MacAddress address) override
    {}

    void RemoveAllBonds() override
    {}

    uint32_t GetMaxNumberOfBonds() const override
    {
        return 10;
    }
};

class PwmDriverStub
    : public PwmDriver
{
public:
    void SetDutyCycle(EMIL_MAYBE_UNUSED uint8_t dutyCycle) override
    {}
};

unsigned int hse_value = 32000000;

int main()
{
    HAL_Init();

    ConfigureDefaultClockNucleoWB55RG();
    ConfigureSystemAndPeripherals();

    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();

    static main_::StmEventInfrastructure eventInfrastructure;
    static main_::Nucleo64WBUi ui;
    static services::DebugLed debugLed(ui.ledBlue);
    static bool blinkOn = false;

    static main_::NucleoWb55rgTracerInfrastructure tracer;
    services::SetGlobalTracerInstance(tracer.tracer);

    static auto randomStaticAddress = CreateUniqueMacAddress();
    PrintModuleInfoBanner(tracer.tracer, randomStaticAddress);

    static hal::GpioPinStm latch(hal::Port::A, 6);
    static hal::GpioPinStm clock(hal::Port::C, 10);
    static hal::GpioPinStm serialIn(hal::Port::C, 12);
    static hal::GpioPinStm enable(hal::Port::C, 13);
    static ShiftRegisterDriverImpl shiftRegisterDriver(enable, latch, clock, serialIn);

    static hal::GpioPinStm pwmMotorFourPin(hal::Port::A, 8, hal::Drive::PushPull, hal::Speed::High, hal::WeakPull::Up);
    static hal::PeripheralPinStm pwmMotorFour(pwmMotorFourPin, hal::PinConfigTypeStm::timerChannel1, 1);
    static hal::GpioPinStm pwmMotorThreePin(hal::Port::A, 15, hal::Drive::PushPull, hal::Speed::High, hal::WeakPull::Up);
    static hal::PeripheralPinStm pwmMotorThree(pwmMotorThreePin, hal::PinConfigTypeStm::timerChannel1, 2);
    static PwmDriverStub PwmDriver1;
    static PwmDriverStub PwmDriver2;
    static PwmDriverImpl PwmDriver3(TIM1);
    static PwmDriverImpl PwmDriver4(TIM2);

    static MotorShieldControllerDcImpl motorShieldControllerDc(shiftRegisterDriver, PwmDriver1, PwmDriver2, PwmDriver3, PwmDriver4);
    static TracingBasicCarControl carControl(motorShieldControllerDc, tracer.tracer);

    tracer.tracer.Trace() << "motors ready for use";

    static ConfigurationStoreInterfaceStub configurationStore;
    static std::array<uint8_t, 2028> flashStorage = {};
    static infra::ByteRange flashRange{ flashStorage };
    static auto flashStorageAccess = services::ConfigurationStoreAccess<infra::ByteRange>{ configurationStore, flashRange };

    static infra::BoundedConstString::WithStorage<9> deviceName = "ble-robot";
    static hal::GapPeripheralSt::GapService gapService{ deviceName, 0 };
    static hal::GapPeripheralSt::RootKeys rootKeys;
    rootKeys.identity = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 };
    rootKeys.encryption = { 0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21, 0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21 };
    static BondStorageSynchronizerStub bondStorageSynchronizer;
    static infra::Creator<services::BondStorageSynchronizer, BondStorageSynchronizerStub, void()> bondStorageSynchronizerCreator;

    static infra::BoundedVector<uint8_t>::WithMaxSize<services::GapPeripheral::maxAdvertisementDataSize> advertisementData = {};
    static const auto flags = infra::enum_cast(services::GapPeripheral::AdvertisementFlags::brEdrNotSupported | services::GapPeripheral::AdvertisementFlags::leGeneralDiscoverableMode);
    AddAdStructure(advertisementData, infra::enum_cast(services::GapAdvertisementDataType::flags), infra::MakeConstByteRange(flags));
    AddAdStructure(advertisementData, infra::enum_cast(services::GapAdvertisementDataType::completeLocalName), infra::MakeConstByteRange(deviceName.Storage()));

    static infra::BoundedVector<uint8_t>::WithMaxSize<services::GapPeripheral::maxScanResponseDataSize> scanResponseData = {};
    AddAdStructure(scanResponseData, infra::enum_cast(services::GapAdvertisementDataType::publicTargetAddress), infra::MakeConstByteRange(randomStaticAddress));

    static RobotServiceGattServerImpl RobotServiceGattServerImpl;

    static infra::Optional<hal::TracingGapPeripheralSt> gapPeripheralSt;
    static infra::Optional<services::GapPeripheralDecorator> gapPeripheralDecorator;
    static infra::Optional<hal::TracingGattServerSt> tracingGattServerSt;
    static infra::Optional<BleUi> bleUi;
    static infra::Optional<CarControlToGattCharacteristic> carControlToGattCharacteristic;

    static hal::TracingSystemTransportLayer tracingSystemTransportLayer(
        flashStorageAccess, [](uint32_t* bondStorageAddress)
        {
            gapPeripheralSt.Emplace(tracingSystemTransportLayer, randomStaticAddress, rootKeys, 23, 0x18, gapService, bondStorageSynchronizerCreator, bondStorageAddress, tracer.tracer);
            gapPeripheralDecorator.Emplace(*gapPeripheralSt);
            gapPeripheralDecorator->SetAdvertisementData(advertisementData.range());
            gapPeripheralDecorator->SetScanResponseData(scanResponseData.range());

            tracingGattServerSt.Emplace(tracingSystemTransportLayer, tracer.tracer);
            tracingGattServerSt->AddService(RobotServiceGattServerImpl.Service());

            bleUi.Emplace(*gapPeripheralSt, ui.ledRed, ui.ledGreen);
            carControlToGattCharacteristic.Emplace(carControl, RobotServiceGattServerImpl);
        },
        tracer.tracer);

    ui.buttonOne.Config(hal::PinConfigType::input);
    ui.buttonOne.EnableInterrupt([]()
        {
            tracer.tracer.Trace() << "BU1: pressed";
            tracer.tracer.Trace() << "started advertising";

            gapPeripheralDecorator->Advertise(services::GapAdvertisementType::advInd, 0x200u);
        },
        hal::InterruptTrigger::fallingEdge);

    ui.buttonTwo.Config(hal::PinConfigType::input);
    ui.buttonTwo.EnableInterrupt([]()
        {
            gapPeripheralDecorator->Standby();
            tracer.tracer.Trace() << "stopped advertising";
        },
        hal::InterruptTrigger::fallingEdge);

    ui.buttonThree.Config(hal::PinConfigType::input);
    ui.buttonThree.EnableInterrupt([]()
        {
            tracer.tracer.Trace() << "BU3: test";
            static auto stepIterator = 0;
            static infra::TimerRepeating testTimer;

            testTimer.Start(std::chrono::seconds(1), []()
                {
                    if (stepIterator == 0)
                        carControl.SpeedMotorLeft(50, infra::emptyFunction);
                    else if (stepIterator == 1)
                        carControl.SpeedMotorRight(50, infra::emptyFunction);
                    else if (stepIterator == 2)
                        carControl.DirectionMotorLeft(Direction::left, infra::emptyFunction);
                    else if (stepIterator == 3)
                        carControl.DirectionMotorLeft(Direction::right, infra::emptyFunction);
                    else if (stepIterator == 4)
                        carControl.DirectionMotorLeft(Direction::stop, infra::emptyFunction);
                    else if (stepIterator == 5)
                        carControl.DirectionMotorRight(Direction::left, infra::emptyFunction);
                    else if (stepIterator == 6)
                        carControl.DirectionMotorRight(Direction::right, infra::emptyFunction);
                    else if (stepIterator == 7)
                        carControl.DirectionMotorRight(Direction::stop, infra::emptyFunction);
                    else if (stepIterator == 8)
                        carControl.StopMotors(infra::emptyFunction);
                    else
                    {
                        testTimer.Cancel();
                        stepIterator = 0;
                        return;
                    }

                    ++stepIterator;
                });
        },
        hal::InterruptTrigger::fallingEdge);

    eventInfrastructure.Run();
    __builtin_unreachable();
}
