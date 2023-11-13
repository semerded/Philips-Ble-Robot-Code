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

    void SpeedMotorLeft(uint8_t percentage, infra::Function<void()> onDone) override;
    void SpeedMotorRight(uint8_t percentage, infra::Function<void()> onDone) override;
    void DirectionMotorLeft(Direction direction, infra::Function<void()> onDone) override;
    void DirectionMotorRight(Direction direction, infra::Function<void()> onDone) override;
    void StopMotors(infra::Function<void()> onDone) override;

private:
    MotorShieldControllerDc& motorShield;
};

#endif