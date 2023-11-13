#ifndef ROBOT_INTERFACES_CAR_CONTROL_HPP
#define ROBOT_INTERFACES_CAR_CONTROL_HPP

#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

class CarControl
{
public:
    virtual void speedMotorLeft(uint8_t percentage, infra::Function<void()> onDone) = 0;
    virtual void speedMotorRight(uint8_t percentage, infra::Function<void()> onDone) = 0;

    virtual void directionMotorLeft(Direction direction, infra::Function<void()> onDone) = 0;
    virtual void directionMotorRight(Direction direction, infra::Function<void()> onDone) = 0;

    virtual void stopMotors(infra::Function<void()> onDone) = 0;
};

#endif
