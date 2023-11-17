#ifndef CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP
#define CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP

#include "infra/util/ByteRange.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/Optional.hpp"
#include "robot_interfaces/CarControl.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include "robot_interfaces/RobotServiceGattServer.hpp"
#include "services/ble/GattServer.hpp"
#include <cstdint>
#include <sys/types.h>

class CarControlToGattCharacteristic
    : public services::GattServerCharacteristicObserver
{
public:
    CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer);

    void DataReceived(infra::ConstByteRange data) override;

private:
    class ControlDataParser
    {
    public:
        ControlDataParser(infra::ConstByteRange data);

        uint8_t& SpeedLeft();
        uint8_t& SpeedRight();
        Direction& DirectionLeft();
        Direction& DirectionRight();

    private:
        Direction directionLeft;
        uint8_t speedLeft;
        Direction directionRight;
        uint8_t speedRight;
    };

    class GattServerCharacteristicAck
    {
    public:
        GattServerCharacteristicAck(services::GattServerCharacteristicUpdate& subject);

        void SendAck();

    private:
        services::GattServerCharacteristicUpdate& subject;
    };

private:
    CarControl& carControl;
    RobotServiceGattServer& robotServiceGattServer;
    infra::Function<void()> sendAck;

    infra::Optional<ControlDataParser> controlDataParser;
    GattServerCharacteristicAck gattSubjectAck;
};

#endif
