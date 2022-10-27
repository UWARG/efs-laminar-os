/*
 * LOS_Position.cpp
 *
 *  Created on: Jun. 2, 2022
 *      Author: anthony
 */

#include "../Inc/LOS_Position.hpp"

/**
 * @brief Gets LOS_Position singleton
 * 
 * @return LOS_Position& 
 */

LOS_Position& LOS_Position::getInstance() {
    static LOS_Position instance;
    return instance;
}

LOS_Position::LOS_Position() {
	// TODO: run this elsewhere or thread this in update thread
	#ifdef BMX160
	IMU& imuObj = BMX160::getInstance();
	#endif

	#ifdef MPU6050
	IMU& imuObj = MPU6050::getInstance();
	#endif

    #ifdef VN300
    // for vn300
    #else
    #define sensor_fusion_ = true;
    #endif

    if (sensor_fusion_)
        SF_Init();

}

void sensor_fusion(IMUData_t new_imuData)
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
    // RawPosition_.airspeed = 

    // gps
    // rawPosition_.latitude = 
    // rawPosition_.longitude = 
    // rawPosition_.utcTime =   
    // rawPosition_.groundSpeed = 
    // rawPosition_.altitude =
    // rawPosition_.heading =
    // rawPosition_.numSatellites = 
    // rawPosition_.fixStatus = 

    // altimeter
    // rawPosition_.pressure = 
    // rawPosition_.altitude =
    // rawPosition_.temp = 

    SF_GetResult(*sensorFusionOut_);
    
    // lat and long
    position_.latitude = sensorFusionOut_.latitude;
    position_.longitude = sensorFusionOut_.longitude;

    position_.latitude_speed = sensorFusionOut_.latitudeSpeed;
    position_.longitude_speed = sensorFusionOut_.longitudeSpeed;

    // rate of climb
    position_.climb_rate = sensorFusionOut_.rateOfClimb;

    // track and heading
    position_.track = sensorFusionOut_.track;
    position_.heading = sensorFusionOut_.heading

    // air speed
    position_.air_speed = sensorFusionOut_.airSpeed;

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

void updatePosition() {

    IMUData_t imuData;
    imuObj->GetResult(imuData);

    if (sensor_fusion_)
    {   
        sensor_fusion(imuData);
    }
    else
    {
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

PositionData_t* LOS_Position::getPosition() {
	// update position
    updatePosition();
	
    // returns pointer to the position struct
    return position_;
}