#ifndef LOS_D_JETSONCOMMS_HPP_
#define LOS_D_JETSONCOMMS_HPP_

#include "LOS_D_AirComms.hpp"
#include "main.h"

class JetsonComms: public AirComms{

    public:
        /**
         * @brief JetsonComms constructor
         * 
         * @param uart Uart peripheral handle being used
         * @param uart_dma_handle_index UART DMA index
         */
        JetsonComms(UART_HandleTypeDef* uart, uint16_t uart_dma_handle_index);
        
        /**
         * @brief Get new data from the local ring buffer
         * 
         * @param buffer Array to transfer the new data into
         * @param length Number of bytes to transfer
         * @return uint8_t Actual number of bytes transferred
         */
        uint8_t GetResult(uint8_t* buffer, uint8_t length);

    private:
        
        /**
         * @brief Dequeues certain about of bytes from the ring buffer
         * 
         * @param num_bytes Number of bytes to dequeue
         * @return true If the number of bytes was successfully dequeued
         * @return false If the number of bytes were unsuccessfully dequeued
         */
        bool dequeueBytes(uint8_t num_bytes);

        /**
         * @brief Queues a byte to the ring buffer
         * 
         * @param data Data to queue
         * @return true If the byte was successfully queued
         * @return false If the byte was unsuccessfully queued
         */
        bool queueByte(uint8_t data);

        /**
         * @brief Returns if the ring buffer is full or not
         * 
         * @return true If full
         * @return false If not full
         */
        bool isFull();

        /**
         * @brief Returns if the ring buffer is empty or not
         * 
         * @return true If empty
         * @return false If not empty
         */
        bool isEmpty();

        /**
         * @brief Interrupt call back when DMA is completed transferring incoming
         * UART data
         * 
         */
        void interrupt_callback();

        UART_HandleTypeDef* uart;
        uint16_t uart_dma_handle_index_;
        static constexpr uint8_t BUFFER_SIZE_ = 100;
        uint8_t interupt_buffer_[BUFFER_SIZE_];
        uint8_t ring_buffer_[BUFFER_SIZE_ * 5];
        uint8_t head;
        uint8_t tail;

};

#endif /* LOS_D_JETSONCOMMS_HPP_ */