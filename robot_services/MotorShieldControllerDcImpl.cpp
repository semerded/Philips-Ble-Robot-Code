#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
    : shiftRegister(shiftRegister)
    , pwm1(pwm1)
    , pwm2(pwm2)
    , pwm3(pwm3)
    , pwm4(pwm4)
{

    // pwm1.SetDutyCycle(0);
    // pwm2.SetDutyCycle(0);
    // pwm3.SetDutyCycle(0);
    // pwm4.SetDutyCycle(0);

}

void MotorShieldControllerDcImpl::MotorConfig(Motor motor, uint8_t MotorIDleft, uint8_t MotorIDright)
{
    std::array<uint8_t, 2>motorDirectionIDs = {MotorIDleft, MotorIDright};
    motorMapping.insert({motor, motorDirectionIDs});

    // [motor1: {2, 3}]
}

std::map<Motor, std::array<uint8_t, 2>> MotorShieldControllerDcImpl::GetMotorMapping()
{
    return motorMapping;
}

void MotorShieldControllerDcImpl::SetDirection(Motor motor, Direction direction)
{
    // int motorNumber = static_cast<uint8_t>(motor);
    std::array<uint8_t, 2>motorIDs = motorMapping.at(motor);


    if (direction == Direction::left)
    {
        motorIDs[0] = 1;
        motorIDs[1] = 0;
    }
    else
    {
        motorIDs[0] = 0;
        motorIDs[1] = 1;
    }
    shiftRegister.EnableOutput();
    shiftRegister.ShiftByte(shiftRegisterByte);
    shiftRegister.DisableOutput();
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
