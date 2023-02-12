#ifndef RC_SENDER_HPP_
#define RC_SENDER_HPP_

#include <cstdint>
#include "main.h"

class RcSender {
    public:
        virtual uint8_t setChannelValue(uint8_t channel, float value) = 0;
        virtual void init() = 0;
        virtual void interrupt_callback(TIM_HandleTypeDef* timer) = 0;
};

#endif