#include "LOS_Comms.hpp"
#include "config.hpp"


Los_Comms& Los_Comms::getInstance()
{
    static Los_Comms singleton;
    return singleton;
}

Los_Comms::Los_Comms(){}

void Los_Comms::transmit(uint8_t* buf, int size) {
    comms_driver.transmit(buf, size);
}

void Los_Comms::recieve(uint8_t* buf, int max_size) {
    comms_driver.receive(buf,max_size);
}