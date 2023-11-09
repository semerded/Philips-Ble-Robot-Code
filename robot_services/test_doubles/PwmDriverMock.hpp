#ifndef PWM_DRIVER_MOCK_HPP
#define PWM_DRIVER_MOCK_HPP

#include "robot_interfaces/PwmDriver.hpp"
#include "gmock/gmock.h"
#include <cstdint>

class PwmDriverMock
    : public PwmDriver
{
    public:
    MOCK_METHOD(void, SetDutyCycle, (uint8_t dutyCycle));
};

#endif
