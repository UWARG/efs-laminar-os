#include "config.hpp"
#include "main.h"
#include "tim.h"

/* Los_Link */
#include "LOS_D_PPMChannel.hpp"
PPMChannel ppm_channel(&htim4, TIM_CHANNEL_1, NUM_RX_CHANNELS);

RcReceiver* rc_receivers_[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};

/* Los_Actuators */
#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"

PWMChannel pwmChannel = PWMChannel(0, nullptr, 
                    &htim2, TIM_CHANNEL_1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};


/* Los Telem */
UART_HandleTypeDef* telem_uart = &huart1;
GenericCommsDevice telem_driver;
QueueHandle_t telem_queue;

/* Los Comms */
UART_HandleTypeDef* comms_uart = &huart3;
GenericCommsDevice comms_driver;
QueueHandle_t comms_queue;