/*
 * LOS_Position.cpp
 *
 *  Created on: Jun. 2, 2022
 *      Author: anthony
 */

#include "LOS_Position.hpp"

/**
 * @brief Gets LOS_Position singleton
 * 
 * @return LOS_Position& 
 */

LOS_Position& LOS_Position::getInstance() {
    static LOS_Position instance;
    return instance;
}

/**
 * @brief constructor for LOS_Position
 * 
 */

LOS_Position::LOS_Position() {

    if (SENSOR_FUSION_ == true)
    {
        SF_Init();
    }

}

/**
 * @brief Calls sensor fusion after updating raw
 *        position from data from sensors
 * 
 */

void LOS_Position::sensor_fusion(IMUData_t new_imuData, GpsData_t new_gpsData,
                                 AltimeterData_t new_altimeterData,
                                 airspeedData_t new_airspeedData)
{
    // imu
    rawPosition_.gyrx = new_imuData.gyro_x; 
    rawPosition_.gyry = new_imuData.gyro_y;
    rawPosition_.gyrz = new_imuData.gyro_z;

    rawPosition_.accx = new_imuData.accel_x;
    rawPosition_.accy = new_imuData.accel_y;
    rawPosition_.accz = new_imuData.accel_z;

    rawPosition_.magx = new_imuData.mag_x;
    rawPosition_.magy = new_imuData.mag_y;
    rawPosition_.magz = new_imuData.mag_z;

    // airspeed
    rawPosition_.airspeed = new_airspeedData.airspeed; 

    // gps
    rawPosition_.latitude = new_gpsData.latitude;
    rawPosition_.longitude = new_gpsData.longitude;
    rawPosition_.utcTime =  new_gpsData.utcTime;
    rawPosition_.groundSpeed = new_gpsData.groundSpeed;
    rawPosition_.altitude_gps = new_gpsData.altitude;
    rawPosition_.heading = new_gpsData.heading;
    rawPosition_.numSatellites = new_gpsData.numSatellites;
    rawPosition_.fixStatus = new_gpsData.fixStatus;

    // altimeter
    rawPosition_.pressure = new_altimeterData.pressure;
    rawPosition_.altitude_alt = new_altimeterData.altitude;
    rawPosition_.temp =  new_altimeterData.temp;

    SF_GenerateNewResult(new_imuData, new_gpsData, new_altimeterData, new_airspeedData);
    SF_GetResult(&sensorFusionOut_);
    
    // lat and long
    position_.latitude = sensorFusionOut_.latitude;
    position_.longitude = sensorFusionOut_.longitude;

    position_.latitude_speed = sensorFusionOut_.latitudeSpeed;
    position_.longitude_speed = sensorFusionOut_.longitudeSpeed;

    // rate of climb
    position_.climb_rate = sensorFusionOut_.rateOfClimb;

    // track and heading
    position_.track = sensorFusionOut_.track;
    position_.heading = sensorFusionOut_.heading;

    // air speed
    position_.air_speed = sensorFusionOut_.airspeed;

    // ground speed
    position_.ground_speed = sensorFusionOut_.groundSpeed;

    // orientation
    position_.roll = sensorFusionOut_.roll;
    position_.pitch = sensorFusionOut_.pitch;
    position_.yaw = sensorFusionOut_.yaw;
    
    position_.roll_rate = sensorFusionOut_.rollRate; 
    position_.pitch_rate = sensorFusionOut_.pitchRate;
    position_.yaw_rate = sensorFusionOut_.yawRate;
}

/**
 * @brief updates the position struct calling
 *        either sensor fusion or imu directly 
 *        (if its VN-300)
 */

void LOS_Position::updatePosition() {

    IMUData_t imuData;
    g_imuObj->GetResult(imuData);

    if (SENSOR_FUSION_)
    {   
        GpsData_t gpsData;
        AltimeterData_t altimeterData;
        airspeedData_t airspeedData;
        g_gpsObj->GetResult(gpsData);
        g_altimeterObj->GetResult(altimeterData);
        g_airspeedObj->GetResult(airspeedData);
        sensor_fusion(imuData, gpsData, altimeterData, airspeedData);
    }
    else
    {
        /* Vector Nav */
        // lat and long
        // position_.latitude = 
        // position_.longitude = 

        // position_.latitude_speed = 
        // position_.longitude_speed =

        // rate of climb
        // position_.climb_rate =

        // track and heading
        // position_.track =
        // position_.heading =

        // airspeed
        // position_.air_speed =
        
        // ground speed
        // position_.ground_speed =

        // orientation
        // position_.roll = 
        // position_.pitch = 
        // position_.yaw = 
        
        // position_.roll_rate = 
        // position_.pitch_rate = 
        // position_.yaw_rate = 
    }
}

/**
 * @brief Retrieves pointer to position data
 * 
 * @return LOS_Position& 
 */

PositionData_t* LOS_Position::getPosition() {
	// update position
    updatePosition();
	
    // returns pointer to the position struct
    return &position_;
}