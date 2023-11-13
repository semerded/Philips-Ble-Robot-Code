#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/test_doubles/CarControlMock.hpp"
#include "services/ble/test_doubles/GattMock.hpp"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

class CarControlToGattCharacteristicTest
: public testing::Test
{
    public:
    testing::StrictMock<CarControlMock> carControl;
    testing::StrictMock<services::GattServerMock> robotService;

    CarControlToGattCharacteristic converter{ carControl, robotService};
};

TEST_F(CarControlToGattCharacteristicTest, initialization)
{
    
}

TEST_F(CarControlToGattCharacteristicTest, converter)
{
    
}

TEST_F(CarControlToGattCharacteristicTest, placeholder)
{
    
}

