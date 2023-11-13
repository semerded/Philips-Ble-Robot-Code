#include "robot_services/BleUi.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "services/ble/Gap.hpp"
#include <chrono>

BleUi::BleUi(services::GapPeripheral& subject, hal::GpioPin& ledStandby, hal::GpioPin& ledBleInteraction)
    : services::GapPeripheralObserver(subject)
    , ledStandby(ledStandby)
    , ledBleInteraction(ledBleInteraction)
{
    ledStandby.Set(true);
    ledBleInteraction.Set(false);
}

BleUi::~BleUi()
{
    ledStandby.Set(false);
    ledBleInteraction.Set(false);
}

void BleUi::StateChanged(services::GapState state)
{
    if (state == services::GapState::advertising)
    {
        ledStandby.Set(false);
        bleInteractionTimer.Start(std::chrono::milliseconds(100), [this]()
        {
            static bool ledState = true;
            ledBleInteraction.Set(ledState);
            ledState = !ledState;
        });
    }
}
