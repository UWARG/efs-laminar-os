#ifndef PWM_CHANNEL_HPP_
#define PWM_CHANNEL_HPP_

#include "main.h"
#include "MotorChannel.hpp"

class PWMChannel : public MotorChannel {
    public:
        PWMChannel(uint16_t pinNum, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, uint16_t timerChannel);

        void set(uint8_t percent);
    private:
        uint16_t num;
        GPIO_TypeDef* port;           
        TIM_HandleTypeDef *timer;     //handle to the timer
        uint16_t timer_channel;       //channel of the timer

        //values in us
        static const uint32_t PWM_PERIOD = 20000;
        static const uint32_t MIN_SIGNAL = 950; //standard for 50hz pwm signal, with a 100 Hz margin added to ensure we can reach the extreme values.
        static const uint32_t MAX_SIGNAL = 2050;

};

#endif // PWM_CHANNEL_HPP_