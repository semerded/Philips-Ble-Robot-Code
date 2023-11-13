#ifndef CAR_CONTROLLER_MOCK_HPP
#define  CAR_CONTROLLER_MOCK_HPP

#include "robot_interfaces/CarControl.hpp"
#include "gmock/gmock.h"

class CarControlMock
: public CarControl
{
    public:
    MOCK_METHOD(void, speedMotorLeft, (uint8_t percentage, infra::Function<void()> onDone));
    MOCK_METHOD(void, speedMotorRight, (uint8_t percentage, infra::Function<void()> onDone));
    
    MOCK_METHOD(void, directionMotorLeft, (Direction direction, infra::Function<void()> onDone));
    MOCK_METHOD(void, directionMotorRight, (Direction direction, infra::Function<void()> onDone));

    MOCK_METHOD(void, stopMotors, (infra::Function<void()> onDone));
};

#endif
