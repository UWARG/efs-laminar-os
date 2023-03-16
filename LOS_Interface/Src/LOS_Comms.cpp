#include "LOS_Comms.hpp"
#include "config.hpp"


Los_Comms& Los_Comms::getInstance()
{
    static Los_Comms singleton;
    return singleton;
}

Los_Comms::Los_Comms(){}

void Los_Comms::transmit(uint8_t* buf, int size) {
    comms_driver.transmit(buf, size, comms_uart);
}

void Los_Comms::receive(CircularBuffer& buf) {
    return comms_driver.receive(buf, comms_queue);
}

void Los_Comms::init() {
    comms_queue = xQueueCreate(COMMS_QUEUE_SIZE,sizeof(uint8_t));
    comms_driver.startInterrupt(comms_uart, (uint8_t*)comms_buffer, sizeof(comms_buffer));
}
