#ifndef MOTOR_CHANNEL_HPP_
#define MOTOR_CHANNEL_HPP_

#include <cstdint>

class MotorChannel {
    public:
        virtual void set(uint8_t percent) = 0;
};

#endif // MOTOR_CHANNEL_HPP_