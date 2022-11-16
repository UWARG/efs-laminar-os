#include "LOS_Link.hpp"

Los_Link& Los_Link::getInstance()
{
    static Los_Link singleton;
    return singleton;
}

Los_Link::Los_Link()
{
    #ifdef PPM
    PPMChannel losLinkInstance = PPMChannel(); //TODO: THIS WILL NOT WORK BEC THE INSTANCE WILL BE DESTROYED ONCE IT
                                               //      IS OUT OF SCOPE. FIND A PLACE TO MAKE IT GLOBAL/ A DIFFERNT METHOD.
    #endif
    
    rc_receiver = &losLinkInstance;
}

LosLinkRx_t Los_Link::getRx(void)
{
    LosLinkRx_t rx_data;

    for (uint8_t channel = 0; channel < NUM_RX_CHANNELS; channel++)
    {
        rx_data.rx_channels[channel] = rc_receiver->GetResult(channel);
    }

    rx_data.rssi = 0; //RSSI has not been implemented so it will be set to 0

    return rx_data;
}

void Los_Link::init(void)
{
    //Does nothing, no initialization of the PPM driver needs to occur
}