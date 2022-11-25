//
// Sensorfusion - Converts raw sensor data into fused human readable formatted structs
// Created by Anthony Luo on 2022-07-12.
// Authored by Lucy Gong, Dhruv Rawat, Anthony Bertnyk, Anthony Luo
//

#ifndef ZP_PROTO_PORT_SENSORFUSION_HPP
#define ZP_PROTO_PORT_SENSORFUSION_HPP

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "CommonDataTypes.hpp"

#include "LOS_Position.hpp"

//Frequency of SF calculations in Hz
const int SF_FREQ = 100;

// -1 = FAILED
// 0 = SUCCESS
// 1 = Old Data
typedef struct {
    int errorCode;
} SFError_t;

//Following structs store the raw sensor data so other modules can have direct access to them without including sensor header files
typedef struct
{
    float magx, magy, magz;
    float accx, accy, accz;
    float gyrx, gyry, gyrz;
    float temp;

    bool isDataNew;
    enum SensorErrorCodes sensorStatus;
    float utcTime;
} IMU_Data_t;

typedef struct
{
    double airspeed;

    enum SensorErrorCodes sensorStatus;
    bool isDataNew;
    float utcTime;
} Airspeed_Data_t;

typedef struct
{
    long double latitude;  // 8 Bytes
    long double longitude; // 8 Bytes
    float utcTime;     // 4 Bytes. Time in seconds since 00:00 (midnight)
    float groundSpeed; // in m/s
    int altitude; // in m
    int16_t heading; // in degrees. Should be between 0-360 at all times, but using integer just in case
    uint8_t numSatellites;    // 1 Byte
    uint8_t fixStatus; //0 = No GPS, 1 = GPS fix, 2 = DGSP Fix, 3 = Estimated/Dead Recoking Fix

    enum SensorErrorCodes sensorStatus; // 0 = no fix, 1 = gps fix, 2 = differential gps fix (DGPS) (other codes are possible)
    bool dataIsNew; // true if data has been refreshed since the previous time GetResult was called, false otherwise.
    bool timeIsNew;

    //Added these so autopilot knows which data is new
    bool ggaDataIsNew; //Position, altitude, time, and number of satellites
    bool vtgDataIsNew; //Groundspeed and Heading
}  Gps_Data_t;

typedef struct  {

    float pressure, altitude, temp;

    bool isDataNew;
    enum SensorErrorCodes status; //TBD but probably 0 = SUCCESS, -1 = FAIL, 1 = BUSY
    int utcTime; //Last time GetResult was called
} Altimeter_Data_t;


/**
 * Initialize sensor fusion.
 */
void SF_Init(void);

/**
 * Generates fused sensor data. Should be called at a constant rate defined by SF_FREQ after SF_Init has been called once.
 */
SFError_t SF_GenerateNewResult(IMUData_t imuData, GpsData_t gpsData, AltimeterData_t altimeterData, AirspeedData_t airspeedData);

/**
 * Get latest fused sensor data. Can be called any time data is needed after SF_init has been called once. Waits until the output struct is not being accessed by another task.
 * @param [out] output Output struct for fused data.
 * @return Error struct.
 */
SFError_t SF_GetResult(SFOutput_t *SFoutput);

/**
 * Get raw IMU data. Can be called any time raw data is needed.
 * @return IMU struct.
 */
IMU_Data_t SF_GetRawIMU();

#ifdef AUTOPILOT
/**
 * Get raw Airspeed data. Can be called any time raw data is needed.
 * @return Airspeed struct.
 */
Airspeed_Data_t SF_GetRawAirspeed();

/**
 * Get raw GPS data. Can be called any time raw data is needed.
 * @return GPS struct.
 */
Gps_Data_t SF_GetRawGPS();

/**
 * Get raw Altimeter data. Can be called any time raw data is needed.
 * @return Altimeter struct.
 */
Altimeter_Data_t SF_GetRawAltimeter();
#endif

#ifdef __cplusplus
}
#endif

#endif //ZP_PROTO_PORT_SENSORFUSION_HPP