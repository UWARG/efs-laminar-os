#ifndef LOS_D_AIRCOMMS_HPP_
#define LOS_D_AIRCOMMS_HPP_

#include <cstdint>

class AirComms{
    public:
        virtual uint8_t GetResult(uint8_t* buffer, uint8_t length) = 0;


#endif /* LOS_D_AIRCOMMS_HPP_ */