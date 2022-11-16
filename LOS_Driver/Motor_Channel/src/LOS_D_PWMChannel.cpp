#include "LOS_D_PWMChannel.hpp"

PWMChannel::PWMChannel(uint16_t pinNum, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, 
                        uint16_t timerChannel) :    pin_num_(pin_num), 
                                                    port_(port), 
                                                    timer_(timer), 
                                                    timer_channel_(timer_channel) {
    HAL_TIM_PWM_Start(timer, timer_channel);

    uint32_t prescalar = timer->Init.Prescalar;
    uint32_t period_ticks = timer->Init.Period;
}

void PWMChannel::set(uint8_t percent) {
    if (percent > 100) {
        return;
    }
    
    uint32_t us = (percent * (MAX_SIGNAL - MIN_SIGNAL)) / 100 + MIN_SIGNAL;
    uint32_t ticks = static_cast<uint32_t>((static_cast<float>(us) / static_cast<float>(PWM_PERIOD)) 
                        * static_cast<float>(period_ticks));

    __HAL_TIM_SET_COMPARE(timer, timer_channel, ticks);
}