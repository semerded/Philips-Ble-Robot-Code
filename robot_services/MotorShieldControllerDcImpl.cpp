#include "robot_services/MotorShieldControllerDcImpl.hpp"

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
: shiftRegister(shiftRegister)
, pwmM1(pwmM1)
, pwmM2(pwmM2)
, pwmM3(pwmM3)
, pwmM4(pwmM4)
{}

void MotorShieldControllerDc::SetDirection()
{

}

void MotorShieldControllerDc::SetSpeed()
{

}