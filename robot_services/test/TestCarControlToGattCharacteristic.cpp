#include "infra/util/Function.hpp"
#include "infra/util/MemoryRange.hpp"
#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/test_doubles/CarControlMock.hpp"
#include "robot_services/test_doubles/RobotServiceGattServerMock.hpp"
#include "gmock/gmock.h"
#include <cstdint>
#include <gtest/gtest.h>

class CarControlToGattCharacteristicTest
: public testing::Test
{
    public:
    testing::StrictMock<CarControlMock> carControl;
    testing::StrictMock<RobotServiceGattServerMock> robotServiceGattServer;

    CarControlToGattCharacteristic carControlToGattCharacteristic{ carControl, robotServiceGattServer};
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{}


TEST_F(CarControlToGattCharacteristicTest, speedLeft) 
{
    uint8_t percentage = 50;
    EXPECT_CALL(carControl, speedMotorLeft(percentage, testing::_));
    robotServiceGattServer.SpeedLeft().NotifyObservers([percentage](auto& observer){

        observer.DataReceived(infra::MakeRangeFromSingleObject(percentage) );
    });
}
