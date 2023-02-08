#ifndef LOS_D_GENERIC_COMMS_DEVICE_HPP
#define LOS_D_GENERIC_COMMS_DEVICE_HPP

#include <cstdint>
#include "usart.h"
#include "FreeRTOS.h"
#include "queue.h"

class GenericCommsDevice {
    public: 
        void transmit(uint8_t* buf, int size);
        void receive(uint8_t* buf, int max_size, int* writePtr, int readPtr);
        GenericCommsDevice(UART_HandleTypeDef* pUart, QueueHandle_t pQueue) : uart{ pUart }, queue{ pQueue } {}
        void Callback(volatile uint8_t* buf, uint16_t size);
        bool matchUART(UART_HandleTypeDef* huart);

    private:
        QueueHandle_t queue; 
        UART_HandleTypeDef* uart;


};

const int DATA_BUFFER_SIZE = 50;

struct CommsData {
    uint8_t buf[DATA_BUFFER_SIZE];
    int size;
};

#endif