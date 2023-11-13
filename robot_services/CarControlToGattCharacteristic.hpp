#ifndef CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP
#define CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP

#include "robot_services/BasicCarControl.hpp"
#include "robot_services/RobotServiceDefinition.hpp"

class CarControlToGattCharacteristic
{
CarControlToGattCharacteristic(BasicCarControl& carControl, RobotServiceGattServer& robotServiceGattServer);
// ~CarControlToGattCharacteristic();
private:
    BasicCarControl& carControl;
    RobotServiceGattServer& robotServiceGattServer;
};

#endif
