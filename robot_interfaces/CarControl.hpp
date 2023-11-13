#ifndef ROBOT_INTERFACES_CAR_CONTROL_HPP
#define ROBOT_INTERFACES_CAR_CONTROL_HPP

#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

class CarControl
{
public:
    virtual void SpeedMotorLeft(uint8_t percentage, infra::Function<void()> onDone) = 0;
    virtual void SpeedMotorRight(uint8_t percentage, infra::Function<void()> onDone) = 0;

    virtual void DirectionMotorLeft(Direction direction, infra::Function<void()> onDone) = 0;
    virtual void DirectionMotorRight(Direction direction, infra::Function<void()> onDone) = 0;

    virtual void StopMotors(infra::Function<void()> onDone) = 0;
};

#endif
