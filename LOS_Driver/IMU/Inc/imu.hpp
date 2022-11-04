/*
 *imu.hpp
 *
 *  Created on: May 24, 2022
 *      Author: anthony
 */

#ifndef INC_IMU_HPP_
#define INC_IMU_HPP_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "i2c.h"
#include "driver_params.hpp"

/* Exported functions prototypes ---------------------------------------------*/
// void Error_Handler();
struct IMUData_t {
	double gyro_x, gyro_y, gyro_z;
	double accel_x, accel_y, accel_z;
	double mag_x, mag_y, mag_z;
};

class IMU {
public:
	virtual void GetResult(IMUData_t &Data) = 0;
};

#endif /* INC_IMU_HPP_ */