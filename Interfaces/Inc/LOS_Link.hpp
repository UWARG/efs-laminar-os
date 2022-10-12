/*
 * LOS_Link.hpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */

#ifndef INC_LOS_LINK_HPP_
#define INC_LOS_LINK_HPP_

#include "../../Drivers/Actuators/Inc/PWM.hpp"
#include "../../Drivers/Comms/Inc/PPM.hpp"
#include "../Inc/interface_datatypes.hpp"

class LOS_Link {
    public:
        /**
         * @brief Construct a new los link object
         * 
         * @param num_channels 8 if not provided
         */
        LOS_Link(uint8_t num_channels = 8);

        
        /**
         * @brief Returns a percent value that was most recently received from all channels
         * Percentage 0-100.
         * 
         * @param num 
         * @return 0 if an invalid channel number was given.
         */
        Teleop_Instructions_t get_inputs();

        uint8_t get_input(int channel);

        bool disconnected(uint32_t sys_time);

    private:
        PPMChannel *ppm;
};



#endif /* INC_LOS_LINK_HPP_ */
