/*
 * imu.cpp
 *
 *  Created on: May 24, 2022
 *      Author: anthony
 */

/* Includes ------------------------------------------------------------------*/
#include "BMX160.hpp"
#include "I2C_Mock.hpp"
//#include <Inc/LOS_Link.hpp>
#include <cstdint>
#include <math.h>

/* Private define ------------------------------------------------------------*/

/* BMX160 Relevant Registers
 Taken from datasheet: https://www.mouser.com/pdfdocs/BST-BMX160-DS000-11.pdf
 */


static constexpr uint8_t IMU_DUMMY_ADDRESS = 0x1E;

static constexpr uint8_t BMX160_I2C_ADDR = (0x68 << 1); // Left-aligned slave address

static constexpr uint8_t MAX_BUFF_SIZE = 21;

// From datasheet - last four bits (1011 indicates a sampling rate of 800 Hz)
// The first four bits indicate OSR4 - data is sampled at an oversampling rate of 4
static uint8_t ACC_ODR_800_OSR4 = 0x0B; // 0b00001011

static uint8_t GYRO_RANGE_1000 = 0x01;

// From datasheet - last four bits (1011 indicates a sampling rate of 800 Hz)
// The first four bits indicate OSR4 - data is sampled at an oversampling rate of 4
static uint8_t GYRO_ODR_800_OSR4 = 0x0B; // 0b00001011
static uint8_t REP_Z_REGULAR_PRESET = 0x0E;

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

/* Private variables ---------------------------------------------------------*/
I2C_Comms methods;
 /* Private Methods ---------------------------------------------------------*/

uint8_t AccBuffer[5]; 
AccBuffer[0] = 0x40;
AccBuffer[1] = 0x41;
AccBuffer[2] = 0x11;
AccBuffer[3] = 0x08;
AccBuffer[4] = 0x0B;

uint8_t GyroBuffer[5];
GyroBuffer[0] = 0x42;
GyroBuffer[1] = 0x43;
GyroBuffer[2] = 0x15;
GyroBuffer[3] = 0x01;
GyroBuffer[4] = 0x0B;

uint8_t MagBuffer[17];
MagBuffer[0]  = 0x44;
MagBuffer[1]  = 0x4C;
MagBuffer[2]  = 0x4D;
MagBuffer[3]  = 0x4E;
MagBuffer[4]  = 0x4F;
MagBuffer[5]  = 0x52;
MagBuffer[6]  = 0x51;
MagBuffer[7]  = 0x4B;
MagBuffer[8]  = 0x19;
MagBuffer[9]  = 0x80;
MagBuffer[10] = 0x00;
MagBuffer[11] = 0x02;
MagBuffer[12] = 0x4C;
MagBuffer[13] = 0x42;
MagBuffer[14] = 0x09;
MagBuffer[15] = 0x07;
MagBuffer[16] = 0x01;

uint8_t Registers[4];
Registers[0] = 0x04;
Registers[1] = 0x1B;
Registers[2] = 0x7E;
Registers[3] = 0x03; 

rawImuData[0] = 100;
rawImuData[2] = 100;
rawImuData[4] = 100;
rawImuData[6] = 50;
rawImuData[8] = 50;
rawImuData[10] = 50;
rawImuData[12] = 50;
rawImuData[14] = 1000;
rawImuData[16] = 1000;
rawImuData[18] = 1000;

void IMUMock::configAcc() {
	// Configure acceleration sampling rate as 800 Hz and every four are averaged
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &AccBuffer[0], 1);
	
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, ACC_CONF_REG,
	//		I2C_MEMADD_SIZE_8BIT, &ACC_ODR_800_OSR4, 1, HAL_MAX_DELAY);

	// Configure accelerometer to have range of +- 8g
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &AccBuffer[3], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, ACC_RANGE_REG,
	//		I2C_MEMADD_SIZE_8BIT, &ACC_RANGE_8G, 1, HAL_MAX_DELAY);
}

void IMUMock::configGyro() {
	// Configure gyro sampling rate as 800 Hz and every four samples are averaged
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, GYR_CONF_REG,
	//		I2C_MEMADD_SIZE_8BIT, &GYRO_ODR_800_OSR4, 1, HAL_MAX_DELAY);

	// Configure gyroscope to have a range of +- 1000 deg/s
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[3], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, GYR_RANGE_REG,
	//		I2C_MEMADD_SIZE_8BIT, &GYRO_RANGE_1000, 1, HAL_MAX_DELAY);
}

