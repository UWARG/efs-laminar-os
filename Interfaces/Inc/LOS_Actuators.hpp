/*
 * LOS_Actuators.hpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */

#ifndef INC_LOS_ACTUATORS_HPP_
#define INC_LOS_ACTUATORS_HPP_

#include <stdint.h>
#include "../Inc/interface_datatypes.hpp"
#include "../../Drivers/Actuators/Inc/PWM.hpp"

class LOS_Actuators {
    public:
        /**
         * @brief Construct a new los actuators object
         * 
         */
        LOS_Actuators();

        /**
         * @brief sets individual channels.
         * 
         * @param channel 
         * @param percent 
         */
        void set(uint8_t channel, float percent);

        /**
         * @brief sets all 4 quad outputs.
         * 
         * @param quad_output 
         */
        void set(Quadrotor_Motor_out quad_output); // function that will just make it easier to get quad output
        
        /**
         * @brief Configure quadrotor motor outputs. Default is cw starting front_left
         * 
         * @param front_left 
         * @param front_right 
         * @param back_left 
         * @param back_right 
         */
        void __configure_quadrotor(uint8_t front_left=0, uint8_t front_right=1, uint8_t back_right=2, uint8_t back_left=3);
    private:
        PWMChannel *pwm;
        uint8_t front_left;
        uint8_t front_right;
        uint8_t back_right;
        uint8_t back_left;
};



#endif /* INC_LOS_ACTUATORS_HPP_ */
