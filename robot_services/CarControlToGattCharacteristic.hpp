#ifndef CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP
#define CAR_CONTROL_TO_GATT_CHARACTERISTIC_HPP

#include "robot_interfaces/CarControl.hpp"
#include "robot_interfaces/RobotServiceGattServer.hpp"

class CarControlToGattCharacteristic
{
public:
    CarControlToGattCharacteristic(CarControl& carControl, RobotServiceGattServer& robotServiceGattServer);
    // ~CarControlToGattCharacteristic();
private:
    CarControl& carControl;
    RobotServiceGattServer& robotServiceGattServer;
};

#endif
