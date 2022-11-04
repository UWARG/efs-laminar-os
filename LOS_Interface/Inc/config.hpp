#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>

/* LOS_Link */
#define PPM
const uint8_t NUM_RX_CHANNELS = 5;
const int32_t ARM_DISARM_CHANNEL_INDEX = 4;
const uint8_t GIMBAL_GRABBER_TOGGLE_INDEX = 5; // three-way switch for gimbal, grabber, or none
const uint8_t LEFT_GIMBAL_GRABBER_CRANE = 6;
const uint8_t RIGHT_GIMBAL_GRABBER_MOUTH = 7;

/* LOS_Pos */
static IMU *g_imuObj = &BMX160::getInstance(); // BMX160 imu
// g_imuObj = &MPU6050::getInstance(); // MPU6050 imu
static Altimeter *g_altimeterObj = &MPL3115A2::getInstance(); // MPL3115A2 altimeter
static airspeed *g_airspeedObj = MPXV7002DP::GetInstance(); // MPXV7002DP Airspeed
static Gps *g_gpsObj = NEOM8::GetInstance(); // NEOM8 Gps
// g_imuObj = &VN300::getInstance(); // VECTOR NAV - 300 
const bool SENSOR_FUSION_ = true;

#endif