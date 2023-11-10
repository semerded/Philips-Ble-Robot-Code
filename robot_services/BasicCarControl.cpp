#include "robot_services/BasicCarControl.hpp"
#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"


BasicCarControl::BasicCarControl(MotorShieldControllerDc& motorShield)
    : motorShield(motorShield)
{}

BasicCarControl::~BasicCarControl()
{}

void BasicCarControl::speedMotorLeft(uint8_t percentage, infra::Function<void()> onDone)
{
    motorShield.SetSpeed(Motor::three, percentage);
    onDone();
}

void BasicCarControl::speedMotorRight(uint8_t percentage, infra::Function<void()> onDone)
{
    motorShield.SetSpeed(Motor::four, percentage);
    onDone();
}

void BasicCarControl::directionMotorLeft(Direction direction, infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::three, Direction::left);
    onDone();
}

void BasicCarControl::directionMotorRight(Direction direction, infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::four, Direction::right);
    onDone();
}

void BasicCarControl::stopMotors(infra::Function<void()> onDone)
{
    motorShield.SetDirection(Motor::three, Direction::stop);
    motorShield.SetDirection(Motor::four, Direction::stop);
    motorShield.SetSpeed(Motor::three, 0);
    motorShield.SetSpeed(Motor::four, 0);
    onDone();
}