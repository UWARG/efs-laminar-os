#ifndef LOS_COMMS_HPP_
#define LOS_COMMS_HPP_

#include <cstdint>

class Los_Comms{

    public:
        Los_Comms(const Los_Comms*) = delete;

        static Los_Comms& getInstance(void);

        void transmit(uint8_t* buf, int size);
        void receive(uint8_t* buf, int max_size, int* writePtr, int readPtr);

    private:
        Los_Comms();
};

#endif