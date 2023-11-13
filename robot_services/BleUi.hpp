#ifndef BLE_UI_HPP
#define BLE_UI_HPP

#include "hal/interfaces/Gpio.hpp"
#include "infra/util/Observer.hpp"
#include "services/ble/Gap.hpp"

class BleUi
    : public services::GapPeripheralObserver
{
public:
    BleUi(services::GapPeripheral& subject, hal::GpioPin& led);
    void StateChanged(services::GapState state) override;

private:
    hal::GpioPin& led;
};

#endif