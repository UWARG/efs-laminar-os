#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>
#include "main.h"
#include "tim.h"

#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"
#include "LOS_D_PPMChannel.hpp"

/* LOS_Link */
constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
constexpr uint8_t NUM_RX_CHANNELS = 5;

extern PPMChannel ppm_channel;

constexpr RcReceiver* rc_receivers[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};


// /* LOS_Actuators */
// const uint8_t NUM_CHANNELS = 2;

// // DSHOTChannel channel1(PWM1_Pin, PWM1_GPIO_Port, &htim1, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
// // PWMChannel   channel2(PWM6_Pin, PWM6_GPIO_Port, &htim3, TIM_CHANNEL_1);

// // For example test build:
// extern DSHOTChannel    channel1;
// extern PWMChannel      channel2;

// constexpr MotorChannel *motor_channels_[NUM_CHANNELS] = {&channel1, &channel2};
// static_assert(motor_channels_[NUM_CHANNELS - 1] != nullptr, "Invalid motor channel configuration");

#endif