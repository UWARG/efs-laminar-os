#ifndef LOS_D_GENERIC_COMMS_DEVICE_HPP
#define LOS_D_GENERIC_COMMS_DEVICE_HPP

#include <cstdint>
#include "usart.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "CircularBuffer.hpp"

class GenericCommsDevice {
    public: 
        void transmit(uint8_t* buf, int size, UART_HandleTypeDef* huart);
        void receive(CircularBuffer buf, QueueHandle_t queue);
        GenericCommsDevice(); 
        void Callback(volatile uint8_t* buf, uint16_t size, QueueHandle_t queue);
        bool matchUART(UART_HandleTypeDef* huartA,UART_HandleTypeDef* huartB);
        void startInterrupt(UART_HandleTypeDef* huart, uint8_t* buf, int size);

    private:
        // QueueHandle_t queue; 
        // UART_HandleTypeDef* uart = NULL;
        bool bufferUsed = false;


};


#endif