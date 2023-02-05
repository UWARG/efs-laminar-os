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

    #ifdef SENSOR_FUSION
        SF_Init();
    #endif

    #ifdef BMX160_CONNECTED
        imuObj = &BMX160::getInstance();
    #endif

    #ifdef NEOM8_CONNECTED
        gpsObj = &NEO_GPS::getInstance();
    #endif

}

/**
 * @brief Calls sensor fusion after updating raw
 *        position from data from sensors
 * 
 */

void LOS_Position::sensorFusion()
{
    imuObj->GetResult(imuData);
    gpsObj->GetResult(gpsData);
    
    /*
        
        g_altimeterObj->GetResult(altimeterData);
        g_airspeedObj->GetResult(airspeedData);
    */
    
    // imu
    rawPosition_.gyrx = imuData.gyro_x; 
    rawPosition_.gyry = imuData.gyro_y;
    rawPosition_.gyrz = imuData.gyro_z;

    rawPosition_.accx = imuData.accel_x;
    rawPosition_.accy = imuData.accel_y;
    rawPosition_.accz = imuData.accel_z;

    rawPosition_.magx = imuData.mag_x;
    rawPosition_.magy = imuData.mag_y;
    rawPosition_.magz = imuData.mag_z;
    
    // airspeed
    rawPosition_.airspeed = 0; 

    // gps
    rawPosition_.latitude = gpsData.latitude;
    rawPosition_.longitude = gpsData.longitude;
    rawPosition_.utcTime =  gpsData.utcTime;
    rawPosition_.groundSpeed = gpsData.groundSpeed;
    rawPosition_.altitude_gps = gpsData.altitude;
    rawPosition_.heading = gpsData.heading;
    rawPosition_.numSatellites = gpsData.numSatellites;
    rawPosition_.fixStatus = gpsData.fixStatus;

    // altimeter
    rawPosition_.pressure = 0;
    rawPosition_.altitude_alt = 0;
    rawPosition_.temp = 0;

    (*this).SFerrorStatus = SF_GenerateNewResult((*this).imuData, 
                                                (*this).gpsData,
                                                (*this).altimeterData, 
                                                (*this).airspeedData);
    SF_GetResult(&sensorFusionOut_);
    
    // lat and long
    position_.latitude = sensorFusionOut_.latitude;
    position_.longitude = sensorFusionOut_.longitude;

    position_.latitudeSpeed = sensorFusionOut_.latitudeSpeed;
    position_.longitudeSpeed = sensorFusionOut_.longitudeSpeed;

    // rate of climb
    position_.rateOfClimb = sensorFusionOut_.rateOfClimb;

    // track and heading
    position_.track = sensorFusionOut_.track;
    position_.heading = sensorFusionOut_.heading;

    // air speed
    position_.airspeed = sensorFusionOut_.airspeed;

    // ground speed
    //position_.ground_speed = sensorFusionOut_.groundSpeed;

    // orientation
    position_.roll = sensorFusionOut_.roll;
    position_.pitch = sensorFusionOut_.pitch;
    position_.yaw = sensorFusionOut_.yaw;
    
    position_.rollRate = sensorFusionOut_.rollRate; 
    position_.pitchRate = sensorFusionOut_.pitchRate;
    position_.yawRate = sensorFusionOut_.yawRate;
}


/**
 * @brief updates the position struct calling
 *        either sensor fusion or imu directly 
 *        (if its VN-300)
 */

void LOS_Position::updatePosition() {

    #ifdef SENSOR_FUSION
        (*this).sensorFusion();
    #else
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
    #endif
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

RawPositionData_t* LOS_Position::getRawPosition() {
	// update position
    updatePosition();
	
    // returns pointer to the position struct
    return &rawPosition_;
}