#include "robot_services/CarControlToGattCharacteristic.hpp"

CarControlToGattCharacteristic::CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer)
    : carControl(carControl)
    , robotServiceGattServer(robotServiceGattServer)
{
    robotServiceGattServer.SpeedLeft();
    robotServiceGattServer.SpeedRight();
    robotServiceGattServer.DirectionLeft();
    robotServiceGattServer.DirectionRight();
    robotServiceGattServer.Stop();
    robotServiceGattServer.Ack();
}