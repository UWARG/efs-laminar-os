#ifndef CONFIG_HPP_
#define CONFIG_HPP_


#include <cstdint>
#include "main.h"
#include "tim.h"

/* LOS_Link */
#include "LOS_D_PPMChannel.hpp"

constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
constexpr uint8_t NUM_RX_CHANNELS = 5;

extern PPMChannel ppm_channel;

constexpr RcReceiver* rc_receivers[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};

#endif // CONFIG_HPP_