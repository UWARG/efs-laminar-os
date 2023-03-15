#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>

/* LOS_Link */
#include "LOS_D_RcReceiver.hpp"

constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
constexpr uint8_t NUM_RX_CHANNELS = 5;

extern RcReceiver* rc_receivers_[];


/* Los Actuators */
#include "LOS_D_MotorChannel.hpp"

const uint8_t NUM_ACTUATOR_CHANNELS = 1;

extern MotorChannel* motor_channels_[];

/* Los Telem */
#include "FreeRTOS.h"
#include "queue.h"
#include "LOS_D_GenericCommsDevice.hpp"
#include "usart.h"

const int TELEM_BUFFER_SIZE = 100;
const int TELEM_QUEUE_SIZE = 500;

extern UART_HandleTypeDef* telem_uart;
extern GenericCommsDevice telem_driver;
extern QueueHandle_t telem_queue;

/* Los Comms */
const int COMMS_BUFFER_SIZE = 50;
const int COMMS_QUEUE_SIZE = 200;

extern UART_HandleTypeDef* comms_uart;
extern GenericCommsDevice comms_driver;
extern QueueHandle_t comms_queue;

#endif // CONFIG_HPP_