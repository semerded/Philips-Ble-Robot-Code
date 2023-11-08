#include "robot_services/ShiftRegisterDriver.hpp"

ShiftRegisterDriver::ShiftRegisterDriver(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn)
    : enable(enable)
    , latch(latch)
    , clock(clock)
    , serialIn(serialIn)
{}

void ShiftRegisterDriver::SendDataOnClock(bool bit)
{
    clock.Set(false);
    serialIn.Set(bit);
    clock.Set(true);
}

void ShiftRegisterDriver::ShiftOnLatch(infra::Function<void()> onShift)
{
    latch.Set(false);
    onShift();
    latch.Set(true);
}

void ShiftRegisterDriver::EnableOutput()
{
    enable.Set(false);
}

void ShiftRegisterDriver::DisableOutput()
{
    enable.Set(true);
}

void ShiftRegisterDriver::ShiftByte(std::bitset<8> byte)
{
    ShiftOnLatch([this, byte]()
        {
            for (auto i = 7; i >= 0; --i)
            {
                auto bit = byte.test(i);
                SendDataOnClock(bit);
            }
        });
}

void ShiftRegisterDriver::ShiftBit(bool bit)
{
    ShiftOnLatch([this, bit]()
        {
            SendDataOnClock(bit);
        });
}
