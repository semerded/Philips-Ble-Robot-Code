#include "robot_services/BasicCarControl.hpp"
#include "infra/util/EnumCast.hpp"
#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"


BasicCarControl::BasicCarControl(MotorShieldControllerDc& motorShield)
    : motorShield(motorShield)
{}

BasicCarControl::~BasicCarControl()
{}

void BasicCarControl::SpeedMotorLeft(uint8_t percentage, infra::Function<void()> onDone)
{
    motorShield.SetSpeed(Motor::three, percentage);
    onDone();
}

void BasicCarControl::SpeedMotorRight(uint8_t percentage, infra::Function<void()> onDone)
{
    motorShield.SetSpeed(Motor::four, percentage);
    onDone();
}

void BasicCarControl::DirectionMotorLeft(Direction direction, infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::three, direction);
    onDone();
}

void BasicCarControl::DirectionMotorRight(Direction direction, infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::four, direction);
    onDone();
}

void BasicCarControl::StopMotors(infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::three, Direction::stop);
    motorShield.SetDirection(Motor::four, Direction::stop);
    motorShield.SetSpeed(Motor::three, 0);
    motorShield.SetSpeed(Motor::four, 0);
    onDone();
}