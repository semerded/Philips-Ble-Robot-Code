#include "infra/util/ByteRange.hpp"
#include "infra/util/EnumCast.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/MemoryRange.hpp"
#include "infra/util/test_helper/MockHelpers.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/test_doubles/CarControlMock.hpp"
#include "robot_services/test_doubles/RobotServiceGattServerMock.hpp"
#include "services/ble/GattServer.hpp"
#include "services/ble/test_doubles/GattServerMock.hpp"
#include "gmock/gmock.h"
#include <cstdint>
#include <gtest/gtest.h>

class CarControlToGattCharacteristicTest
    : public testing::Test
{
public:
    void ExpectSendAcknowledge(infra::Function<void()> onDone)
    {
        static uint8_t ok = 0;
        EXPECT_CALL(gattServerCharacteristicUpdateAck, Update(infra::CheckByteRangeContents(infra::MakeRangeFromSingleObject(ok)), testing::_));
        onDone();
    }

public:
    testing::StrictMock<CarControlMock> carControl;
    testing::StrictMock<RobotServiceGattServerMock> robotServiceGattServer;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateSpeedLeft;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateSpeedRight;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateDirectionLeft;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateDirectionRight;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateStop;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateAck;

    infra::Execute construct{ [this]()
        {
            EXPECT_CALL(robotServiceGattServer, SpeedLeft()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateSpeedLeft));
            EXPECT_CALL(robotServiceGattServer, SpeedRight()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateSpeedRight));
            EXPECT_CALL(robotServiceGattServer, DirectionLeft()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateDirectionLeft));
            EXPECT_CALL(robotServiceGattServer, DirectionRight()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateDirectionRight));
            EXPECT_CALL(robotServiceGattServer, Stop()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateStop));
            EXPECT_CALL(robotServiceGattServer, Ack()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateAck));
        } };
    CarControlToGattCharacteristic carControlToGattCharacteristic{ carControl, robotServiceGattServer };
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{}

TEST_F(CarControlToGattCharacteristicTest, speedLeft)
{
    uint8_t percentage = 50;
    EXPECT_CALL(carControl, SpeedMotorLeft(percentage, testing::_)).WillOnce(testing::Invoke([this](uint8_t percentage, infra::Function<void()> onDone)
        {
            ExpectSendAcknowledge(onDone);
        }));
    gattServerCharacteristicUpdateSpeedLeft.NotifyObservers([percentage](auto& observer)
        {
            observer.DataReceived(infra::MakeRangeFromSingleObject(percentage));
        });
}

TEST_F(CarControlToGattCharacteristicTest, speedRight)
{
    uint8_t percentage = 50;
    EXPECT_CALL(carControl, SpeedMotorRight(percentage, testing::_)).WillOnce(testing::Invoke([this](uint8_t percentage, infra::Function<void()> onDone)
        {
            ExpectSendAcknowledge(onDone);
        }));
    gattServerCharacteristicUpdateSpeedRight.NotifyObservers([percentage](auto& observer)
        {
            observer.DataReceived(infra::MakeRangeFromSingleObject(percentage));
        });
}

TEST_F(CarControlToGattCharacteristicTest, directionLeft)
{
    auto direction = Direction::left;
    EXPECT_CALL(carControl, DirectionMotorLeft(direction, testing::_)).WillOnce(testing::Invoke([this](Direction direction, infra::Function<void()> onDone)
        {
            ExpectSendAcknowledge(onDone);
        }));

    auto directionCasted = infra::enum_cast(direction);
    gattServerCharacteristicUpdateDirectionLeft.NotifyObservers([directionCasted](auto& observer)
        {
            observer.DataReceived(infra::MakeRangeFromSingleObject(directionCasted));
        });
}

TEST_F(CarControlToGattCharacteristicTest, directionRight)
{
    auto direction = Direction::right;
    EXPECT_CALL(carControl, DirectionMotorRight(direction, testing::_)).WillOnce(testing::Invoke([this](Direction direction, infra::Function<void()> onDone)
        {
            ExpectSendAcknowledge(onDone);
        }));

    auto directionCasted = infra::enum_cast(direction);
    gattServerCharacteristicUpdateDirectionRight.NotifyObservers([directionCasted](auto& observer)
        {
            observer.DataReceived(infra::MakeRangeFromSingleObject(directionCasted));
        });
}

TEST_F(CarControlToGattCharacteristicTest, stop)
{
    EXPECT_CALL(carControl, StopMotors(testing::_)).WillOnce(testing::Invoke([this](infra::Function<void()> onDone)
        {
            ExpectSendAcknowledge(onDone);
        }));

    auto direction = infra::enum_cast(Direction::stop);
    gattServerCharacteristicUpdateStop.NotifyObservers([direction](auto& observer)
        {
            observer.DataReceived(infra::MakeRangeFromSingleObject(direction));
        });
}
