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
#include <sys/types.h>

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
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateControl;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdateAck;

    infra::Execute construct{ [this]()
        {
            EXPECT_CALL(robotServiceGattServer, Control()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateControl));
            EXPECT_CALL(robotServiceGattServer, Ack()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdateAck));
        } };
    CarControlToGattCharacteristic carControlToGattCharacteristic{ carControl, robotServiceGattServer };
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{}

TEST_F(CarControlToGattCharacteristicTest, speedLeft)
{
    static const std::array<uint8_t, 4> data = { 0x01, 0x32, 0x02, 0x20 };
    EXPECT_CALL(carControl, SpeedMotorLeft(0x32, testing::_)).WillOnce(testing::Invoke([this](uint8_t speed, infra::Function<void()> onDone)
        {
            EXPECT_CALL(carControl, SpeedMotorRight(0x20, testing::_)).WillOnce(testing::Invoke([this](uint8_t speed, infra::Function<void()> onDone)
                {
                    EXPECT_CALL(carControl, DirectionMotorLeft(Direction::left, testing::_)).WillOnce(testing::Invoke([this](Direction direction, infra::Function<void()> onDone)
                        {
                            EXPECT_CALL(carControl, DirectionMotorRight(Direction::right, testing::_)).WillOnce(testing::Invoke([this](Direction direction, infra::Function<void()> onDone)
                                {
                                    ExpectSendAcknowledge(onDone);
                                }));
                            onDone();
                        }));
                    onDone();
                }));
            onDone();
        }));

    gattServerCharacteristicUpdateControl.NotifyObservers([](auto& observer)
        {
            observer.DataReceived(infra::MakeConstByteRange(data));
        });
}