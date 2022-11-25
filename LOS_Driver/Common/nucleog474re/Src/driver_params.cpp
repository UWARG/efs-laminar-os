#include "driver_params.hpp"
#include "config.h"

#include "LOS_D_DSHOTChannel.h"
#include "LOS_D_PWMChannel.h"

#define PWM1_PIN  0 
#define PWM1_PORT nullptr

#define PWM2_PIN  0 
#define PWM2_PORT nullptr

#define TIM1_HANDLE &htim1
#define TIM2_HANDLE &htim2

const uint8_t NUM_ACTUATOR_CHANNELS = 2;

PWMChannel pwmChannel = PWMChannel(PWM2_PIN, PWM2_PORT, 
                    TIM2_HANDLE, TIM_CHANNEL_1);

DSHOTChannel dshotChannel = DSHOTChannel(PWM1_PIN, PWM1_PORT, TIM1_HANDLE, 
                        TIM_CHANNEL_1, TIM_DMA_ID_CC1, 
                        TIM_DMA_CC1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel, &dshotChannel};