/*
 * LOS_Position.hpp
 *
 * Created on: Jun. 2, 2022
 *      Author: anthony
 * 
 */

#ifndef INC_LOS_POSITION_HPP_
#define INC_LOS_POSITION_HPP_

#include "BMX160.hpp"
#include "MPU6060.hpp"

#include "airpseed.hpp"

#include "altimeter.hpp"

#include "gps.hpp"

#include "CommonDataTypes.hpp"
#include "SensorFusion.hpp"

#include "interface_datatypes.hpp"

class LOS_Position {
        // This class is used to get the current position
        // and attitude of the plane
public:
        static LOS_Position& getInstance();

        PositionData_t* getPosition();
        PositionData_t* getRawPosition();
        void updatePosition();

private:
        LOS_Position();
        void sensor_fusion(IMUData_t new_imuData, GpsData_t gpsData,
                           AltimeterData_t altimeterData,
                           airspeedData_t airspeedData);

        PositionData_t position_;
        RawPositionData_t rawPosition_;

        SFOutput_t sensorFusionOut_;
};

#endif 