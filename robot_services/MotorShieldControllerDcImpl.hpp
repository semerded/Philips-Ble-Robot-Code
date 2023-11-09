#ifndef ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP
#define ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP

#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_interfaces/PwmDriver.hpp"
#include "robot_interfaces/ShiftRegisterDriver.hpp"
#include <array>
#include <cstdint>
#include <map>
#include <sys/types.h>
#include <vector>

class MotorShieldControllerDcImpl
    : public MotorShieldControllerDc
{
public:
    using RegisterPosition = std::array<uint8_t, 2>;

    MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4);
    ~MotorShieldControllerDcImpl();

    // Implementation of MotorShieldControllerDc
    void SetDirection(Motor motor, Direction direction) override;
    void SetSpeed(Motor motor, uint8_t percentage) override;

private:
    void ResetMotorsSpeed();

private:
    struct MotorEntry
    {
        PwmDriver& pwm;
        RegisterPosition position;
    };

    ShiftRegisterDriver& shiftRegister;

    std::bitset<8> shiftRegisterByte;
    std::map<Motor, MotorEntry> motorMapping;
};

#endif
