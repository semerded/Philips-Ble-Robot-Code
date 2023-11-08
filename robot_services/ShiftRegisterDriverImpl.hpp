#ifndef SHIFT_REGISTER_DRIVER_HPP
#define SHIFT_REGISTER_DRIVER_HPP

#include "hal/interfaces/Gpio.hpp"
#include "infra/util/Function.hpp"
#include "robot_interfaces/ShiftRegisterDriver.hpp"

class ShiftRegisterDriverImpl
    : public ShiftRegisterDriver
{
public:
    ShiftRegisterDriverImpl(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn);

    // Implements ShiftRegisterDriver
    void EnableOutput() override;
    void DisableOutput() override;
    void ShiftByte(std::bitset<8> byte) override;
    void ShiftBit(bool bit) override;

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
