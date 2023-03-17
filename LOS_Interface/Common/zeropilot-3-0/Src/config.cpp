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

PWMChannel pwmChannel = PWMChannel(0, nullptr, &htim3, TIM_CHANNEL_2);

MotorChannel* motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};