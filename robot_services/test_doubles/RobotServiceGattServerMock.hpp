#ifndef ROBOT_SERVICES_ROBOT_SERVICE_GATT_SERVER_MOCK_HPP
#define ROBOT_SERVICES_ROBOT_SERVICE_GATT_SERVER_MOCK_HPP

#include "robot_interfaces/RobotServiceGattServer.hpp"
#include "gmock/gmock.h"

class RobotServiceGattServerMock
    : public RobotServiceGattServer
{
public:
    MOCK_METHOD(services::GattServerService&, Service, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, SpeedLeft, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, SpeedRight, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, DirectionLeft, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, DirectionRight, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, Stop, ());
    MOCK_METHOD(services::GattServerCharacteristicUpdate&, Ack, ());
};

#endif
