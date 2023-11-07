#ifndef SHIFT_REGISTER_DRIVER_HPP
#define SHIFT_REGISTER_DRIVER_HPP

#include"hal/interfaces/Gpio.hpp"

class ShiftRegisterDriver
{
public:
    ShiftRegisterDriver(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn);
    ~ShiftRegisterDriver();

private:
    hal::GpioPin& enable;
    hal::GpioPin& latch;
    hal::GpioPin& clock;
    hal::GpioPin& serialIn;
};

#endif
