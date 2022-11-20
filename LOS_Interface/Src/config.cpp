#include "config.hpp"

/* LOS_Link */
PPMChannel ppm_channel(&htim2, TIM_CHANNEL_1, NUM_RX_CHANNELS);

/* LOS_Actuators */

// DSHOTChannel channel1(PWM1_Pin, PWM1_GPIO_Port, &htim1, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
// PWMChannel   channel2(PWM6_Pin, PWM6_GPIO_Port, &htim3, TIM_CHANNEL_1);

// For example test build:
// DSHOTChannel    channel1(0, nullptr, nullptr, 0, 0, 0);
// PWMChannel      channel2(1, nullptr, nullptr, 1);
