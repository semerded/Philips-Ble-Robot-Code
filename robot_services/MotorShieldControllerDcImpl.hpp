#ifndef ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP
#define ROBOT_SERVICES_MOTOR_SHIELD_CONTROLLER_DC_IMPL_HPP

#include "infra/util/BoundedVector.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_interfaces/PwmDriver.hpp"
#include "robot_interfaces/ShiftRegisterDriver.hpp"

class MotorShieldControllerDcImpl
    : public MotorShieldControllerDc
{
public:
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
        MotorEntry(PwmDriver& pwm, uint8_t positionA, uint8_t positionB)
            : pwm(pwm)
            , positionA(positionA)
            , positionB(positionB)
        {}

        PwmDriver& pwm;
        uint8_t positionA;
        uint8_t positionB;
    };

    ShiftRegisterDriver& shiftRegister;

    std::bitset<8> shiftRegisterByte;
    infra::BoundedVector<MotorEntry>::WithMaxSize<4> motorMapping;
};

#endif
