#include "robot_services/CarControlToGattCharacteristic.hpp"
#include "robot_services/BasicCarControl.hpp"
#include "robot_services/RobotServiceDefinition.hpp"

CarControlToGattCharacteristic::CarControlToGattCharacteristic(BasicCarControl& carControl, RobotServiceGattServer& robotServiceGattServer)
: carControl(carControl)
, robotServiceGattServer(robotServiceGattServer)
{};