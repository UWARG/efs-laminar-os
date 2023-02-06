#include "LOS_D_GenericCommsDevice.hpp"


void GenericCommsDevice::transmit(uint8_t* buf, int size) {
    HAL_UART_Transmit_DMA(this->uart,buf, size);

}
void GenericCommsDevice::receive(uint8_t* buf, int max_size) {
    uint8_t bytePtr = 0;
    // read from freertos queue and put in the buffer
    for (int x = 0; x < max_size; x++) {
        if(this->queue != NULL) {
           if( xQueueReceive( this->queue, &bytePtr,( TickType_t ) 10 ) != pdPASS ) {
               return;
           }

           buf[x] = bytePtr;

        }
    }
}

void GenericCommsDevice::Callback(volatile uint8_t* buf, uint16_t size) {
    for (int x = 0; x < size; x++) {
        uint8_t byte = buf[x];
        if (xQueueSendFromISR(this->queue, &byte,pdFALSE) != pdTRUE){
            // queue is full
            return;
        }
    }
}

bool GenericCommsDevice::matchUART(UART_HandleTypeDef* huart) {
    if(huart != NULL) {
        return huart->Instance == this->uart->Instance;
    }
    return false;
}