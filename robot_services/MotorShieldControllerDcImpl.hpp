#ifndef ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP
#define ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP

#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_interfaces/PwmDriver.hpp"
#include "robot_interfaces/ShiftRegisterDriver.hpp"
#include <cstdint>

class MotorShieldControllerDcImpl
    : public MotorShieldControllerDc
{
public:
    MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4);

    // Implementation of MotorShieldControllerDc
    void SetDirection(Motor motor, Direction direction) override;
    void SetSpeed(Motor motor, uint8_t percentage) override;

private:
    ShiftRegisterDriver& shiftRegister;
    PwmDriver& pwm1;
    PwmDriver& pwm2;
    PwmDriver& pwm3;
    PwmDriver& pwm4;

    std::bitset<8> shiftRegisterByte;
};

#endif