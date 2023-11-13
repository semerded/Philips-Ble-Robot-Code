#include "hal/interfaces/test_doubles/GpioMock.hpp"
#include "infra/timer/test_helper/ClockFixture.hpp"
#include "infra/util/Function.hpp"
#include "robot_services/BleUi.hpp"
#include "services/ble/Gap.hpp"
#include "services/ble/test_doubles/GapPeripheralMock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <chrono>


class BleUiTest
    : public testing::Test
    , public infra::ClockFixture
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

TEST_F(BleUiTest, go_to_state_advertising)
{
    EXPECT_CALL(ledRed, Set(false));

    subject.NotifyObservers([](auto& observer)
        {
            observer.StateChanged(services::GapState::advertising);
        });

    EXPECT_CALL(ledGreen, Set(testing::_)).Times(2).WillRepeatedly(testing::Invoke([](bool ledOn)
        {
            static bool current = true;
            EXPECT_EQ(current, ledOn);
            current = !current;
        }));

    ForwardTime(std::chrono::milliseconds(200));
}

TEST_F(BleUiTest, go_to_state_connected)
{
    EXPECT_CALL(ledRed, Set(false));
    EXPECT_CALL(ledGreen, Set(true));

    subject.NotifyObservers([](auto& observer)
        {
            observer.StateChanged(services::GapState::connected);
        });
}

TEST_F(BleUiTest, go_to_state_standby)
{
    EXPECT_CALL(ledRed, Set(true));
    EXPECT_CALL(ledGreen, Set(false));

    subject.NotifyObservers([](auto& observer)
        {
            observer.StateChanged(services::GapState::standby);
        });
}
