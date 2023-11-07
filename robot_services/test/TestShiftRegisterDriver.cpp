#include "robot_services/ShiftRegisterDriver.hpp"
#include "gtest/gtest.h"
#include <cstdint>
#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "infra/util/Function.hpp"

class ShiftRegisterDriverTest
    : public testing::Test
{
public:
    testing::StrictMock<hal::GpioPinMock> enable;
    testing::StrictMock<hal::GpioPinMock> latch;
    testing::StrictMock<hal::GpioPinMock> clock;
    testing::StrictMock<hal::GpioPinMock> serialIn;

    infra::Execute execute{[this]
    {
        EXPECT_CALL(enable, Set(true));
    }};
    ShiftRegisterDriver driver{enable, latch, clock, serialIn};
    infra::ExecuteOnDestruction dexecute{[this]
    {
        EXPECT_CALL(enable, Set(false));
    }};
};

TEST_F(ShiftRegisterDriverTest, initialization)
{}

TEST_F(ShiftRegisterDriverTest, SetData)
{
    EXPECT_CALL(clock, Set(testing::_)).Times(10).WillRepeatedly(testing::Invoke([](bool value)
        {
            static bool compareator = false;
            EXPECT_EQ(compareator, value);
            compareator != compareator;
        }));
    EXPECT_CALL(latch, Set(false));

    std::array<bool, 8> data = {true, false, false, false, true, true, false, false};
    uint8_t iterator = 0;

    EXPECT_CALL(serialIn, Set(testing::_)).Times(8).WillRepeatedly(testing::Invoke([data, &iterator](bool value)
        {
            EXPECT_EQ(data[iterator], value);
            ++iterator;
        }));

    driver.SetData(0b00110001);
}
