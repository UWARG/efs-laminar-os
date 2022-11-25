#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>
#include "main.h"
#include "tim.h"


#include "main.h"

#include "LOS_D_MotorChannel.hpp"

#include "main.h"

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
// #define BMX160_CONNECTED
// #define MPXV7002DP_CONNECTED
// #define MPL3115A2_CONNECTED
// #define NEOM8_CONNECTED

#ifdef BMX160_CONNECTED
#include "BMX160.hpp"
static IMU *g_imuObj = &BMX160::getInstance(); // BMX160 imu
#endif

#ifdef MPU6050_CONNECTED
#include "MPU6050.hpp"
static IMU g_imuObj = &MPU6050::getInstance(); // MPU6050 imu
#endif

#ifdef VN300_CONNECTED
#include "VN300.hpp"
static IMU g_imuObj = &VN300::getInstance(); // VECTOR NAV - 300 
#else
const bool SENSOR_FUSION_ = true;
#endif

#ifdef MPXV7002DP_CONNECTED
#include "MPXV7002DP.hpp"
static airspeed *g_airspeedObj = MPXV7002DP::GetInstance(); // MPXV7002DP Airspeed
#endif

#ifdef MPL3115A2_CONNECTED
#include "MPL3115A2.hpp"
static Altimeter *g_altimeterObj = &MPL3115A2::getInstance(); // MPL3115A2 altimeter
#endif 

#ifdef NEOM8_CONNECTED
#include "NEOM8.hpp"
static Gps *g_gpsObj = NEOM8::GetInstance(); // NEOM8 Gps
#endif

/* LOS_Actuators */
extern const uint8_t NUM_ACTUATOR_CHANNELS;
extern MotorChannel *motor_channels_[];

#endif