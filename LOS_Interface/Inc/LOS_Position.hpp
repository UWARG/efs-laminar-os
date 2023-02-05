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
#include "config.hpp"

class LOS_Position {
        // This class is used to get the current position
        // and attitude of the aircraft
public:
        LOS_Position();
        static LOS_Position& getInstance();
        void updatePosition();

        PositionData_t* getPosition();
        RawPositionData_t* getRawPosition();

private:
        void sensorFusion();

        IMUData_t imu_data;
        GpsData_t gps_data;
        AltimeterData_t altimeter_data;
        airspeedData_t airspeed_data;

        PositionData_t position;
        RawPositionData_t raw_position;

        SFOutput_t sensor_fusion_out;

        IMU* imu_obj;
        Gps* gps_obj;

        SFError_t SF_error_status;
};

#endif 