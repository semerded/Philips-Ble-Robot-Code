#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "robot_services/BleUi.hpp"
#include "services/ble/Gap.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class BleUiTest
: public testing::Test
{
    public:
        testing::StricktMock<services::GapPeripheral> subject;
        testing::StricktMock<hal::GpioPinMock> led;

    BleUi ble{subject, led};
};

TEST_F(BleUiTest, )
{

}