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
        imu_obj = &BMX160::getInstance();
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
    raw_position.gyrx = imu_data.gyro_x; 
    raw_position.gyry = imu_data.gyro_y;
    raw_position.gyrz = imu_data.gyro_z;

    raw_position.accx = imu_data.accel_x;
    raw_position.accy = imu_data.accel_y;
    raw_position.accz = imu_data.accel_z;

    raw_position.magx = imu_data.mag_x;
    raw_position.magy = imu_data.mag_y;
    raw_position.magz = imu_data.mag_z;
    
    // airspeed
    raw_position.airspeed = 0; 

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
    raw_position.pressure = 0;
    raw_position.altitude_alt = 0;
    raw_position.temp = 0;

    SF_error_status = SF_GenerateNewResult((*this).imu_data, 
                                           (*this).gps_data,
                                           (*this).altimeter_data, 
                                           (*this).airspeed_data);
    SF_GetResult(&sensor_fusion_out);
    
    // lat and long
    position.latitude = sensor_fusion_out.latitude;
    position.longitude = sensor_fusion_out.longitude;

    position.latitudeSpeed = sensor_fusion_out.latitudeSpeed;
    position.longitudeSpeed = sensor_fusion_out.longitudeSpeed;

    // rate of climb
    position.rateOfClimb = sensor_fusion_out.rateOfClimb;

    // track and heading
    position.track = sensor_fusion_out.track;
    position.heading = sensor_fusion_out.heading;

    // air speed
    position.airspeed = sensor_fusion_out.airspeed;

    // ground speed
    //position_.ground_speed = sensor_fusion_out.groundSpeed;

    // orientation
    position.roll = sensor_fusion_out.roll;
    position.pitch = sensor_fusion_out.pitch;
    position.yaw = sensor_fusion_out.yaw;
    
    position.rollRate = sensor_fusion_out.rollRate; 
    position.pitchRate = sensor_fusion_out.pitchRate;
    position.yawRate = sensor_fusion_out.yawRate;
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
    // returns pointer to the position struct
    return &position;
}

RawPositionData_t* LOS_Position::getRawPosition() {
    // returns pointer to the position struct
    return &raw_position;
}
