#ifndef SHIFT_REGISTER_DRIVER_HPP
#define SHIFT_REGISTER_DRIVER_HPP

#include "hal/interfaces/Gpio.hpp"
#include <bitset>


class ShiftRegisterDriver
{
public:
    ShiftRegisterDriver(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn);
    ~ShiftRegisterDriver();

    void SetData(std::bitset<8> byte);

private:
    hal::GpioPin& enable;
    hal::GpioPin& latch;
    hal::GpioPin& clock;
    hal::GpioPin& serialIn;
};

#endif
