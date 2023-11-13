#ifndef ROBOT_INTERFACE_ROBOT_SERVICE_GATT_SERVER_HPP
#define ROBOT_INTERFACE_ROBOT_SERVICE_GATT_SERVER_HPP

#include "services/ble/GattServer.hpp"

class RobotServiceGattServer
{
public:
    virtual services::GattServerService& Service() = 0;
    virtual services::GattServerCharacteristicUpdate& SpeedLeft() = 0;
    virtual services::GattServerCharacteristicUpdate& SpeedRight() = 0;
    virtual services::GattServerCharacteristicUpdate& DirectionLeft() = 0;
    virtual services::GattServerCharacteristicUpdate& DirectionRight() = 0;
    virtual services::GattServerCharacteristicUpdate& Stop() = 0;
    virtual services::GattServerCharacteristicUpdate& Ack() = 0;
};

#endif
