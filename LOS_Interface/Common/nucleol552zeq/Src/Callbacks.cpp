#include "main.h"
#include "config.hpp"
#include "LOS_Comms.hpp"
#include "LOS_Telem.hpp"
#include "stm32l5xx_hal.h"

#include <cstdint>


void HardFault_Handler(void)
{ 
   while(1); 
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {

}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart) {

}