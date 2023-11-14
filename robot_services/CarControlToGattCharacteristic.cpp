#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "infra/util/Compatibility.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/MemoryRange.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

CarControlToGattCharacteristic::CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer)
    : carControl(carControl)
    , robotServiceGattServer(robotServiceGattServer)
    , sendAck([this]()
          {
              gattSubjectAck.SendAck();
          })
    , gattObserverSpeedLeft(robotServiceGattServer.SpeedLeft(), [this](uint8_t data)
          {
              this->carControl.SpeedMotorLeft(data, sendAck);
          })
    , gattObserverSpeedRight(robotServiceGattServer.SpeedRight(), [this](uint8_t data)
          {
              this->carControl.SpeedMotorRight(data, sendAck);
          })
    , gattObserverDirectionLeft(robotServiceGattServer.DirectionLeft(), [this](uint8_t data)
          {
              this->carControl.DirectionMotorLeft(static_cast<Direction>(data), sendAck);
          })
    , gattObserverDirectionRight(robotServiceGattServer.DirectionRight(), [this](uint8_t data)
          {
              this->carControl.DirectionMotorRight(static_cast<Direction>(data), sendAck);
          })
    , gattObserverStop(robotServiceGattServer.Stop(), [this](EMIL_MAYBE_UNUSED uint8_t data)
          {
              this->carControl.StopMotors(sendAck);
          })
    , gattSubjectAck(robotServiceGattServer.Ack())
{}

CarControlToGattCharacteristic::GattServerExclusiveReceiveCharacteristic::GattServerExclusiveReceiveCharacteristic(services::GattServerCharacteristicUpdate& subject, infra::Function<void(uint8_t data)> onDataReceived)
    : services::GattServerCharacteristicObserver(subject)
    , onDataReceived(onDataReceived)
{}

void CarControlToGattCharacteristic::GattServerExclusiveReceiveCharacteristic::DataReceived(infra::ConstByteRange data)
{
    onDataReceived(data.front());
}

CarControlToGattCharacteristic::GattServerCharacteristicAck::GattServerCharacteristicAck(services::GattServerCharacteristicUpdate& subject)
    : subject(subject)
{}

void CarControlToGattCharacteristic::GattServerCharacteristicAck::SendAck()
{
    static constexpr uint8_t ok = 0;
    subject.Update(infra::MakeRangeFromSingleObject(ok), infra::emptyFunction);
}