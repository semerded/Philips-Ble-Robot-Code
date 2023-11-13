#include "robot_services/CarControlToGattCharacteristic.hpp"


CarControlToGattCharacteristic::CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer)
    : carControl(carControl)
    , robotServiceGattServer(robotServiceGattServer){};