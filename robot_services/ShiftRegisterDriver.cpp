#include "robot_services/ShiftRegisterDriver.hpp"
#include "ShiftRegisterDriver.hpp"

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

