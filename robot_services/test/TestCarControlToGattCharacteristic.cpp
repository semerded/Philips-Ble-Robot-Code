#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/test_doubles/CarControlMock.hpp"
#include "robot_services/test_doubles/RobotServiceGattServerMock.hpp"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

class CarControlToGattCharacteristicTest
: public testing::Test
{
    public:
    testing::StrictMock<CarControlMock> carControl;
    testing::StrictMock<RobotServiceGattServerMock> robotServiceGattServer;

    CarControlToGattCharacteristic converter{ carControl, robotServiceGattServer};
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{}
