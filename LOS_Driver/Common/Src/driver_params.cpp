#include "driver_params.hpp"

TIM_HandleTypeDef *PWM_TIM = &htim3;
TIM_HandleTypeDef *DSHOT_TIM = &htim1;

/* PPM Driver */
TIM_HandleTypeDef *PPM_TIM = &htim2;

/* SD Card Driver */
SPI_HandleTypeDef* LOS_D_SD_SPI = &hspi2;