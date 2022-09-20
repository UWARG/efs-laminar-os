/*
 * interface_datatypes.hpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */

#ifndef INC_INTERFACE_DATATYPES_HPP_
#define INC_INTERFACE_DATATYPES_HPP_


#include <cstdint>

typedef struct Teleop_Instructions_t{
	float teleop_inp[8]; // deprecated, here just in case
	// should these individual channels be defined in the link or in zp?
	// I think they should be defined in ZP.... (in case you wanted to fly with trims/rates?)
	uint8_t roll;
	uint8_t pitch;
	uint8_t yaw;
	uint8_t throttle;
	uint8_t is_armed;
};

typedef struct Quadrotor_Motor_out {
	float front_left;
	float front_right;
	float back_left;
	float back_right;
};

typedef struct
{
    float frontLeftMotorPercent;
    float frontRightMotorPercent;
    float backLeftMotorPercent;
    float backRightMotorPercent;

} PID_Output_t;

typedef struct PositionData_t {
    float pitch, roll, yaw;
	float ax, ay, az;
	double lat, lon;
	float alt;
	float vx, vy, vz;
	float q0, q1, q2, q3;
	float ax, ay, az;
	float gx, gy, gz;
};

#endif /* INC_INTERFACE_DATATYPES_HPP_ */
