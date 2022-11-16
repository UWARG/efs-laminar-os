/*
 * imu.cpp
 *
 *  Created on: May 24, 2022
 *      Author: anthony
 */

/* Includes ------------------------------------------------------------------*/
#include "imu.hpp"
#include "BMX160.hpp"
#include "MPU6050.hpp"
//#include <Inc/LOS_Link.hpp>

#include <cstdint>

/* Private define ------------------------------------------------------------*/

/* BMX160 Relevant Registers
 Taken from datasheet: https://www.mouser.com/pdfdocs/BST-BMX160-DS000-11.pdf
 */

static constexpr uint8_t BMX160_READ_BIT = 0x01;
static constexpr uint8_t BMX160_WRITE_BIT = 0x00;
static constexpr uint8_t BMX160_DUMMY_BYTE = 0x00;

static constexpr uint8_t BMX160_I2C_ADDR = (0x68 << 1); // Left-aligned slave address

static constexpr uint8_t CHIP_ID_REG = 0x00;
static constexpr uint8_t DATA_REG = 0x04;
static constexpr uint8_t STATUS_REG = 0x1B;
static constexpr uint8_t CMD_REG = 0x7E;
static constexpr uint8_t PMU_STATUS_REG = 0x03;

// Registers for configuring accelerometer, gyroscope, and magnetometer
static constexpr uint8_t ACC_CONF_REG = 0x40;
static constexpr uint8_t ACC_RANGE_REG = 0x41;
static constexpr uint8_t GYR_CONF_REG = 0x42;
static constexpr uint8_t GYR_RANGE_REG = 0x43;
static constexpr uint8_t MAG_CONF_REG = 0x44;
static constexpr uint8_t MAG_IF_0_REG = 0x4C;
static constexpr uint8_t MAG_IF_1_REG = 0x4D;
static constexpr uint8_t MAG_IF_2_REG = 0x4E;
static constexpr uint8_t MAG_IF_3_REG = 0x4F;

static constexpr uint8_t MAX_BUFF_SIZE = 21;

static uint8_t MAG_REPZ_REG = 0x52;
static uint8_t MAG_REPXY_REG = 0x51;
static uint8_t MAG_MODE_REG = 0x4B;

// Registers for setting power mode to normal
static uint8_t ACC_NORMAL_MODE_CMD = 0x11;
static uint8_t GYRO_NORMAL_MODE_CMD = 0x15;
static uint8_t MAG_NORMAL_MODE_CMD = 0x19;

static uint8_t ACC_RANGE_8G = 0x08;

// From datasheet - last four bits (1011 indicates a sampling rate of 800 Hz)
// The first four bits indicate OSR4 - data is sampled at an oversampling rate of 4
static uint8_t ACC_ODR_800_OSR4 = 0x0B; // 0b00001011

static uint8_t GYRO_RANGE_1000 = 0x01;

// From datasheet - last four bits (1011 indicates a sampling rate of 800 Hz)
// The first four bits indicate OSR4 - data is sampled at an oversampling rate of 4
static uint8_t GYRO_ODR_800_OSR4 = 0x0B; // 0b00001011
static uint8_t MAG_SETUP_EN = 0x80;
static uint8_t MAG_SETUP_DIS = 0x00;
static uint8_t REP_XY_REGULAR_PRESET = 0x04; // TODO there is also a high accuracy preset. Not too sure what that's about.
static uint8_t REP_Z_REGULAR_PRESET = 0x0E;
static uint8_t MAG_IF_3_DATA_MODE = 0x02;
static uint8_t MAG_IF_2_DATA_MODE = 0x4C;
static uint8_t MAG_IF_1_DATA_MODE = 0x42;
static uint8_t MAG_REFRESH_200_HZ = 0x09;
static uint8_t MAG_REFRESH_50_HZ = 0x07;
static uint8_t MAG_SLEEP_MODE = 0x01;

