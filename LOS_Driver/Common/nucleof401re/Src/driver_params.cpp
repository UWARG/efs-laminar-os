#include "driver_params.hpp"
#include "config.hpp"

TIM_HandleTypeDef *PWM_TIM = &htim3;
TIM_HandleTypeDef *DSHOT_TIM = &htim1;

/* PPM */
TIM_HandleTypeDef *PPM_TIM = &htim2;

/* Actuators */
const int NUM_ACTUATOR_CHANNELS = 1;