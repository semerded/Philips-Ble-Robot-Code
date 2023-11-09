#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string>

namespace
{
    static std::bitset<8> shiftRegisterByte;
}

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
    : shiftRegister(shiftRegister)
    , pwm1(pwm1)
    , pwm2(pwm2)
    , pwm3(pwm3)
    , pwm4(pwm4)
{

    pwm1.SetDutyCycle(0);
    pwm2.SetDutyCycle(0);
    pwm3.SetDutyCycle(0);
    pwm4.SetDutyCycle(0);
}

void MotorShieldControllerDcImpl::SetDirection(Motor motor, Direction direction)
{
    int motorNumber = --*(int*)motor;

    if (direction == Direction::left)
    {
        shiftRegisterByte[motorNumber] = 1;
        shiftRegisterByte[motorNumber + 1] = 0;
    }
    else
    {
        shiftRegisterByte[motorNumber] = 0;
        shiftRegisterByte[motorNumber + 1] = 1;
    }
    shiftRegister.EnableOutput();
    shiftRegister.ShiftByte(shiftRegisterByte);
}

void MotorShieldControllerDcImpl::SetSpeed(Motor motor, uint8_t percentage)
{
    switch (motor)
    {
        case Motor::one:
            pwm1.SetDutyCycle(percentage);
            break;

        case Motor::two:
            pwm2.SetDutyCycle(percentage);
            break;

        case Motor::three:
            pwm3.SetDutyCycle(percentage);
            break;

        case Motor::four:
            pwm4.SetDutyCycle(percentage);
            break;
    }
}
