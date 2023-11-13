#ifndef BASIC_CAR_CONTROLL_HPP
#define BASIC_CAR_CONTROLL_HPP

#include "infra/util/Function.hpp"
#include "robot_interfaces/CarControl.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

class BasicCarControl
    : public CarControl
{
public:
    BasicCarControl(MotorShieldControllerDc& motorShield);
    ~BasicCarControl();

    void speedMotorLeft(uint8_t percentage, infra::Function<void()> onDone) override;
    void speedMotorRight(uint8_t percentage, infra::Function<void()> onDone) override;

    void directionMotorLeft(Direction direction, infra::Function<void()> onDone) override;
    void directionMotorRight(Direction direction, infra::Function<void()> onDone) override;

    void stopMotors(infra::Function<void()> onDone) override;

private:
    MotorShieldControllerDc& motorShield;
};

#endif