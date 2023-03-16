#ifndef LOS_TELEM_HPP_
#define LOS_TELEM_HPP_

#include <cstdint>
#include "config.hpp"

class Los_Telem{

    public:
        Los_Telem(const Los_Telem*) = delete;

        static Los_Telem& getInstance(void);
        void init();

        void transmit(uint8_t* buf, int size);
        void receive(CircularBuffer& buf);

        volatile uint8_t telem_buffer[TELEM_BUFFER_SIZE] = { 0 };

    private:
        Los_Telem();
};

#endif