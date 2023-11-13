#ifndef CAR_CONTROLLER_MOCK_HPP
#define  CAR_CONTROLLER_MOCK_HPP

#include "robot_interfaces/CarControl.hpp"
#include "gmock/gmock.h"

class CarControlMock
: public CarControl
{
    public:
    MOCK_METHOD(void, SpeedMotorLeft, (uint8_t percentage, infra::Function<void()> onDone));
    MOCK_METHOD(void, SpeedMotorRight, (uint8_t percentage, infra::Function<void()> onDone));

    MOCK_METHOD(void, DirectionMotorLeft, (Direction direction, infra::Function<void()> onDone));
    MOCK_METHOD(void, DirectionMotorRight, (Direction direction, infra::Function<void()> onDone));

    MOCK_METHOD(void, StopMotors, (infra::Function<void()> onDone));
};

#endif
