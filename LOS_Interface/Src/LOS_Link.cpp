#include "LOS_Link.hpp"

Los_Link& Los_Link::getInstance()
{
    static Los_Link singleton;
    return singleton;
}

Los_Link::Los_Link(){
    for (uint8_t instance = 0; instance < NUM_RC_RECEIVER_INSTANCES; ++instance) {
        rc_receivers_[instance]->init();
    }

    for (uint8_t instance = 0; instance < NUM_RC_SENDER_INSTANCES; ++instance) {
        rc_senders_[instance]->init();
    }
}

LosLinkRx_t Los_Link::getRx(uint8_t instance)
{
    LosLinkRx_t rx_data;

    for (uint8_t channel = 0; channel < NUM_RX_CHANNELS; ++channel) {
        rx_data.rx_channels[channel] = rc_receivers_[instance]->GetResult(channel);
    }

    rx_data.rssi = 0; //RSSI has not been implemented so it will be set to 0

    return rx_data;
}

uint8_t Los_Link::sendTx(uint8_t instance, LosLinkTx_t &tx_data)
{
    uint8_t success = 1;

    for (uint8_t channel = 0; channel < NUM_TX_CHANNELS; ++channel) {
        success &= rc_senders_[instance]->setChannelValue(channel, tx_data.tx_channels[channel]);
    }

    return success;
}
