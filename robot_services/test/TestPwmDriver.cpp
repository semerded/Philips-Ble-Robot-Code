#include "hal/interfaces/Gpio.hpp"
#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cstdint>

class PwmDriverTest
    : public testing::Test
{
public:
    testing::StrictMock<hal::PinConfigType> config;
    testing::StrictMock<hal::GpioPinMock> pin;

    PwmDriver driver{config, pin};
};

TEST_F(PwmDriverTest, initialization)
{};

TEST_F(PwmDriverTest, SetDutyCycle)
{
    EXPECT_CALL()
}