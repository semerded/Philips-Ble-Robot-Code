#include "robot_services/ShiftRegisterDriver.hpp"

ShiftRegisterDriver::ShiftRegisterDriver(hal::GpioPin& enable, hal::GpioPin& latch, hal::GpioPin& clock, hal::GpioPin& serialIn)
    : enable(enable)
    , latch(latch)
    , clock(clock)
    , serialIn(serialIn)
{
    enable.Set(true);
}

ShiftRegisterDriver::~ShiftRegisterDriver()
{
    enable.Set(false);
}

void ShiftRegisterDriver::SetData(std::bitset<8> byte)
{
    latch.Set(false);
    for (auto i = 7; i >= 0; --i)
    {
        clock.Set(false);

        auto bit = byte.test(i);
        serialIn.Set(bit);

        clock.Set(true);
    }
    latch.Set(true);
}
