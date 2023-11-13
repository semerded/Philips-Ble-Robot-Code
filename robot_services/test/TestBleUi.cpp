#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "infra/util/Function.hpp"
#include "robot_services/BleUi.hpp"
#include "services/ble/test_doubles/GapPeripheralMock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class BleUiTest
    : public testing::Test
{
public:
    testing::StrictMock<services::GapPeripheralMock> subject;
    testing::StrictMock<hal::GpioPinMock> ledRed;
    testing::StrictMock<hal::GpioPinMock> ledGreen;

    infra::Execute construct{ [this]()
        {
            EXPECT_CALL(ledRed, Set(true));
            EXPECT_CALL(ledGreen, Set(false));
        } };
    BleUi ble{ subject, ledRed, ledGreen };
    infra::ExecuteOnDestruction destruct{ [this]()
        {
            EXPECT_CALL(ledRed, Set(false));
            EXPECT_CALL(ledGreen, Set(false));
        } };
};

TEST_F(BleUiTest, initialization_in_standby)
{}
