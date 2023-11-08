#ifndef MOTOR_SHIELD_CONTROLLER_DC_HPP
#define MOTOR_SHIELD_CONTROLLER_DC_HPP

#include "robot_services/PwmDriver.hpp"
#include "robot_services/ShiftRegisterDriver.hpp"
#include <cstdint>
class MotorShieldControllerDc
{
    MotorShieldControllerDc(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm);

    void SetDirection(uint8_t motor, bool forwards);

    void SetSpeed(uint8_t motor, uint8_t percentage);
};

#endif