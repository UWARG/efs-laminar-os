#include "DSHOTChannel.hpp"

DSHOTChannel::DSHOTChannel(uint16_t pinNum, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, uint16_t timerChannel, uint16_t timDMAHandleIndex, uint16_t timDMASource) : pinNum(pinNum), port(port), timer(timer), timerChannel(timerChannel), timDMAHandleIndex(timDMAHandleIndex), timDMASource(timDMASource) {
    HAL_TIM_PWM_Start(timer, timer_channel);

    prepareDMABuffer(0); //init buffer for 0 percent throttle
    startDMA(); //start DMA... it should never be stopped after this bec it is in circular mode
    enableDMARequests();
}

void DSHOTChannel::set(uint8_t percent) {
    prepareDMABuffer(percent);
}

uint16_t DSHOTChannel::prepareFrame(uint8_t throttlePercentage, bool telemetry) {
    /* DSHOT data frame (16 bits total):
     *
     *           b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15
     *           |-------------------------------| |-| |-------------| 
     *                      Throttle Data           ^     Checksum
     *                                              |
     *                                           Telemetry
     */

    uint16_t frame;

    frame = (((uint16_t)(DSHOT_MAX_THROTTLE * (float)throttlePercentage / 100) + DSHOT_RESERVED_VALUES) << 1) | (telemetry ? 1 : 0); //throttle and telemetry bits

    uint8_t checksum = (frame ^ (frame >> 4) ^ (frame >> 8)) & 0x00F; //calculating checksum... splitting first 12 bits into 3 nibbles and XORing

    frame = (frame << 4) | checksum; //adding the checksum to the frame
    
    return frame;
}

void DSHOTChannel::prepareDMABuffer(uint8_t throttlePercentage) {
    uint16_t frame = prepareFrame(throttlePercentage, false);

    for (int i = 0; i < DSHOT_DATA_FRAME_LEN; i++)
    {
        //Using the frame, populate the buffer with the duty cycle value corresponding to a 1 and 0
        //We are masking out everything except the most significant bit (far left bit) and setting the proper value in the buffer depending if it's a 1 or 0
        dmaBuffer[i] = (frame & 0x8000 ? DSHOT_150_BIT_1 : DSHOT_150_BIT_0);

        //Left shifting the current frame over by 1 to set the next frame bit in the buffer
        frame <<= 1;
    }

    //Setting the last two indexes in the buffer to 0 to ensure the last part of the signal is low
    dmaBuffer[16] = 0;
    dmaBuffer[17] = 0;
}

void DSHOTChannel::startDMA() {
    uint32_t destinationBuffer;

    switch (timer_channel) {
        case TIM_CHANNEL_1:
            destinationBuffer = (uint32_t)&timer->Instance->CCR1;
            break;
        case TIM_CHANNEL_2:
            destinationBuffer = (uint32_t)&timer->Instance->CCR2;
            break;
        case TIM_CHANNEL_3:
            destinationBuffer = (uint32_t)&timer->Instance->CCR3;
            break;
        case TIM_CHANNEL_4:
            destinationBuffer = (uint32_t)&timer->Instance->CCR4;
            break;
    }
    HAL_DMA_Start(timer->hdma[timDMAHandleIndex], (uint32_t)dmaBuffer, destinationBuffer, DSHOT_DMA_BUFFER_SIZE);
}

void DSHOTChannel::enableDMARequests() {
    __HAL_TIM_ENABLE_DMA(timer, timDMASource); 
}
