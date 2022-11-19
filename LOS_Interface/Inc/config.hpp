#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>
#include "main.h"
#include "tim.h"

#include "LOS_D_PWMChannel.hpp"
#include "LOS_D_DSHOTChannel.hpp"
#include "LOS_D_PPMChannel.hpp"

/* LOS_Link */
static constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
static constexpr uint8_t NUM_RX_CHANNELS = 5;

PPMChannel ppm_channel(&htim2, TIM_CHANNEL_1, NUM_RX_CHANNELS);

constexpr RcReceiver* rc_receivers[NUM_RC_RECEIVER_INSTANCES] = {&ppm_channel};

/* LOS_Pos */
#define BMX160_CONNECTED
#define MPXV7002DP_CONNECTED
#define MPL3115A2_CONNECTED
#define NEOM8_CONNECTED

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
const uint8_t NUM_CHANNELS = 2;

// DSHOTChannel channel1(PWM1_Pin, PWM1_GPIO_Port, &htim1, TIM_CHANNEL_1, TIM_DMA_ID_CC1, TIM_DMA_CC1);
// PWMChannel   channel2(PWM6_Pin, PWM6_GPIO_Port, &htim3, TIM_CHANNEL_1);

// For example test build:
DSHOTChannel    channel1(0, nullptr, nullptr, 0, 0, 0);
PWMChannel      channel2(1, nullptr, nullptr, 1);

constexpr MotorChannel *motor_channels_[NUM_CHANNELS] = {&channel1, &channel2};

// Ensure correct number of motor channels have been set
static_assert(motor_channels_[NUM_CHANNELS - 1] != nullptr, "Invalid motor channel configuration");

#endif