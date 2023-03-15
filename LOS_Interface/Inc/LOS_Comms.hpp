#ifndef LOS_COMMS_HPP_
#define LOS_COMMS_HPP_

#include <cstdint>
#include "config.hpp"

class Los_Comms{

    public:
        Los_Comms(const Los_Comms*) = delete;

        static Los_Comms& getInstance(void);
        void init();

        void transmit(uint8_t* buf, int size);
        void receive(uint8_t* buf, int max_size, int& writePtr, int readPtr);

        volatile uint8_t comms_buffer[COMMS_BUFFER_SIZE] = { 0 };

    private:
        Los_Comms();
};

#endif