#include "driver_params.hpp"

TIM_HandleTypeDef *PWM_TIM = &htim3;
TIM_HandleTypeDef *DSHOT_TIM = &htim1;

/* PPM */
TIM_HandleTypeDef *PPM_TIM = &htim2;
