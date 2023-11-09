#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_services/test_doubles/PwmDriverMock.hpp"
#include "robot_services/test_doubles/ShiftRegisterDriverMock.hpp"
#include "gmock/gmock.h"
#include <cstdint>
#include <gtest/gtest.h>

class MotorShieldControllerDcTest
    : public testing::Test
{
    testing::StrictMock<ShiftRegisterDriverMock> shiftRegister;
    testing::StrictMock<PwmDriverMock> pwmM1;
    testing::StrictMock<PwmDriverMock> pwmM2;
    testing::StrictMock<PwmDriverMock> pwmM3;
    testing::StrictMock<PwmDriverMock> pwmM4;

    MotorShieldControllerDc controller{shiftRegister, pwmM1, pwmM2, pwmM3, pwmM4};
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
    EXPECT_CALL(Direction)
}

TEST_F(MotorShieldControllerDcTest, SetSpeed)
{
    testing::InSequence seq;
}