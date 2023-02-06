#include "main.h"
#include "config.hpp"

#include <cstdint>


volatile uint8_t comms_buffer[COMMS_BUFFER_SIZE];
volatile uint8_t telem_buffer[TELEM_BUFFER_SIZE];

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {

	if(comms_driver.matchUART(huart)) {
        // put data into queue
        comms_driver.Callback(comms_buffer, size);

        // listen for more data
		HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) comms_buffer, sizeof(comms_buffer));
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}

	if(telem_driver.matchUART(huart)) {
        // put data into queue
        telem_driver.Callback(telem_buffer, size);

        // listen for more data
		HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) telem_buffer, sizeof(telem_buffer));
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}
}