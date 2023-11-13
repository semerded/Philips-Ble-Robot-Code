#include "infra/util/Function.hpp"
#include "infra/util/MemoryRange.hpp"
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
    testing::StrictMock<CarControlMock> carControl;
    testing::StrictMock<RobotServiceGattServerMock> robotServiceGattServer;
    testing::StrictMock<services::GattServerCharacteristicUpdateMock> gattServerCharacteristicUpdate;

    infra::Execute construct{[this]()
    {
        EXPECT_CALL(robotServiceGattServer, SpeedLeft()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
        EXPECT_CALL(robotServiceGattServer, SpeedRight()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
        EXPECT_CALL(robotServiceGattServer, DirectionLeft()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
        EXPECT_CALL(robotServiceGattServer, DirectionRight()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
        EXPECT_CALL(robotServiceGattServer, Stop()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
        EXPECT_CALL(robotServiceGattServer, Ack()).WillOnce(testing::ReturnRef(gattServerCharacteristicUpdate));
    }};
    CarControlToGattCharacteristic carControlToGattCharacteristic{ carControl, robotServiceGattServer};
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{}


TEST_F(CarControlToGattCharacteristicTest, speedLeft)
{
    uint8_t percentage = 50;
    EXPECT_CALL(carControl, SpeedMotorLeft(percentage, testing::_));
    robotServiceGattServer.SpeedLeft().NotifyObservers([percentage](auto& observer){

        observer.DataReceived(infra::MakeRangeFromSingleObject(percentage) );
    });
}
