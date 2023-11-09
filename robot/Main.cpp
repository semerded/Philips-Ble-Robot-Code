#include "hal_st/instantiations/NucleoTracerInfrastructure.hpp"
#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoWB55RG.hpp"
#include "services/util/DebugLed.hpp"
#include "robot_services/ShiftRegisterDriver.hpp"
#include "robot/PwmDriver.hpp"

unsigned int hse_value = 32000000;

int main()
{
    HAL_Init();

    // Configure your clock here
    ConfigureDefaultClockNucleoWB55RG();

    static main_::StmEventInfrastructure eventInfrastructure;
    static main_::Nucleo64WBUi ui;
    static services::DebugLed debugLed(ui.ledBlue);

    static main_::NucleoWb55rgTracerInfrastructure tracer;

    tracer.tracer.Trace() << "hello world!";

    static hal::GpioPinStm latch(hal::Port::A, 6);
    static hal::GpioPinStm clock(hal::Port::C, 10);
    static hal::GpioPinStm serialIn(hal::Port::C, 12);
    static hal::GpioPinStm enable(hal::Port::C, 13);

    static ShiftRegisterDriver shiftRegisterDriver(enable, latch, clock, serialIn);

    shiftRegisterDriver.ShiftByte(0b11'00'00'00);
    shiftRegisterDriver.EnableOutput();

    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();

    static hal::GpioPinStm pwmMotorFourPin(hal::Port::A, 8, hal::Drive::PushPull, hal::Speed::High, hal::WeakPull::Up);
    static hal::PeripheralPinStm pwmMotorFour(pwmMotorFourPin, hal::PinConfigTypeStm::timerChannel1, 1);
    static hal::GpioPinStm pwmMotorThreePin(hal::Port::A, 15, hal::Drive::PushPull, hal::Speed::High, hal::WeakPull::Up);
    static hal::PeripheralPinStm pwmMotorThree(pwmMotorThreePin, hal::PinConfigTypeStm::timerChannel1, 2);

    static PwmDriver PwmDriver1(TIM1);
    static PwmDriver PwmDriver2(TIM2);

    PwmDriver1.SetDutyCycle(0);
    PwmDriver2.SetDutyCycle(0);

    ui.buttonOne.Config(hal::PinConfigType::input);
    ui.buttonOne.EnableInterrupt([]()
        {
            tracer.tracer.Trace() << "BU1: pressed";
            PwmDriver1.SetDutyCycle(50);
        },
        hal::InterruptTrigger::fallingEdge);

    ui.buttonTwo.Config(hal::PinConfigType::input);
    ui.buttonTwo.EnableInterrupt([]()
        {
            tracer.tracer.Trace() << "BU2: pressed";
            PwmDriver2.SetDutyCycle(50);
        },
        hal::InterruptTrigger::fallingEdge);

    eventInfrastructure.Run();
    __builtin_unreachable();
}
