#include "main.h"
#include "config.hpp"
#include "LOS_Link.hpp"


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    for (uint8_t i = 0; i < NUM_RC_RECEIVER_INSTANCES; ++i) {
        rc_receivers_[i]->interrupt_callback(htim);
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == TIM16) {
    HAL_IncTick();
    }

if (htim->Instance == TIM4){
    for (uint8_t i = 0; i < NUM_RC_SENDER_INSTANCES; ++i) {
        rc_senders_[i]->interrupt_callback(htim);
    }
}

}

