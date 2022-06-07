/*
 * LOS_Link.cpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */




// #include "../../Drivers/Comms/Inc/PPM.hpp"
#include "../Inc/LOS_Link.hpp"

LOS_Link &LOS_Link::getInstance() {
    static LOS_Link instance;
    return instance;
}

LOS_Link::LOS_Link() {
    uint8_t NUM_CHANNELS = 8;
    this->ppm = new PPMChannel(NUM_CHANNELS);
    // PPMChannel *ppm = new PPMChannel(channels);
}

Instructions_t LOS_Link::get_inputs(){
    Instructions_t instructions;
    for(uint8_t i=0; i<8; ++i) {
        instructions.input[i] = this->ppm->get(i);
    }
}