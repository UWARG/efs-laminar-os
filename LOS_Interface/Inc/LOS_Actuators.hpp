#ifndef LOS_ACTUATORS_HPP_
#define LOS_ACTUATORS_HPP_

#include <stdint.h>

class Los_Actuators{

    public:
        Los_Actuators();
        
        void set(uint8_t channel, uint8_t percent);

};

#endif // LOS_ACTUATORS_HPP_