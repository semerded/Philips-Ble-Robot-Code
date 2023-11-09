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

    MotorShieldControllerDcImpl controller{ shiftRegister, pwm1, pwm2, pwm3, pwm4 };
public:
    void ExpectShiftRegister(std::bitset<8> testByte) {
        EXPECT_CALL(shiftRegister, EnableOutput());
        EXPECT_CALL(shiftRegister, ShiftByte(testByte));
        EXPECT_CALL(shiftRegister, DisableOutput());
    }
};

// TEST_F(MotorShieldControllerDcTest, initialization)
// {
//     EXPECT_CALL(pwm1, SetDutyCycle(0));
//     EXPECT_CALL(pwm2, SetDutyCycle(0));
//     EXPECT_CALL(pwm3, SetDutyCycle(0));
//     EXPECT_CALL(pwm4, SetDutyCycle(0));
// }

// TEST_F(MotorShieldControllerDcTest, EnableController)
// {
// }

TEST_F(MotorShieldControllerDcTest, configMotor) 
{
    controller.MotorConfig(Motor::one, 2, 3);
    EXPECT_CALL(obj, call)
}

// TEST_F(MotorShieldControllerDcTest, GetMotorMapping) 
// {
    
// }

TEST_F(MotorShieldControllerDcTest, SetDirection)
{
    testing::InSequence seq;

    std::bitset<8> testByte(0b00000001);
    ExpectShiftRegister(testByte);

    testByte = 0b00000101;
    ExpectShiftRegister(testByte);

    controller.SetDirection(Motor::one, Direction::left);
    controller.SetDirection(Motor::two, Direction::right);
}

TEST_F(MotorShieldControllerDcTest, SetSpeed)
{
    testing::InSequence seq;
    // EXPECT_CALL(pwm1, Set(50));
    controller.SetSpeed(Motor::one, 50);
}
