#ifndef RC_RECIEVER_HPP_
#define RC_RECIEVER_HPP_

#include <cstdint>

class RC_Receiver{
    public:
        virtual uint8_t GetResult(uint8_t channel) = 0;
};

#endif