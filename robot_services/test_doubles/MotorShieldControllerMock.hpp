#ifndef MOTOR_SHIELD_CONTROLLER_HPP
#define MOTOR_SHIELD_CONTROLLER_HPP

#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "gmock/gmock.h"
#include <cstdint>

class MotorShieldControllerDcMock
    : public MotorShieldControllerDc
{
    public:
    MOCK_METHOD(void, SetDirection, (Motor motor, Direction direction));
    MOCK_METHOD(void, SetSpeed, (Motor motor, uint8_t percentage));
};

#endif
