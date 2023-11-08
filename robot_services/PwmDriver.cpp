#include "robot_services/PwmDriver.hpp"
#include "hal/interfaces/Gpio.hpp"
#include <cstdint>

PwmDriver::PwmDriver(hal::PinConfigType config, hal::GpioPin& pin)
    : config(config)
    , pin(pin)
{}

void PwmDriver::SetDutyCycle(uint8_t dutyCycle)
{
    
}