constexpr float GYRO_RANGE_1000_FACTOR = 1879.3f; // lsb/rad/s
constexpr float ACC_RANGE_8_FACTOR = 4.096f; // lsb/mg
constexpr float MAG_ADJUST_FACTOR = 16.0f; // lsb/uT

/* Arrays for data collection and calibration */
static int16_t accXLog[2000];
static int16_t accYLog[2000];
static int16_t accZLog[2000];

static int16_t gyrXLog[2000];
static int16_t gyrYLog[2000];
static int16_t gyrZLog[2000];

static uint16_t index;
static uint8_t cnter;


/* MPU6050 defines */ //Might need some cleaning

#define WHO_AM_I 0x75 // Use to check if device is there

#define MPU6050_ADDRESS (0x68 << 1) // 7-bit address

#define PWR_MGMT_1 0x6B

#define SMPLRT_DIV 0x19

//Config
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

//Gryo registers
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x44
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

//Accelerometer register
#define ACCEL_XOUT_H 0x3B

// constants

const uint8_t kImuAddr = 104;
const double kGryoCorrector = 131.0;
const double kAccelCorrector = 16384.0;


/* Private variables ---------------------------------------------------------*/
//I2C_HandleTypeDef hi2c1;

/* Public Methods  ---------------------------------------------------------*/

IMU& MPU6050::getInstance(){
  static MPU6050 singleton;
  return singleton;

}

void MPU6050::GetResult(IMUData_t &Data){
	uint8_t data[6];
	int16_t raw_x = 0, raw_y = 0, raw_z = 0;
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, GYRO_XOUT_H, 1, data, 6, HAL_MAX_DELAY);

	raw_x = (int16_t)(data[0] << 8 | data[1]);
	raw_y = (int16_t)(data[2] << 8 | data[3]);
	raw_z = (int16_t)(data[4] << 8 | data[5]);

	/* Converting raw values into degrees per second.
	* Scaling by the sensitivity for the configured scale range.*/

	Data.gyro_x = raw_x / kGryoCorrector;
	Data.gyro_y = raw_y / kGryoCorrector;
	Data.gyro_z = raw_z / kGryoCorrector;

	status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, ACCEL_XOUT_H, 1, data, 6, HAL_MAX_DELAY);

	raw_x = (int16_t)(data[0] << 8 | data[1]);
	raw_y = (int16_t)(data[2] << 8 | data[3]);
	raw_z = (int16_t)(data[4] << 8 | data[5]);

	/* Converting raw values into acceleration in terms of g.
	*  Scaling by the sensitivity for the configured scale range.*/

	Data.accel_x = raw_x / kAccelCorrector;
	Data.accel_y = raw_y / kAccelCorrector;
	Data.accel_z = raw_z / kAccelCorrector;

}

/* Private methods  ---------------------------------------------------------*/

MPU6050::MPU6050(){
  HAL_I2C_Init(&hi2c1);
}

void MPU6050::IMUInit (void){
	//Use this for IMU set up
	uint8_t imu_check = 0, data_check = 0;
	HAL_StatusTypeDef wake = HAL_OK;


	//Check if device is present and the IMU is the expected device

		if (HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, WHO_AM_I, 1, &imu_check, 1, HAL_MAX_DELAY) == HAL_OK && imu_check == kImuAddr){

				//Wake the sensor up
				wake = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, PWR_MGMT_1, 1, &data_check, 1, HAL_MAX_DELAY);

				data_check = 0x07;
				HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, SMPLRT_DIV, 1, &data_check, 1, HAL_MAX_DELAY);

				//Configure gyro to have range of +/- 250 dps
				data_check = 0x00;
				HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, GYRO_CONFIG, 1, &data_check, 1, HAL_MAX_DELAY);

				//Configure Accelerometer to have range of +/- 2g
				data_check = 0x00;
				HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, ACCEL_CONFIG, 1, &data_check, 1, HAL_MAX_DELAY);
			}



}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/