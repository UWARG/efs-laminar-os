#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>

/* LOS_Link */
#include "LOS_D_RcReceiver.hpp"
#include "LOS_D_RcSender.hpp"

constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
constexpr uint8_t NUM_RX_CHANNELS = 8;
constexpr uint8_t NUM_RC_SENDER_INSTANCES = 1;
constexpr uint8_t NUM_TX_CHANNELS = 8;

extern RcReceiver* rc_receivers_[];
extern RcSender* rc_senders_[];


/* Los Actuators */
#include "LOS_D_MotorChannel.hpp"

const uint8_t NUM_ACTUATOR_CHANNELS = 1;

extern MotorChannel* motor_channels_[];

#endif // CONFIG_HPP_