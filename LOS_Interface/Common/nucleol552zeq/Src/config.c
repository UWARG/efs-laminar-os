#include "config.h"

#define TIM1_HANDLE &htim4

const uint8_t NUM_ACTUATOR_CHANNELS = 1;

PWMChannel pwmChannel = PWMChannel(0, nullptr, 
                    TIM1_HANDLE, TIM_CHANNEL_1);

// DSHOTChannel dshotChannel = DSHOTChannel(0, nullptr, 
//                     TIM1_HANDLE, TIM_CHANNEL_1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};
