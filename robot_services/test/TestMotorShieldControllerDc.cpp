#include "robot_services/test_doubles/PwmDriverMock.hpp"
#include "robot_services/test_doubles/ShiftRegisterDriverMock.hpp"
#include "robot_services/MotorShieldControllerDcImpl.hpp"
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

    MotorShieldControllerDcImpl controller{ shiftRegister, pwm1, pwm2, pwm3, pwm4 };
};

TEST_F(MotorShieldControllerDcTest, initialization)
{
}

TEST_F(MotorShieldControllerDcTest, EnableController)
{
}

TEST_F(MotorShieldControllerDcTest, SetDirection)
{
    testing::InSequence seq;
    static std::bitset<8> testByte (std::string("10010000"));

    EXPECT_CALL(shiftRegister, ShiftByte(testByte));

    controller.SetDirection(Motor::one, Direction::left);
    controller.SetDirection(Motor::two, Direction::right);

}

TEST_F(MotorShieldControllerDcTest, SetSpeed)
{
    testing::InSequence seq;
    // EXPECT_CALL(pwm1, Set(50));
    controller.SetSpeed(Motor::one, 50);
}