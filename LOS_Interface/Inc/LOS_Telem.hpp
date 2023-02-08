#ifndef LOS_TELEM_HPP_
#define LOS_TELEM_HPP_

#include <cstdint>

class Los_Telem{

    public:
        Los_Telem(const Los_Telem*) = delete;

        static Los_Telem& getInstance(void);

        void transmit(uint8_t* buf, int size);
        void receive(uint8_t* buf, int max_size, int* writePtr, int readPtr);

    private:
        Los_Telem();
};

#endif