void IMUMock::configMag() {

	/*
	 Steps for Magnetometer Configuration:
	 1.) Put Mag into normal power mode (Already there since that was called before)
	 2.) Wait 650 us
	 3.) Write 0x80 to 0x4C (MAG_IF[0]) - set Mag into setup mode - done
	 4.) Write 0x01 to 0x4F (MAG_IF[3]) and 0x4B to 0x4E (MAG_IF[2]) - put mag into sleep mode - done
	 5.) Write 0x04 to 0x4F (MAG_IF[3]) and 0x51 to 0x4E (MAG_IF[2]) - put mag in regular preset mode - done
	 6.) Write 0x0E to 0x4F (MAG_IF[3]) and 0x52 to 0x4E (MAG_IF[2]) - done
	 7.) Write 0x02 to 0x4F, 0x4C to 0x4E, and 0x42 to 0x4D - prepare MAG_IF[0:3] for mag_if_data mode - done
	 8.) Write 0x__ to MAG_CONF_REG to set ODR to 800 Hz - done
	 9.) Write 0x00 to 0x4C
	 */
	HAL_Delay(650);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &MagBuffer[9], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_0_REG,
	//		I2C_MEMADD_SIZE_8BIT, &MAG_SETUP_EN, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &MagBuffer[16], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_3_REG,
	//		I2C_MEMADD_SIZE_8BIT, &MAG_SLEEP_MODE, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_2_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_MODE_REG, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_3_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &REP_XY_REGULAR_PRESET, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_2_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_REPXY_REG, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_3_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &REP_Z_REGULAR_PRESET, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_2_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_REPZ_REG, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_3_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_IF_3_DATA_MODE, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_2_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_IF_2_DATA_MODE, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_1_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_IF_1_DATA_MODE, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_CONF_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_REFRESH_50_HZ, 1, HAL_MAX_DELAY);
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[4], 1);
	// HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, MAG_IF_0_REG,
	// 		I2C_MEMADD_SIZE_8BIT, &MAG_SETUP_DIS, 1, HAL_MAX_DELAY);

}

// Nothing to scan, return true
bool IMUMock::scan() {
	return true;
}

// Calibrates IMU so that any drift or offset is accounted for
void IMUMock::calibrate(void) {
	const int nSamplesForReliableAverage = 100;
	IMUData_t TempImuData;
	IMUData_t TempImuCalibration;

	TempImuCalibration.accel_x = 0.0f;
	TempImuCalibration.accel_y = 0.0f;
	TempImuCalibration.accel_z = 0.0f;
	TempImuCalibration.gyro_x = 0.0f;
	TempImuCalibration.gyro_y = 0.0f;
	TempImuCalibration.gyro_z = 0.0f;
	TempImuCalibration.mag_x = 0.0f;
	TempImuCalibration.mag_y = 0.0f;
	TempImuCalibration.mag_z = 0.0f;

	for (int i = 0; i < nSamplesForReliableAverage; i++) {
		this->updateData();

		HAL_Delay(7);

		this->GetResult(TempImuData);

		TempImuCalibration.gyro_x += TempImuData.gyro_x;
		TempImuCalibration.gyro_y += TempImuData.gyro_y;
		TempImuCalibration.gyro_z += TempImuData.gyro_z;

	}

	// TempImuCalibration.accel_x /= (float) nSamplesForReliableAverage;
	// TempImuCalibration.accel_y /= (float) nSamplesForReliableAverage;
	// TempImuCalibration.accel_z /= (float) nSamplesForReliableAverage;

	// // the normalization factor needs to normalize no motion relative to the earth at 1g (1000mg)
	// float norm = 1000 / sqrtf(TempImuCalibration.accel_x * TempImuCalibration.accel_x
	// 						+ TempImuCalibration.accel_y * TempImuCalibration.accel_y
	// 						+ TempImuCalibration.accel_z * TempImuCalibration.accel_z);

	// IMUCalibration.accel_x = norm;
	// IMUCalibration.accel_y = norm;
	// IMUCalibration.accel_z = norm;

	IMUCalibration.gyro_x = TempImuCalibration.gyro_x
			/ (float) nSamplesForReliableAverage;
	IMUCalibration.gyro_y = TempImuCalibration.gyro_y
			/ (float) nSamplesForReliableAverage;
	IMUCalibration.gyro_z = TempImuCalibration.gyro_z
			/ (float) nSamplesForReliableAverage;

}

// /* Public Methods  ---------------------------------------------------------*/

IMU& IMUMock::getInstance() {
	// static BMX160 singleton;
	// return singleton;
}

