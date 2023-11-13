#include "robot_services/BleUi.hpp"
#include "hal/interfaces/Gpio.hpp"
#include "services/ble/Gap.hpp"

BleUi::BleUi(services::GapPeripheral& subject, hal::GpioPin& led)
    : services::GapPeripheralObserver(subject)
    , led(led)
{
}

void BleUi::StateChanged(services::GapState state)
{
}
