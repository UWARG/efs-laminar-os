#include "config.hpp"
#include "main.h"
#include "tim.h"

/* Los_Link */
#include "LOS_D_PPMChannel.hpp"
#include "LOS_D_PPMChannelOut.hpp"

PPMChannel ppm_channel(&htim3, TIM_CHANNEL_1, NUM_RX_CHANNELS);
PPMChannelOut ppm_channel_out(&htim4, TIM_CHANNEL_1, NUM_TX_CHANNELS);

RcReceiver* rc_receivers_[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};
RcSender* rc_senders_[NUM_RC_SENDER_INSTANCES] = {&ppm_channel_out};

/* Los_Actuators */
#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"

PWMChannel pwmChannel = PWMChannel(0, nullptr, 
                    &htim2, TIM_CHANNEL_1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};
