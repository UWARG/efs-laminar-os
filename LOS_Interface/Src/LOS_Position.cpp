/*
 * LOS_Position.cpp
 *
 *  Created on: Jun. 2, 2022
 *      Author: anthony
 */

#include "LOS_Position.hpp"

/**
 * @brief Gets LOS_Position singleton
 */
LOS_Position& LOS_Position::getInstance() {
    static LOS_Position instance;
    return instance;
}

/**
 * @brief constructor for LOS_Position
 */
LOS_Position::LOS_Position() {
#ifdef SENSOR_FUSION
    SF_Init();
#else
    us_data.req_data = {true, true};
#endif

#ifdef BMX160_CONNECTED
    imu_obj = &BMX160::getInstance();
#endif

#ifdef NEOM8_CONNECTED
    /* TODO: Initialize NEOM8 */
#endif

#ifdef VN300_CONNECTED
    us_obj =  &VN300::getInstance();
#endif
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
    (*this).readUnifiedSensor();
#endif
}

/**
 * @brief Retrieves pointer to position data
 */
PositionData_t* LOS_Position::getPosition() {
    // returns pointer to the position struct
    return &position;
}

/**
 * @brief Retrieves pointer to raw position data
 */
RawPositionData_t* LOS_Position::getRawPosition() {
    // returns pointer to the position struct
    return &raw_position;
}


#ifdef SENSOR_FUSION
/**
 * @brief Calls sensor fusion after updating raw
 *        position from data from sensors
 */
void LOS_Position::sensorFusion()
{
    imu_obj->GetResult(imu_data);
    
    /*
        g_gpsObj->GetResult(gpsData);
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
    raw_position.latitude = 0;
    raw_position.longitude = 0;
    raw_position.utcTime =  0;
    raw_position.groundSpeed = 0;
    raw_position.altitude_gps = 0;
    raw_position.heading = 0;
    raw_position.numSatellites = 0;
    raw_position.fixStatus = 0;

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
#else /* SENSOR_FUSION */

/**
 * @brief Reads data from a single sensor that
 *        does not need fusion e.g. VN300
 */
void LOS_Position::readUnifiedSensor()
{
    us_obj->GetResult(us_data);

    /* Vector Nav */
    
    // lat and long
    position.latitude = us_data.gps_data.latitude;
    position.longitude = us_data.gps_data.longitude;

    // rate of climb
    position.rateOfClimb = -us_data.gps_data.velDown;

    // track and heading
    // position_.track =
    // position_.heading =

    // airspeed
    // position_.air_speed =
    
    // ground speed
    // position_.ground_speed =

    // orientation
    position.roll = us_data.imu_data.roll;
    position.pitch = us_data.imu_data.pitch;
    position.yaw = us_data.imu_data.yaw;
    
    // position_.roll_rate = 
    // position_.pitch_rate = 
    // position_.yaw_rate = 
}
#endif /* SENSOR_FUSION */