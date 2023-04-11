#ifndef LOS_D_US_HPP_
#define LOS_D_US_HPP_

#include <stdint.h>

typedef struct {
    uint64_t time;        // Time since startup in nanoseconds
    double latitude;      // Latitude in degrees
    double longitude;     // Longitude in degrees
    double altitude;      // Altitude in m
    float velNorth;       // Velocity in North frame in m/s
    float velEast;        // Velocity in East frame in m/s
    float velDown;        // Velocity in Down frame in m/s
} USGPSData_t;

typedef struct {
    float pitch;        // Pitch in degrees
    float roll;         // Roll in degrees
    float yaw;          // Yaw in degrees
    float accel0;       // Acceleration in m/s^2 in body frame 0
    float accel1;       // Acceleration in m/s^2 in body frame 1
    float accel2;       // Acceleration in m/s^2 in body frame 2
} USIMUData_t;

// This is the enum that will signify which data to send
typedef struct {
    bool gps;
    bool imu;
} requestData_t;

/*
    -This is the struct that will be passed in and out of GetResult
    -Based on type_data, we will know which data to send with all the rest being 0
*/
typedef struct {
    USGPSData_t gps_data;
    USIMUData_t imu_data;
    requestData_t req_data;
} USData_t;

class UnifiedSensor {
    public:
        virtual void GetResult(USData_t& data) = 0;
};

#endif /* LOS_D_US_HPP_ */