#ifndef LOS_D_MOTOR_CHANNEL_HPP_
#define LOS_D_MOTOR_CHANNEL_HPP_

#include <cstdint>

class MotorChannel {
    public:
        virtual void set(uint8_t percent) = 0;
};

#endif // LOS_D_MOTOR_CHANNEL_HPP_