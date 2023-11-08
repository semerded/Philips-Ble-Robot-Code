#ifndef PWM_DRIVER_HPP
#define PWM_DRIVER_HPP

#include DEVICE_HEADER
#include "stm32wbxx_hal_tim.h"
#include <cstdint>
#include "robot_interfaces/PwmDriver.hpp"

class PwmDriverImpl
    : public PwmDriver
{
public:
    PwmDriverImpl(TIM_TypeDef* timer);

    // Implements PwmDriver
    void SetDutyCycle(uint8_t dutyCycle) override;

private:
    TIM_HandleTypeDef handle;
};

#endif
