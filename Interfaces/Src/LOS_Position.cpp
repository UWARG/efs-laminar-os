/*
 * LOS_Position.cpp
 *
 *  Created on: Jun. 2, 2022
 *      Author: anthony
 */


#include "../Inc/LOS_Position.hpp"
#include "../../Drivers/Sensors/Inc/imu.hpp"


/**
 * @brief Gets LOS_Position singleton
 * 
 * @return LOS_Position& 
 */ 
LOS_Position &LOS_Position::getInstance() {
    static LOS_Position instance;
    return instance;
}


LOS_Position::LOS_Position() {
    // TODO: run this elsewhere or thread this in update thread
    imuObj = &BMX160::getInstance();
}

PositionData_t LOS_Position::getPosition() {
    // gets BMX160 results
    // Todo: put the getting of results in updatePosition
    // updatePosition(imuObj->GetResult()); or smth
    IMUData_t imuData;
    imuObj->GetResult(imuData);
    position_.roll = imuData.gyro_x;
    position_.pitch = imuData.gyro_y;
    position_.yaw = imuData.gyro_z;
    position_.ax = imuData.accel_x;
    position_.ay = imuData.accel_y;
    position_.az = imuData.accel_z;
    return position_;
}