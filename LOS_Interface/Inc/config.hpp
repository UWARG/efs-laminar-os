#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>
#include "main.h"
#include "tim.h"


/* LOS_Link */
#define PPM
const uint8_t MAX_PPM_CHANNELS = 12;
const uint8_t NUM_RX_CHANNELS = 5;
const uint16_t PPM_TIMEOUT = 1000;
const int32_t ARM_DISARM_CHANNEL_INDEX = 4;
const uint8_t GIMBAL_GRABBER_TOGGLE_INDEX = 5; // three-way switch for gimbal, grabber, or none
const uint8_t LEFT_GIMBAL_GRABBER_CRANE = 6;
const uint8_t RIGHT_GIMBAL_GRABBER_MOUTH = 7;

/* LOS_Pos */


#endif