void IMUMock::updateData(void) {
	// Just updates the rawIMUData and conducts some processing on it
	if !(rawImuData[0] > 1.1) {
		rawImuData[0] = sqrt(rawImuData[0]);
		rawImuData[2] = sqrt(rawImuData[2]);
		rawImuData[4] = sqrt(rawImuData[4]);
		rawImuData[6] = sqrt(rawImuData[6]);
		rawImuData[8] = sqrt(rawImuData[8]);
		rawImuData[10] = sqrt(rawImuData[10]);
		rawImuData[12] = sqrt(rawImuData[12]);
		rawImuData[14] = sqrt(rawImuData[14]);
		rawImuData[16] = sqrt(rawImuData[16]);
		rawImuData[18] = sqrt(rawImuData[18]);
	}
	methods.I2C_Receive(IMU_DUMMY_ADDRESS, &Registers[0], rawImuData, 20, 1);
	//HAL_I2C_Mem_Read(&hi2c1, BMX160_I2C_ADDR, DATA_REG, I2C_MEMADD_SIZE_8BIT,
	//		rawImuData, 20, HAL_MAX_DELAY);
}

void IMUMock::GetResult(IMUData_t &Data) {
	// // The 15:8 and 7:0 bits are in different registers. The bitmasking below joins them into one 16 bit integer
	this->updateData();
	int16_t magx = rawImuData[0];
	int16_t magy = rawImuData[2];
	int16_t magz = rawImuData[4];
	int16_t rhall = rawImuData[6];
	int16_t gyrx = rawImuData[8];
	int16_t gyry = rawImuData[10];
	int16_t gyrz = rawImuData[12];
	int16_t accx = rawImuData[14];
	int16_t accy = rawImuData[16];
	int16_t accz = rawImuData[18];

	Data.mag_x = (static_cast<float>(magx) / MAG_ADJUST_FACTOR);
	Data.mag_y = (static_cast<float>(magy) / MAG_ADJUST_FACTOR);
	Data.mag_z = (static_cast<float>(magz) / MAG_ADJUST_FACTOR);

	Data.accel_x = (static_cast<float>(accx) / ACC_RANGE_8_FACTOR); //- IMUCalibration.accel_x;
	Data.accel_y = (static_cast<float>(accy) / ACC_RANGE_8_FACTOR); //- IMUCalibration.accel_y;
	Data.accel_z = (static_cast<float>(accz) / ACC_RANGE_8_FACTOR); //- IMUCalibration.accel_z;

	Data.gyro_x = (static_cast<float>(gyrx) / GYRO_RANGE_1000_FACTOR)
			- IMUCalibration.gyro_x;
	Data.gyro_y = (static_cast<float>(gyry) / GYRO_RANGE_1000_FACTOR)
			- IMUCalibration.gyro_y;
	Data.gyro_z = (static_cast<float>(gyrz) / GYRO_RANGE_1000_FACTOR)
			- IMUCalibration.gyro_z;
}

IMUMock::IMUMock() {
	IMUInit();
	this->calibrate(); // Calibrate IMU and populate callibration struct for use
}

void IMUMock::IMUInit(void) {
	if (scan()) {
		setAllPowerModesToNormal();
		configAcc();
		configGyro();
		configMag();
		methods.I2C_Receive(IMU_DUMMY_ADDRESS, &Registers[3], &powerStatus, 1, 1);
		//HAL_I2C_Mem_Read(&hi2c1, BMX160_I2C_ADDR, PMU_STATUS_REG,
		//		I2C_MEMADD_SIZE_8BIT, &powerStatus, 1, HAL_MAX_DELAY);
	} 
}

void IMUMock::setAllPowerModesToNormal() {

	// Set gyro to normal mode
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &GyroBuffer[2], 1); // Writing one byte 
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, CMD_REG, I2C_MEMADD_SIZE_8BIT,
	//		&GYRO_NORMAL_MODE_CMD, 1, HAL_MAX_DELAY);
	HAL_Delay(10);

	// Set accelerometer to normal mode
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &AccBuffer[2], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, CMD_REG, I2C_MEMADD_SIZE_8BIT,
	//		&ACC_NORMAL_MODE_CMD, 1, HAL_MAX_DELAY);
	HAL_Delay(10);

	// Set magnetometer to normal mode
	methods.I2C_Transmit(IMU_DUMMY_ADDRESS, &MagBuffer[8], 1);
	//HAL_I2C_Mem_Write(&hi2c1, BMX160_I2C_ADDR, CMD_REG, I2C_MEMADD_SIZE_8BIT,
	//		&MAG_NORMAL_MODE_CMD, 1, HAL_MAX_DELAY);
	HAL_Delay(10);

}
