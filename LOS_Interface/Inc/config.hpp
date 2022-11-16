#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>

#include "main.h"

#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"

/* LOS_Link */
#define PPM
const uint8_t NUM_RX_CHANNELS = 5;
const int32_t ARM_DISARM_CHANNEL_INDEX = 4;
const uint8_t GIMBAL_GRABBER_TOGGLE_INDEX = 5; // three-way switch for gimbal, grabber, or none
const uint8_t LEFT_GIMBAL_GRABBER_CRANE = 6;
const uint8_t RIGHT_GIMBAL_GRABBER_MOUTH = 7;

/* LOS_Actuators */
const uint8_t NUM_CHANNELS = 2;

// DSHOTChannel channel1(PWM1_Pin, PWM1_GPIO_Port, &htim1, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
// PWMChannel   channel2(PWM6_Pin, PWM6_GPIO_Port, &htim3, TIM_CHANNEL_1);

// For example test build:
DSHOTChannel    channel1(0, nullptr, nullptr, 0, 0, 0);
PWMChannel      channel2(1, nullptr, nullptr, 1);

constexpr MotorChannel *motor_channels_[NUM_CHANNELS] = {&channel1, &channel2};

// Ensure correct number of motor channels have been set
static_assert(motor_channels_[NUM_CHANNELS - 1] != nullptr, "Invalid motor channel configuration");

#endif