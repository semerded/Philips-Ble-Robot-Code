#include "robot_services/MotorShieldControllerDcImpl.hpp"

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
    : shiftRegister(shiftRegister)
    , pwm1(pwm1)
    , pwm2(pwm2)
    , pwm3(pwm3)
    , pwm4(pwm4)
{}

void MotorShieldControllerDcImpl::SetDirection(Motor motor, Direction direction)
{
}

void MotorShieldControllerDcImpl::SetSpeed(Motor motor, uint8_t percentage)
{
}
