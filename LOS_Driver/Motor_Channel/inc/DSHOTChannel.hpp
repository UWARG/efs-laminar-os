#ifndef DSHOT_CHANNEL_HPP_
#define DSHOT_CHANNEL_HPP_

#include "PWMChannel.hpp"


class DSHOTChannel : public PWMChannel {
    public:
        DSHOTChannel(uint16_t pinNum, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, uint16_t timerChannel, uint16_t timDMAHandleIndex, uint16_t timDMASource);

        void set(uint8_t percent);
    private:
        static const int DSHOT_DATA_FRAME_LEN = 16;

        static const int DSHOT_DMA_BUFFER_SIZE      =  18;
        static const int DSHOT_MAX_THROTTLE         =  2000;
        static const int DSHOT_RESERVED_VALUES      =  47;
        static const int DSHOT_150_BIT_1            =  240;
        static const int DSHOT_150_BIT_0            =  120;

        volatile uint32_t dmaBuffer[DSHOT_DMA_BUFFER_SIZE];

        /**
        * @brief Prepares the Dshot data frame including the data, telemetry bit, and checksum
        * @param throttlePercentage Trottle percentage output from the PID loop, 0-100%
        * @param telemetry Bool indicating whether to set the telemetry bit or not
        * @retval 16 bit dshot data frame
        */    
        uint16_t prepareFrame(uint8_t throttlePercentage, bool telemetry);

        /**
        * @brief Prepares the DMA buffer using the data frame
        * @param frame DSHOT data frame
        * @retval None
        */    
        void prepareDMABuffer(uint8_t throttlePercentage);

        /**
        * @brief Starts DMA peripheral 
        * @retval None
        */
        void startDMA();

        /**
        * @brief Enables DMA request 
        * @retval None
        */
        void enableDMARequests();

};

#endif // DSHOT_CHANNEL_HPP_