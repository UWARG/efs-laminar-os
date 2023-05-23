#include "config.hpp"

#include "main.h"
#include "tim.h"

/* Los_Link */
#include "LOS_D_PPMChannel.hpp"
PPMChannel ppm_channel(&htim3, TIM_CHANNEL_1, NUM_RX_CHANNELS);

RcReceiver* rc_receivers_[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};

/* Los_Actuators */
#include "LOS_D_DSHOTChannel.hpp"
#include "LOS_D_PWMChannel.hpp"

PWMChannel pwm_T3_C4 = PWMChannel(0, nullptr, &htim3, TIM_CHANNEL_4);
PWMChannel pwm_T3_C3 = PWMChannel(0, nullptr, &htim3, TIM_CHANNEL_3);
PWMChannel pwm_T3_C2 = PWMChannel(0, nullptr, &htim3, TIM_CHANNEL_2);
PWMChannel pwm_T3_C1 = PWMChannel(0, nullptr, &htim3, TIM_CHANNEL_1);
PWMChannel pwm_T4_C4 = PWMChannel(0, nullptr, &htim4, TIM_CHANNEL_4);
PWMChannel pwm_T4_C3 = PWMChannel(0, nullptr, &htim4, TIM_CHANNEL_3);
PWMChannel pwm_T4_C2 = PWMChannel(0, nullptr, &htim4, TIM_CHANNEL_2);
PWMChannel pwm_T4_C1 = PWMChannel(0, nullptr, &htim4, TIM_CHANNEL_1);

DSHOTChannel dshot_T1_C2 =
    DSHOTChannel(0, nullptr, &htim1, TIM_CHANNEL_2, TIM_DMA_ID_CC2, TIM_DMA_CC2);
DSHOTChannel dshot_T1_C1 =
    DSHOTChannel(0, nullptr, &htim1, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
DSHOTChannel dshot_T5_C4 =
    DSHOTChannel(0, nullptr, &htim5, TIM_CHANNEL_4, TIM_DMA_ID_CC4, TIM_DMA_CC4);
DSHOTChannel dshot_T5_C3 =
    DSHOTChannel(0, nullptr, &htim5, TIM_CHANNEL_3, TIM_DMA_ID_CC3, TIM_DMA_CC3);
DSHOTChannel dshot_T5_C2 =
    DSHOTChannel(0, nullptr, &htim5, TIM_CHANNEL_2, TIM_DMA_ID_CC2, TIM_DMA_CC2);
DSHOTChannel dshot_T5_C1 =
    DSHOTChannel(0, nullptr, &htim5, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
DSHOTChannel dshot_T16_C1 =
    DSHOTChannel(0, nullptr, &htim16, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
DSHOTChannel dshot_T17_C1 =
    DSHOTChannel(0, nullptr, &htim17, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);

MotorChannel* motor_channels_[NUM_ACTUATOR_CHANNELS] = {
    &pwm_T3_C4,   &pwm_T3_C3,   &pwm_T3_C2,    &pwm_T3_C1,    &pwm_T4_C4,   &pwm_T4_C3,
    &pwm_T4_C2,   &pwm_T4_C1,   &dshot_T1_C2,  &dshot_T1_C1,  &dshot_T5_C4, &dshot_T5_C3,
    &dshot_T5_C2, &dshot_T5_C1, &dshot_T16_C1, &dshot_T17_C1,
};