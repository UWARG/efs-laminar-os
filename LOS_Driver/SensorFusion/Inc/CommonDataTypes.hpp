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

typedef struct {
    float pressure, altitude, temp;
    
    bool isDataNew; 
    SensorErrorCodes status;
    uint32_t utcTime;
} AltimeterData_t;

typedef struct {
    long double latitude;  // 8 Bytes
    long double longitude; // 8 Bytes
    float utcTime;     // 4 Bytes. Time in seconds since 00:00 (midnight)
    float groundSpeed; // in m/s
    int altitude; // in m
    int16_t heading; // in degrees. Should be between 0-360 at all times, but using integer just in case
    uint8_t numSatellites;    // 1 Byte
	uint8_t fixStatus; //0 = No GPS, 1 = GPS fix, 2 = DGSP Fix, 3 = Estimated/Dead Recoking Fix

    SensorErrorCodes sensorStatus; // 0 = good, 1 = error
    bool dataIsNew; // true if data has been refreshed since the previous time GetResult was called, false otherwise.
	bool timeIsNew;

	//Added these so autopilot knows which data is new
	bool ggaDataIsNew; //Position, altitude, time, and number of satellites
	bool vtgDataIsNew; //Groundspeed and Heading

} GpsData_t;

typedef struct {
	double gyro_x, gyro_y, gyro_z;
	double accel_x, accel_y, accel_z;
	double mag_x, mag_y, mag_z;
} IMUData_t ;


typedef struct {
    double airspeed;        // in m/s

    SensorErrorCodes sensorStatus;       // report any errors, possible malfunctions 
    bool isDataNew;         // is the data fresh?
    float utcTime;          // 4 Bytes. Time in seconds since 00:00 
} AirspeedData_t;

#endif

