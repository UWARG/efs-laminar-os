#ifndef LOS_LINK_HPP_
#define LOS_LINK_HPP_

#include "interface_datatypes.hpp"
#include "RcReceiver.hpp"
#include "PPM.hpp"

class Los_Link{

    public:
        Los_Link();
        
        LosLinkRx_t getRx(void);

    private:
        RcReceiver *rc_receiver;

        void init(void);

};

#endif