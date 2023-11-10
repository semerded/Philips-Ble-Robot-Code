#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_services/BasicCarControl.hpp"
#include "robot_services/test_doubles/MotorShieldControllerMock.hpp"
#include "infra/util/test_helper/MockCallback.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class BasicCarControlTest
    : public testing::Test
{
public:
    testing::StrictMock<MotorShieldControllerDcMock> motorShield;

    BasicCarControl controller{ motorShield };
};

TEST_F(BasicCarControlTest, initialization)
{
}

TEST_F(BasicCarControlTest, speedMotorLeft)
{
    EXPECT_CALL(motorShield, SetSpeed(Motor::three, 50));
    infra::VerifyingFunctionMock<void()> done;
    controller.speedMotorLeft(50, done);
}

TEST_F(BasicCarControlTest, speedMotorRight)
{
    EXPECT_CALL(motorShield, SetSpeed(Motor::four, 50));
    infra::VerifyingFunctionMock<void()> done;
    controller.speedMotorRight(50, done);
}

TEST_F(BasicCarControlTest, directionMotorLeft)
{
    EXPECT_CALL(motorShield, SetDirection(Motor::three, Direction::left));
    infra::VerifyingFunctionMock<void()> done;
    controller.directionMotorLeft(Direction::left, done);
}

TEST_F(BasicCarControlTest, directionMotorRight)
{
    EXPECT_CALL(motorShield, SetDirection(Motor::four, Direction::right));
    infra::VerifyingFunctionMock<void()> done;
    controller.directionMotorRight(Direction::right, done);
}

TEST_F(BasicCarControlTest, stopMotors)
{

    EXPECT_CALL(motorShield, SetDirection(Motor::three, Direction::stop));
    EXPECT_CALL(motorShield, SetDirection(Motor::four, Direction::stop));
    EXPECT_CALL(motorShield, SetSpeed(Motor::three, 0));
    EXPECT_CALL(motorShield, SetSpeed(Motor::four, 0));

    infra::VerifyingFunctionMock<void()> done;
    controller.stopMotors(done);
}
