#include "robot_services/RobotServiceDefinition.hpp"

namespace
{
    constexpr auto maxPacketSize = 23 - 3; // Optimization as found in ST document AN5289 Rev 7 (Section 7.6.9 How to maximize data throughput).
    constexpr auto permissionFlags = services::GattServerCharacteristic::PermissionFlags::none;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::ServiceUuid()
{
    return serviceUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::ControlUuid()
{
    return controlUuid;
}

const services::AttAttribute::Uuid128& RobotServiceDefinition::AckUuid()
{
    return ackUuid;
}

RobotServiceGattServerImpl::RobotServiceGattServerImpl()
    : control(service, RobotServiceDefinition::ControlUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::writeWithoutResponse, permissionFlags)
    , ack(service, RobotServiceDefinition::AckUuid(), maxPacketSize, services::GattCharacteristic::PropertyFlags::notify, permissionFlags)
{}

services::GattServerService& RobotServiceGattServerImpl::Service()
{
    return service;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServerImpl::Control()
{
    return control;
}

services::GattServerCharacteristicUpdate& RobotServiceGattServerImpl::Ack()
{
    return ack;
}
