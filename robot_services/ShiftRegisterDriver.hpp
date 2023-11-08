#ifndef SHIFT_REGISTER_DRIVER_HPP
#define SHIFT_REGISTER_DRIVER_HPP

#include "hal/interfaces/Gpio.hpp"
#include "infra/util/Function.hpp"
#include <bitset>


class ShiftRegisterDriver
{
public:
    ShiftRegisterDriver(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn);

    void EnableOutput();
    void DisableOutput();

    void ShiftByte(std::bitset<8> byte);

    void ShiftBit(bool bit);

private:
    void SendDataOnClock(bool bit);

    void ShiftOnLatch(infra::Function<void()> onShift);  

private:
    hal::GpioPin& enable;
    hal::GpioPin& latch;
    hal::GpioPin& clock;
    hal::GpioPin& serialIn;
};

#endif
