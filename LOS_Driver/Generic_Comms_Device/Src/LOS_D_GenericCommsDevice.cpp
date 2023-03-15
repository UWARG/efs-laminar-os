#include "LOS_D_GenericCommsDevice.hpp"
#include "main.h"

void GenericCommsDevice::startInterrupt(UART_HandleTypeDef* huart, uint8_t* buf, int size) {
    HAL_UARTEx_ReceiveToIdle_DMA(huart, buf, size);
	__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
}

void GenericCommsDevice::transmit(uint8_t* buf, int size, UART_HandleTypeDef* huart) {
    HAL_UART_Transmit_DMA(huart,buf, size);
}

GenericCommsDevice::GenericCommsDevice() {}

void GenericCommsDevice::receive(CircularBuffer buf, QueueHandle_t queue) {
    uint8_t currByte = 0;

    while(buf.hasSpace()) { // make sure theres space in the buffer
        if( xQueueReceive(queue, &currByte,( TickType_t ) 10 ) != pdPASS ) {
            // queue is probably empty
            return; 
        }
        buf.write(currByte);
    }
}

void GenericCommsDevice::Callback(volatile uint8_t* buf, uint16_t size, QueueHandle_t queue) {
    for (int x = 0; x < size; x++) {
        uint8_t byte = buf[x];
        if (xQueueSendFromISR(queue, &byte,pdFALSE) != pdTRUE){
            // queue is full
            return;
        }
    }
}

bool GenericCommsDevice::matchUART(UART_HandleTypeDef* huartA, UART_HandleTypeDef* huartB) {
    if(huartA != NULL && huartB != NULL) {
        return huartA->Instance == huartB->Instance;
    }
    return false;
}
