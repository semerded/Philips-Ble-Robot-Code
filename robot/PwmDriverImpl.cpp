#include "robot/PwmDriverImpl.hpp"
#include <cstdint>
#include <cstdlib>
#include <algorithm>

namespace
{
    constexpr auto pwmFrequency = 490;
    constexpr auto timerFrequency = 1000000;
    auto prescaler = 63; // ((SystemCoreClock) / timerFrequency) - 1;
    auto period = (timerFrequency / pwmFrequency) - 1;
}

PwmDriverImpl::PwmDriverImpl(TIM_TypeDef* timer)
{
    handle.Instance = timer;
    handle.Init.Prescaler = prescaler;
    handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    handle.Init.Period = period;
    handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_PWM_Init(&handle) != HAL_OK)
        std::abort();

    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(&handle, &sMasterConfig) != HAL_OK)
        std::abort();
}

void PwmDriverImpl::SetDutyCycle(uint8_t dutyCycle)
{
    if (dutyCycle != std::clamp<uint8_t>(dutyCycle, 0, 100))
        std::abort();

    if (HAL_TIM_PWM_Stop_IT(&handle, TIM_CHANNEL_1) != HAL_OK)
        std::abort();

    auto pulse = period * dutyCycle / 100;

    TIM_OC_InitTypeDef sConfigOC = { 0 };
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&handle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
        std::abort();

    if (HAL_TIM_PWM_Start_IT(&handle, TIM_CHANNEL_1) != HAL_OK)
        std::abort();
}
