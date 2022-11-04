#ifndef INTERFACE_TEMP_PARAMS_HPP_
#define INTERFACE_TEMP_PARAMS_HPP_

#include "main.h"
#include "tim.h"
#include <cstdint>

extern TIM_HandleTypeDef *PWM_TIM;
extern TIM_HandleTypeDef *DSHOT_TIM;

/* PPM Driver */
extern TIM_HandleTypeDef *PPM_TIM;
#define PPM_TIME_BASE TIM2
#define PPM_TIM_CHANNEL TIM_CHANNEL_1


#endif /* INTERFACE_TEMP_PARAMS_HPP_ */