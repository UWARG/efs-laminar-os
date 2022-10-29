#ifndef COMMON_DATA_TYPES_HPP
#define COMMON_DATA_TYPES_HPP

enum SensorErrorCodes {SENSOR_SUCCESS = 0, SENSOR_FAIL = 1};

typedef struct {
    float roll, pitch, yaw; //Degrees. Yaw of 180 is north.
    float rollRate, pitchRate, yawRate; //Degrees/second
    float airspeed; //m/s
    float altitude; //m
    float rateOfClimb; //m/s
    long double latitude; //Decimal degrees
    float latitudeSpeed; //m/s
    long double longitude; //Decimal degrees
    float longitudeSpeed; //m/s
    double track; //Degrees. Track of 0 is north.
    float groundSpeed; //m/s
    double heading; //Degrees. Heading of 0 is north.
} SFOutput_t;

#endif

