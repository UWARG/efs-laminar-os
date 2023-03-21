#ifndef RC_SENDER_HPP_
#define RC_SENDER_HPP_

#include <cstdint>
#include "main.h"

class RcSender {
    public:
        /* Set the value of a specific channel (0-100). Returns 1 if success, 0 if failed. */
        virtual uint8_t setChannelValue(uint8_t channel, uint8_t value) = 0;

        /* Initialize the RC output. */
        virtual void init() = 0;

        /* A callback that gets called after each RC value is sent. */
        virtual void interrupt_callback(TIM_HandleTypeDef* timer) = 0;
};

#endif