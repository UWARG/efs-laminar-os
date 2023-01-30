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
#define BMX160_CONNECTED
#define TARGET_BUILD
#define SENSOR_FUSION

#include "imu.hpp"
#include "gps.hpp"
#include "airspeed.hpp"
#include "altimeter.hpp"

#ifdef SENSOR_FUSION
#include "SensorFusion.hpp"
#endif

#ifdef BMX160_CONNECTED
#include "BMX160.hpp"
IMU* g_imuObj = &BMX160::getInstance(); // BMX160 imu
#endif

#endif // CONFIG_HPP_