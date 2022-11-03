#include "LOS_Actuators.hpp"
#include "config.hpp"

Los_Actuators::Los_Actuators() {}

void Los_Actuators::set(uint8_t channel, uint8_t percent) {
    if (channel >= NUM_CHANNELS) 
        return;

    MOTOR_CHANNELS[channel]->set(percent);
}