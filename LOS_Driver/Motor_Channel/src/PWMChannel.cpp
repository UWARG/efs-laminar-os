#include "PWMChannel.hpp"

PWMChannel::PWMChannel(uint16_t pinNum, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, uint16_t timerChannel) : pinNum(pinNum), port(port), timer(timer), timerChannel(timerChannel) {
    HAL_TIM_PWM_Start(timer, timer_channel);
}

PWMChannel::set(uint8_t percent) {
    uint32_t prescalar = timer->Init.Prescalar;
    uint32_t us = (percent * (MAX_SIGNAL - MIN_SIGNAL)) / 100 + MIN_SIGNAL;
    uint32_t periodTicks = timer->Init.Period;
    uint32_t ticks = static_cast<uint32_t>((static_cast<float>(us) / static_cast<float>(pwmPeriod)) * static_cast<float>(periodTicks));

    __HAL_TIM_SET_COMPARE(timer, timer_channel, ticks);
}