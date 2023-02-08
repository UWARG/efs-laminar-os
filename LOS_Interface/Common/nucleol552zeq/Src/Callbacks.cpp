#include "main.h"
#include "config.hpp"
#include "LOS_Comms.hpp"
#include "LOS_Telem.hpp"

#include <cstdint>




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {

	if(comms_driver.matchUART(huart)) {
        // put data into queue
        comms_driver.Callback(Los_Comms::getInstance().comms_buffer, size);

        // listen for more data
		HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) Los_Comms::getInstance().comms_buffer, sizeof(Los_Comms::getInstance().comms_buffer));
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}

	if(telem_driver.matchUART(huart)) {
        // put data into queue
        telem_driver.Callback(Los_Telem::getInstance().telem_buffer, size);

        // listen for more data
		HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *) Los_Telem::getInstance().telem_buffer, sizeof(Los_Telem::getInstance().telem_buffer));
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}
}