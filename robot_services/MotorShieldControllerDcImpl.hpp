#ifndef MOTOR_SHIELD_CONTROLLER_DC_HPP
#define MOTOR_SHIELD_CONTROLLER_DC_HPP

#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_interfaces/PwmDriver.hpp"
#include "robot_interfaces/ShiftRegisterDriver.hpp"
#include <cstdint>

class MotorShieldControllerDcImpl
    : public MotorShieldControllerDc
{
public:
    MotorShieldControllerDc(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4);

    void SetDirection(Motor motor, Direction forwards) override;

    void SetSpeed(Motor motor, uint8_t percentage) override;

private:
    ShiftRegisterDriver& shiftRegister;
    PwmDriver& pwm1;
    PwmDriver& pwm2;
    PwmDriver& pwm3;
    PwmDriver& pwm4;
};

#endif