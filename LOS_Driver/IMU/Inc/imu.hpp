/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IMU_HPP
#define IMU_HPP


/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "i2c.h"
#include "main.h"

/* Exported functions prototypes ---------------------------------------------*/
// void Error_Handler();

struct IMUData_t {
  double gyro_x, gyro_y, gyro_z;
  double accel_x, accel_y, accel_z;
  double mag_x, mag_y, mag_z;
};

class IMU {
  public:
    virtual void GetResult(IMUData_t& Data) = 0;
};

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
