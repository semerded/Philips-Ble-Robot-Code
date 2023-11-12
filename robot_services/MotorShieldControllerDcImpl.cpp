#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "infra/util/ReallyAssert.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "infra/util/EnumCast.hpp"
#include <algorithm>
#include <bitset>
#include <cstdint>

MotorShieldControllerDcImpl::MotorShieldControllerDcImpl(ShiftRegisterDriver& shiftRegister, PwmDriver& pwm1, PwmDriver& pwm2, PwmDriver& pwm3, PwmDriver& pwm4)
    : shiftRegister(shiftRegister)
{
    shiftRegister.ShiftByte(0);
    shiftRegister.EnableOutput();

    motorMapping.emplace_back( pwm1, 2, 3 );
    motorMapping.emplace_back( pwm2, 1, 4 );
    motorMapping.emplace_back( pwm3, 5, 7 );
    motorMapping.emplace_back( pwm4, 0, 6 );

    ResetMotorsSpeed();
}

MotorShieldControllerDcImpl::~MotorShieldControllerDcImpl()
{
    shiftRegister.DisableOutput();
    ResetMotorsSpeed();
}

void MotorShieldControllerDcImpl::SetDirection(Motor motor, Direction direction)
{
    auto motorEntry = motorMapping[infra::enum_cast(motor)];

    std::bitset<2> directionSet = infra::enum_cast(direction);
    shiftRegisterByte[motorEntry.positionA] = directionSet.test(0);
    shiftRegisterByte[motorEntry.positionB] = directionSet.test(1);

    shiftRegister.ShiftByte(shiftRegisterByte);
}

void MotorShieldControllerDcImpl::SetSpeed(Motor motor, uint8_t percentage)
{
    really_assert(percentage == std::clamp<uint8_t>(percentage, 0, 100));
    motorMapping[infra::enum_cast(motor)].pwm.SetDutyCycle(percentage);
}

void MotorShieldControllerDcImpl::ResetMotorsSpeed()
{
    for (auto& motor : motorMapping)
        motor.pwm.SetDutyCycle(0);
}
