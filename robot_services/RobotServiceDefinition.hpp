#ifndef ROBOT_SERVICE_ROBOT_SERVICE_DEFINITION_HPP
#define ROBOT_SERVICE_ROBOT_SERVICE_DEFINITION_HPP

#include "services/ble/Gatt.hpp"
#include "services/ble/GattServer.hpp"
#include "services/ble/GattServerCharacteristicImpl.hpp"

class RobotServiceDefinition
{
public:
    static const services::AttAttribute::Uuid128& ServiceUuid();

    static const services::AttAttribute::Uuid128& SpeedLeftUuid();
    static const services::AttAttribute::Uuid128& SpeedRightUuid();
    static const services::AttAttribute::Uuid128& DirectionLeftUuid();
    static const services::AttAttribute::Uuid128& DirectionRightUuid();
    static const services::AttAttribute::Uuid128& StopUuid();
    static const services::AttAttribute::Uuid128& AckUuid();

private:
    static inline const services::AttAttribute::Uuid128 serviceUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x99 } };

    static inline const services::AttAttribute::Uuid128 speedLeftUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9a } };
    static inline const services::AttAttribute::Uuid128 speedRightUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9b } };
    static inline const services::AttAttribute::Uuid128 directionLeftUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9c } };
    static inline const services::AttAttribute::Uuid128 directionRightUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9d } };
    static inline const services::AttAttribute::Uuid128 stopUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9e } };
    static inline const services::AttAttribute::Uuid128 ackUuid{ { 0xc9, 0x26, 0x17, 0x65, 0x10, 0x76, 0x41, 0xac, 0x82, 0xd7, 0xa4, 0x54, 0xe8, 0x01, 0xbd, 0x9f } };
};

class RobotServiceGattServer
{
public:
    RobotServiceGattServer();
    services::GattServerService& Service();
    services::GattServerCharacteristicUpdate& SpeedLeft();
    services::GattServerCharacteristicUpdate& SpeedRight();
    services::GattServerCharacteristicUpdate& DirectionLeft();
    services::GattServerCharacteristicUpdate& DirectionRight();
    services::GattServerCharacteristicUpdate& Stop();
    services::GattServerCharacteristicUpdate& Ack();

private:
    services::GattServerService service{ RobotServiceDefinition::ServiceUuid() };
    services::GattServerCharacteristicImpl speedLeft;
    services::GattServerCharacteristicImpl speedRight;
    services::GattServerCharacteristicImpl directionLeft;
    services::GattServerCharacteristicImpl directionRight;
    services::GattServerCharacteristicImpl stop;
    services::GattServerCharacteristicImpl ack;
};

#endif
