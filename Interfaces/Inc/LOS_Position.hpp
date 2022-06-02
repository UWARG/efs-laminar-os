/*
 * LOS_Position.hpp
 *
 *  Created on: Jun. 2, 2022
 *      Author: anthony
 */

#ifndef INC_LOS_POSITION_HPP_
#define INC_LOS_POSITION_HPP_


#include "interface_datatypes.hpp"
#include "../../Drivers/Sensors/Inc/imu.hpp"

class LOS_Position {
    // LOS_Position class returns yaw, pitch, roll as a singleton
    // This class is used to get the current position of the drone
    public:
        static LOS_Position* getInstance();
        PositionData_t getPosition();
        void updatePosition(IMUData_t imuData);
    private:
        LOS_Position();
        PositionData_t position_;
        static LOS_Position * instance_;
        static IMU *imuObj;
};


#endif /* INC_LOS_POSITION_HPP_ */
