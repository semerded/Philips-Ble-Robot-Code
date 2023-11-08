#ifndef PWM_DRIVER_HPP
#define PWM_DRIVER_HPP

#include DEVICE_HEADER
#include "stm32wbxx_hal_tim.h"
#include <cstdint>

class PwmDriver
{
public:
    PwmDriver(TIM_TypeDef* timer);

    void SetDutyCycle(uint8_t dutyCycle);

private:
    TIM_HandleTypeDef handle;
};

#endif
