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
#include "CommonDataTypes.hpp"

/* Exported functions prototypes ---------------------------------------------*/
// void Error_Handler();

class IMU {
public:
	virtual void GetResult(IMUData_t &Data) = 0;
};

#endif /* INC_IMU_HPP_ */