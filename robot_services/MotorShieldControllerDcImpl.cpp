#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "infra/util/ReallyAssert.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <algorithm>
#include <bitset>
#include <cstdint>

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
    : shiftRegister(shiftRegister)
{
    shiftRegister.ShiftByte(0);
    shiftRegister.EnableOutput();

    motorMapping.insert({ Motor::one, MotorEntry{ pwm1, { 2, 3 } } });
    motorMapping.insert({ Motor::two, MotorEntry{ pwm2, { 1, 4 } } });
    motorMapping.insert({ Motor::three, MotorEntry{ pwm3, { 5, 7 } } });
    motorMapping.insert({ Motor::four, MotorEntry{ pwm4, { 0, 6 } } });

    ResetMotorsSpeed();
}

MotorShieldControllerDcImpl::~MotorShieldControllerDcImpl()
{
    shiftRegister.DisableOutput();
    ResetMotorsSpeed();
}

void MotorShieldControllerDcImpl::SetDirection(Motor motor, Direction direction)
{
    RegisterPosition registerPosition = motorMapping.at(motor).position;

    std::bitset<2> directionSet = static_cast<uint8_t>(direction);
    shiftRegisterByte[registerPosition[0]] = directionSet.test(0);
    shiftRegisterByte[registerPosition[1]] = directionSet.test(1);

    shiftRegister.ShiftByte(shiftRegisterByte);
}

void MotorShieldControllerDcImpl::SetSpeed(Motor motor, uint8_t percentage)
{
    really_assert(percentage == std::clamp<uint8_t>(percentage, 0, 100));
    motorMapping.at(motor).pwm.SetDutyCycle(percentage);
}

void MotorShieldControllerDcImpl::ResetMotorsSpeed()
{
    for (auto& motor : motorMapping)
        motor.second.pwm.SetDutyCycle(0);
}
