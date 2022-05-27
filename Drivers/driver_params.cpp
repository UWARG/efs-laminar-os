/*
 * driver_params.cpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */


#include "driver_params.hpp"




TIM_HandleTypeDef *PWM_TIM = &htim3;
TIM_HandleTypeDef *DSHOT_TIM = &htim1;

TIM_HandleTypeDef *PPM_TIM = &htim2;
