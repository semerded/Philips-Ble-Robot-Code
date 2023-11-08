#ifndef PWM_DRIVER_HPP
#define PWM_DRIVER_HPP

#include "hal/interfaces/Gpio.hpp"
#include <cstdint>

class PwmDriver
{
public:
    PwmDriver(hal::PinConfigType config, hal::GpioPin& pin);

    void SetDutyCycle(uint8_t dutyCycle);
};

#endif
