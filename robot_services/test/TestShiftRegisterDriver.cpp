#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "robot_services/ShiftRegisterDriver.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cstdint>

class ShiftRegisterDriverTest
    : public testing::Test
{
public:
    void ExpectSerialDataOnClock(bool bitValue)
    {
        EXPECT_CALL(clock, Set(false));
        EXPECT_CALL(serialIn, Set(bitValue));
        EXPECT_CALL(clock, Set(true));
    }

public:
    testing::StrictMock<hal::GpioPinMock> enable;
    testing::StrictMock<hal::GpioPinMock> latch;
    testing::StrictMock<hal::GpioPinMock> clock;
    testing::StrictMock<hal::GpioPinMock> serialIn;

    ShiftRegisterDriver driver{ enable, latch, clock, serialIn };
};

TEST_F(ShiftRegisterDriverTest, initialization)
{
}

TEST_F(ShiftRegisterDriverTest, EnableOutput)
{
    EXPECT_CALL(enable, Set(true));
    driver.EnableOutput();
}

TEST_F(ShiftRegisterDriverTest, DisableOutput)
{
    EXPECT_CALL(enable, Set(false));
    driver.DisableOutput();
}

TEST_F(ShiftRegisterDriverTest, ShiftByte)
{
    testing::InSequence seq;

    EXPECT_CALL(latch, Set(false));

    static std::vector<bool> data = { false, false, true, true, false, false, false, true };
    for (auto bitValue : data)
        ExpectSerialDataOnClock(bitValue);

    EXPECT_CALL(latch, Set(true));

    driver.ShiftByte(0b00110001);
}

TEST_F(ShiftRegisterDriverTest, ShiftBit)
{
    testing::InSequence seq;

    EXPECT_CALL(latch, Set(false));
    ExpectSerialDataOnClock(true);
    EXPECT_CALL(latch, Set(true));

    driver.ShiftBit(true);
}

