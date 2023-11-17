#ifndef ROBOT_INTERFACE_ROBOT_SERVICE_GATT_SERVER_HPP
#define ROBOT_INTERFACE_ROBOT_SERVICE_GATT_SERVER_HPP

#include "services/ble/GattServer.hpp"

class RobotServiceGattServer
{
public:
    virtual services::GattServerService& Service() = 0;
    virtual services::GattServerCharacteristicUpdate& Control() = 0;
    virtual services::GattServerCharacteristicUpdate& Ack() = 0;
};

#endif
