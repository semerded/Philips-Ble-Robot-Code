#include "robot_services/ShiftRegisterDriverImpl.hpp"

ShiftRegisterDriverImpl::ShiftRegisterDriverImpl(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn)
    : enable(enable)
    , latch(latch)
    , clock(clock)
    , serialIn(serialIn)
{}

void ShiftRegisterDriverImpl::SendBitOnClock(bool bit)
{
    clock.Set(false);
    serialIn.Set(bit);
    clock.Set(true);
}

void ShiftRegisterDriverImpl::ShiftOnLatch(infra::Function<void()> onShift)
{
    latch.Set(false);
    onShift();
    latch.Set(true);
}

void ShiftRegisterDriverImpl::EnableOutput()
{
    enable.Set(false);
}

void ShiftRegisterDriverImpl::DisableOutput()
{
    enable.Set(true);
}

void ShiftRegisterDriverImpl::ShiftByte(std::bitset<8> byte)
{
    ShiftOnLatch([this, byte]()
        {
            for (auto i = 7; i >= 0; --i)
            {
                auto bit = byte.test(i);
                SendBitOnClock(bit);
            }
        });
}

void ShiftRegisterDriverImpl::ShiftBit(bool bit)
{
    ShiftOnLatch([this, bit]()
        {
            SendBitOnClock(bit);
        });
}
