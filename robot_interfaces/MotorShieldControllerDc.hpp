#ifndef ROBOT_INTERFACES_MOTOR_SHIELD_CONTROLLER_DC_HPP
#define ROBOT_INTERFACES_MOTOR_SHIELD_CONTROLLER_DC_HPP

#include <cstdint>

enum class Direction
{
    left,
    right
};

enum class Motor : uint8_t
{
    one,
    two,
    three,
    four
};

class MotorShieldControllerDc
{
public:
    virtual void SetDirection(Motor motor, Direction direction) = 0;
    virtual void SetSpeed(Motor motor, uint8_t percentage) = 0;
};

#endif
