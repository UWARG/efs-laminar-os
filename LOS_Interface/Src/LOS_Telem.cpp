#include "LOS_Telem.hpp"
#include "config.hpp"


Los_Telem& Los_Telem::getInstance()
{
    static Los_Telem singleton;
    return singleton;
}

Los_Telem::Los_Telem(){}

void Los_Telem::transmit(uint8_t* buf, int size) {
    telem_driver.transmit(buf, size, telem_uart);
}

void Los_Telem::receive(uint8_t* buf, int max_size, int& writePtr, int readPtr) {
    return telem_driver.receive(buf,max_size, writePtr, readPtr, comms_queue);
}

void Los_Telem::init() {
    telem_queue = xQueueCreate(COMMS_QUEUE_SIZE,sizeof(uint8_t));
    telem_driver.startInterrupt(telem_uart, (uint8_t*)telem_buffer, sizeof(telem_buffer));
}