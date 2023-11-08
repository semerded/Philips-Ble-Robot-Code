
#include "robot_services/PwmDriver.hpp"
#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "robot_services/ShiftRegisterDriver.hpp"
#include "gmock/gmock.h"
#include <cstdint>
#include <gtest/gtest.h>

class MotorShieldControllerDCTest
    : public testing::Test
{
    testing::StrictMock<ShiftRegisterDriver> shiftRegister;
    testing::StrictMock<PwmDriver> pwm;

    MotorShieldControllerDC controller{shiftRegister, pwm};

};