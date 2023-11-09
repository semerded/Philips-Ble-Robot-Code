#include "infra/util/Function.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_services/MotorShieldControllerDcImpl.hpp"
#include "robot_services/test_doubles/PwmDriverMock.hpp"
#include "robot_services/test_doubles/ShiftRegisterDriverMock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <bitset>
#include <cstdint>

class MotorShieldControllerDcTest
    : public testing::Test
{
public:
    testing::StrictMock<ShiftRegisterDriverMock> shiftRegister;
    testing::StrictMock<PwmDriverMock> pwm1;
    testing::StrictMock<PwmDriverMock> pwm2;
    testing::StrictMock<PwmDriverMock> pwm3;
    testing::StrictMock<PwmDriverMock> pwm4;

    infra::Execute construct{ [this]()
        {
            EXPECT_CALL(shiftRegister, ShiftByte(std::bitset<8>{0}));
            EXPECT_CALL(shiftRegister, EnableOutput());
            EXPECT_CALL(pwm1, SetDutyCycle(0));
            EXPECT_CALL(pwm2, SetDutyCycle(0));
            EXPECT_CALL(pwm3, SetDutyCycle(0));
            EXPECT_CALL(pwm4, SetDutyCycle(0));
        } };
    MotorShieldControllerDcImpl controller{ shiftRegister, pwm1, pwm2, pwm3, pwm4 };
    infra::ExecuteOnDestruction destruct{ [this]()
        {
            EXPECT_CALL(shiftRegister, DisableOutput());
            EXPECT_CALL(pwm1, SetDutyCycle(0));
            EXPECT_CALL(pwm2, SetDutyCycle(0));
            EXPECT_CALL(pwm3, SetDutyCycle(0));
            EXPECT_CALL(pwm4, SetDutyCycle(0));
        } };
};

TEST_F(MotorShieldControllerDcTest, initialization)
{
}

TEST_F(MotorShieldControllerDcTest, SetDirection)
{
    testing::InSequence seq;

    std::bitset<8> testByte(0b00000100);

    EXPECT_CALL(shiftRegister, ShiftByte(testByte));
    controller.SetDirection(Motor::one, Direction::left);

    testByte = 0b00010100;
    EXPECT_CALL(shiftRegister, ShiftByte(testByte));
    controller.SetDirection(Motor::two, Direction::right);

    testByte = 0b00011000;
    EXPECT_CALL(shiftRegister, ShiftByte(testByte));
    controller.SetDirection(Motor::one, Direction::right);
}

TEST_F(MotorShieldControllerDcTest, SetSpeed)
{
    EXPECT_CALL(pwm1, SetDutyCycle(25));
    controller.SetSpeed(Motor::one, 25);

    EXPECT_CALL(pwm2, SetDutyCycle(50));
    controller.SetSpeed(Motor::two, 50);

    EXPECT_CALL(pwm3, SetDutyCycle(75));
    controller.SetSpeed(Motor::three, 75);

    EXPECT_CALL(pwm4, SetDutyCycle(100));
    controller.SetSpeed(Motor::four, 100);
}
