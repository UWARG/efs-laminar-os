#ifndef LOS_LINK_HPP_
#define LOS_LINK_HPP_

#include "interface_datatypes.hpp"
#include "LOS_D_RcReceiver.hpp"
#include "LOS_D_PPMChannel.hpp"
#include "LOS_D_RcSender.hpp"
#include "LOS_D_PPMChannelOut.hpp"

class Los_Link{

    public:
        Los_Link(const Los_Link*) = delete;

        static Los_Link& getInstance(void);
        
        LosLinkRx_t getRx(uint8_t instance = 0);
        uint8_t sendTx(uint8_t instance, LosLinkTx_t &tx_data);

    private:
        Los_Link();
        
};

#endif