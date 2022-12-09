#ifndef LOS_COMMS_HPP_
#define LOS_COMMS_HPP_

#include <stdint.h>
#include "interface_datatypes.hpp"

class Los_Comms{

    public:
        Los_Comms(const Los_Comms*) = delete;

        static Los_Comms& getInstance();

        /**
         * @brief This function transports all new data from the local circular buffer to
         * the circular buffer passed in.
         * 
         * @param input_ring_buffer buffer passed in to hold any new data
         * @param buffer_size size of the circular buffer
         * @param start_index index at which the first byte of data should be placed
         * 
         * @return number of actual bytes transferred
         */
        uint8_t getData(LosCommsRx_t* los_comms_rx);

    private:
        Los_Comms();
};

#endif // LOS_COMMS_HPP_