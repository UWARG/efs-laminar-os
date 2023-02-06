#include "config.hpp"
#include "main.h"
#include "tim.h"
#include "usart.h"

/* Los_Link */
#include "LOS_D_PPMChannel.hpp"
PPMChannel ppm_channel(&htim2, TIM_CHANNEL_1, NUM_RX_CHANNELS);

RcReceiver* rc_receivers_[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};

/* Los_Actuators */
#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"

PWMChannel pwmChannel = PWMChannel(0, nullptr, 
                    &htim2, TIM_CHANNEL_1);

MotorChannel *motor_channels_[NUM_ACTUATOR_CHANNELS] = {&pwmChannel};

/* Los Telem */
QueueHandle_t telem_queue = xQueueCreate( TELEM_QUEUE_SIZE,sizeof( uint8_t ) ); 
UART_HandleTypeDef* telem_uart = &huart2;
GenericCommsDevice telem_driver(telem_uart, telem_queue);

/* Los Comms */
QueueHandle_t comms_queue = xQueueCreate( COMMS_QUEUE_SIZE,sizeof( uint8_t ) );
UART_HandleTypeDef* comms_uart = &huart3;
GenericCommsDevice comms_driver(comms_uart, comms_queue);
