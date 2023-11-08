#ifndef ROBOT_INTERFACES_PWM_DRIVER_HPP
#define ROBOT_INTERFACES_PWM_DRIVER_HPP

#include <cstdint>

class PwmDriver
{
public:
    virtual void SetDutyCycle(uint8_t dutyCycle) = 0;
};

#endif