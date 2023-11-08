#include "robot_services/MotorShieldControllerDc.hpp"
#include "robot_services/PwmDriver.hpp"
#include "robot_services/ShiftRegisterDriver.hpp"

MotorShieldControllerDc::MotorShieldControllerDc(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm)
: shiftRegister(shiftRegister)
, pwm(pwm)
{}

void MotorShieldControllerDc::SetDirection() 
{

}

void MotorShieldControllerDc::SetSpeed() 
{

}