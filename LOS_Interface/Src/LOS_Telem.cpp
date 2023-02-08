#include "LOS_Telem.hpp"
#include "config.hpp"


Los_Telem& Los_Telem::getInstance()
{
    static Los_Telem singleton;
    return singleton;
}

Los_Telem::Los_Telem(){}

void Los_Telem::transmit(uint8_t* buf, int size) {
    telem_driver.transmit(buf, size);
}

void Los_Telem::receive(uint8_t* buf, int max_size, int* writePtr, int readPtr) {
    return telem_driver.receive(buf,max_size, writePtr, readPtr);
}