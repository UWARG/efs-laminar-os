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

/* Los Position */
#include "LOS_D_IMU.hpp"
#include "gps.hpp"
#include "airspeed.hpp"
#include "altimeter.hpp"

// defining the connected sensors to select which sensors are used
#define BMX160_CONNECTED
//#define NEOM8_CONNECTED
#define VN300_CONNECTED
//#define SENSOR_FUSION

#ifdef SENSOR_FUSION
#include "LOS_D_SensorFusion.hpp"
#endif

#ifdef BMX160_CONNECTED
#include "LOS_D_BMX160.hpp"
#endif

#ifdef NEOM8_CONNECTED
/* TODO: Inlcude NEOM8 header */
#endif

#ifdef VN300_CONNECTED
#include "LOS_D_VN300.hpp"
#endif

#endif // CONFIG_HPP_