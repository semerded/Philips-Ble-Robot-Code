#ifndef BASIC_CAR_CONTROLL_HPP
#define BASIC_CAR_CONTROLL_HPP

#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

class BasicCarControl
{
public:
    BasicCarControl(MotorShieldControllerDc& motorShield);
    ~BasicCarControl();

    void speedMotorLeft(uint8_t percentage, infra::Function<void()> onDone);
    void speedMotorRight(uint8_t percentage, infra::Function<void()> onDone);

    void directionMotorLeft(Direction direction, infra::Function<void()> onDone);
    void directionMotorRight(Direction direction, infra::Function<void()> onDone);

    void stopMotors(infra::Function<void()> onDone);

private:
    MotorShieldControllerDc& motorShield;
};

#endif