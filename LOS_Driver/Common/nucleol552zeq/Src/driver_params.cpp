#include "driver_params.hpp"
#include "config.hpp"

#include "LOS_D_DSHOTChannel.hpp"
#include "LOS_D_PWMChannel.hpp"

// These are not used anywhere, we should get rid of them
#define PWM1_PIN  0 
#define PWM1_PORT nullptr

#define TIM1_HANDLE &htim4

const uint8_t NUM_ACTUATOR_CHANNELS = 2;

PWMChannel pwmChannel = PWMChannel(PWM1_PIN, PWM1_PORT, 
                    TIM1_HANDLE, TIM_CHANNEL_1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};