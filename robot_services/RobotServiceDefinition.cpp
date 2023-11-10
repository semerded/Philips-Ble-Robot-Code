#include "robot_services/RobotServiceDefinition.hpp"

namespace
{
    constexpr auto maxPacketSize = 23 - 3; // Optimization as found in ST document AN5289 Rev 7 (Section 7.6.9 How to maximize data throughput).
    constexpr auto permissionFlags = services::GattServerCharacteristic::PermissionFlags::encryptedWrite;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::ServiceUuid()
{
    return serviceUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::SpeedLeftUuid()
{
    return speedLeftUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::SpeedRightUuid()
{
    return speedRightUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::DirectionLeftUuid()
{
    return directionLeftUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::DirectionRightUuid()
{
    return directionRightUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::StopUuid()
{
    return stopUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::AckUuid()
{
    return ackUuid;
}

RobotServiceGattServer::RobotServiceGattServer()
    : speedLeft(service, RobotServiceDefinition::SpeedLeftUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , speedRight(service, RobotServiceDefinition::SpeedRightUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , directionLeft(service, RobotServiceDefinition::DirectionLeftUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , directionRight(service, RobotServiceDefinition::DirectionRightUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , stop(service, RobotServiceDefinition::StopUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , ack(service, RobotServiceDefinition::AckUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::notify, permissionFlags)
{}

services::GattServerService& RobotServiceGattServer::Service()
{
    return service;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::SpeedLeft()
{
    return speedLeft;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::SpeedRight()
{
    return speedRight;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::DirectionLeft()
{
    return directionLeft;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::DirectionRight()
{
    return directionRight;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::Stop()
{
    return stop;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServer::Ack()
{
    return ack;
}
