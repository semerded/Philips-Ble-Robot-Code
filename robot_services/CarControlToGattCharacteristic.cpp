#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "infra/util/Function.hpp"
#include "infra/util/MemoryRange.hpp"
#include "infra/util/ReallyAssert.hpp"
#include "robot_interfaces/MotorShieldControllerDc.hpp"
#include <cstdint>

CarControlToGattCharacteristic::CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer)
    : services::GattServerCharacteristicObserver(robotServiceGattServer.Control())
    , carControl(carControl)
    , robotServiceGattServer(robotServiceGattServer)
    , sendAck([this]()
          {
              gattSubjectAck.SendAck();
          })
    , gattSubjectAck(robotServiceGattServer.Ack())
{}

void CarControlToGattCharacteristic::DataReceived(infra::ConstByteRange data)
{
    controlDataParser.Emplace(data);

    this->carControl.SpeedMotorLeft(this->controlDataParser->SpeedLeft(), [this]()
        {
            this->carControl.SpeedMotorRight(this->controlDataParser->SpeedRight(), [this]()
                {
                    this->carControl.DirectionMotorLeft(this->controlDataParser->DirectionLeft(), [this]()
                        {
                            this->carControl.DirectionMotorRight(this->controlDataParser->DirectionRight(), sendAck);
                        });
                });
        });
}

CarControlToGattCharacteristic::ControlDataParser::ControlDataParser(infra::ConstByteRange data)
{
    really_assert(data.size() == 4);

    directionLeft = static_cast<Direction>(data[0]);
    speedLeft = data[1];
    directionRight = static_cast<Direction>(data[2]);
    speedRight = data[3];
}

uint8_t& CarControlToGattCharacteristic::ControlDataParser::SpeedLeft()
{
    return speedLeft;
}

uint8_t& CarControlToGattCharacteristic::ControlDataParser::SpeedRight()
{
    return speedRight;
}

Direction& CarControlToGattCharacteristic::ControlDataParser::DirectionLeft()
{
    return directionLeft;
};

Direction& CarControlToGattCharacteristic::ControlDataParser::DirectionRight()
{
    return directionRight;
};

CarControlToGattCharacteristic::GattServerCharacteristicAck::GattServerCharacteristicAck(services::GattServerCharacteristicUpdate& subject)
    : subject(subject)
{}

void CarControlToGattCharacteristic::GattServerCharacteristicAck::SendAck()
{
    static constexpr uint8_t ok = 0;
    subject.Update(infra::MakeRangeFromSingleObject(ok), infra::emptyFunction);
}
