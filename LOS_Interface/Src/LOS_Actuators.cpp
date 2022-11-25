#include "LOS_Actuators.hpp"
#include "config.hpp"

Los_Actuators& Los_Actuators::getInstance()
{
    static Los_Actuators singleton;
    return singleton;
}

Los_Actuators::Los_Actuators() {}

void Los_Actuators::set(uint8_t channel, uint8_t percent) {
    if (channel >= NUM_ACTUATOR_CHANNELS) 
        return;

    motor_channels_[channel]->set(percent);
}