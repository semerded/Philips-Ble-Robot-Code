#ifndef CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP
#define CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP

#include "infra/util/Function.hpp"
#include "robot_interfaces/CarControl.hpp"
#include "robot_interfaces/RobotServiceGattServer.hpp"
#include "services/ble/GattServer.hpp"
#include <cstdint>
#include <sys/types.h>

class CarControlToGattCharacteristic
{
public:
    CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer);

private:
    class GattServerExclusiveReceiveCharacteristic
        : public services::GattServerCharacteristicObserver
    {
    public:
        GattServerExclusiveReceiveCharacteristic(services::GattServerCharacteristicUpdate& subject, infra::Function<void(uint8_t data)> onDataReceived);

        void DataReceived(infra::ConstByteRange data) override;

    private:
        infra::Function<void(uint8_t data)> onDataReceived;
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

    GattServerExclusiveReceiveCharacteristic gattObserverSpeedLeft;
    GattServerExclusiveReceiveCharacteristic gattObserverSpeedRight;
    GattServerExclusiveReceiveCharacteristic gattObserverDirectionLeft;
    GattServerExclusiveReceiveCharacteristic gattObserverDirectionRight;
    GattServerExclusiveReceiveCharacteristic gattObserverStop;
    GattServerCharacteristicAck gattSubjectAck;
};

#endif
