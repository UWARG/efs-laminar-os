#include "config.h"

#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"

PWMChannel pwmChannel = PWMChannel(0, nullptr, 
                    TIM2_HANDLE, TIM_CHANNEL_1);

DSHOTChannel dshotChannel = DSHOTChannel(0, nullptr, TIM1_HANDLE, 
                        TIM_CHANNEL_1, TIM_DMA_ID_CC1, 
                        TIM_DMA_CC1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel, &dshotChannel};
