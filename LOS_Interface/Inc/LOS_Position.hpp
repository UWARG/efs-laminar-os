/*
 * LOS_Position.hpp
 *
 * Created on: Jun. 2, 2022
 *      Author: anthony
 * 
 */

#ifndef INC_LOS_POSITION_HPP_
#define INC_LOS_POSITION_HPP_

#include "interface_datatypes.hpp"
#include "SF_Interface.h"
#include "config.hpp"

class LOS_Position {
        // This class is used to get the current position
        // and attitude of the plane
public:
        LOS_Position();
        static LOS_Position& getInstance();

        PositionData_t* getPosition();
        RawPositionData_t* getRawPosition();
        
        void updatePosition();

private:
        void sensorFusion();
        IMUData_t imuData;

        PositionData_t position_;
        RawPositionData_t rawPosition_;

        SFOutput_t sensorFusionOut_;
};

#endif 