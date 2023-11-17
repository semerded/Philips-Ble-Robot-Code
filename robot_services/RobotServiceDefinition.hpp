#ifndef ROBOT_SERVICE_ROBOT_SERVICE_DEFINITION_HPP
#define ROBOT_SERVICE_ROBOT_SERVICE_DEFINITION_HPP

#include "services/ble/Gatt.hpp"
#include "robot_interfaces/RobotServiceGattServer.hpp"
#include "services/ble/GattServerCharacteristicImpl.hpp"

class RobotServiceDefinition
{
public:
    static const services::AttAttribute::Uuid128& ServiceUuid();

    static const services::AttAttribute::Uuid128& ControlUuid();
    static const services::AttAttribute::Uuid128& AckUuid();

private:
    static inline const services::AttAttribute::Uuid128 serviceUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x99 } };

    static inline const services::AttAttribute::Uuid128 controlUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9a } };
    static inline const services::AttAttribute::Uuid128 ackUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9f } };
};

class RobotServiceGattServerImpl
    : public RobotServiceGattServer
{
public:
    RobotServiceGattServerImpl();

    services::GattServerService& Service() override;
    services::GattServerCharacteristicUpdate& Control() override;
    services::GattServerCharacteristicUpdate& Ack() override;

private:
    services::GattServerService service{ RobotServiceDefinition::ServiceUuid() };
    services::GattServerCharacteristicImpl control;
    services::GattServerCharacteristicImpl ack;
};

#endif
