/*
 * LOS_Link.cpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */




// #include "../../Drivers/Comms/Inc/PPM.hpp"
#include "../Inc/LOS_Link.hpp"
#include "../../Drivers/Comms/Inc/RSSI.hpp"

LOS_Link::LOS_Link(uint8_t channels) {
    this->ppm = new PPMChannel(channels);
    // PPMChannel *ppm = new PPMChannel(channels);
}

Teleop_Instructions_t LOS_Link::get_inputs(){
    Teleop_Instructions_t instructions;
    for(uint8_t i=0; i<8; ++i) {
        instructions.teleop_inp[i] = this->ppm->get(i);
    }
}

uint8_t LOS_Link::get_input(int channel) {
    return this->ppm->get(channel);
}

bool LOS_Link::disconnected(uint32_t sys_time){
	return this->ppm->is_disconnected(sys_time);
}
