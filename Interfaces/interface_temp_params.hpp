/*
 * interface_temp_params.hpp
 *
 *  Created on: May 24, 2022
 *      Author: anthony
 */

#ifndef INTERFACE_TEMP_PARAMS_HPP_
#define INTERFACE_TEMP_PARAMS_HPP_


#include "main.h"
#include "tim.h"

TIM_HandleTypeDef *PWM_TIM = &htim3;
TIM_HandleTypeDef *DSHOT_TIM = &htim1;


#endif /* INTERFACE_TEMP_PARAMS_HPP_ */
