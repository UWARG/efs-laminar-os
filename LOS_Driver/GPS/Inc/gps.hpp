/**
 * Gps sensor interface and part number selector.
 * Author(s): Anthony Berbari, Dhruv Rawat
 */

#ifndef GPS_HPP
#define	GPS_HPP

#include <stdint.h>
#include "LOS_D_SF_CommonDataTypes.hpp"
#include "main.h"
/** What UART interface the device is connected to */
#define GPS_UART_INTERFACE 1

/** Baudrate the gps communicates over by default */
#define GPS_UART_BAUDRATE 9600

/** How large to make the internal buffer for parsing messages. Should be the size
 of the largest message we'll receive from the gps*/
#define GPS_UART_BUFFER_SIZE 800

#define NEO_M8 0

struct GpsData_t{
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
};

class Gps
{
	public:
		/**
		* Begins the process of collecting the sensor's data.
		* This is a non blocking function that returns right away.
		*/
//        virtual void BeginMeasuring(void) = 0;

		/**
		* Gets the information about the aircraft's position (See GpsData_t struct).
		* This is a non blocking function that returns right away, either with new data,
		* or with old data (in case of old data, the dataIsNew flag of the result struct will be cleared).
		* @param[out]		Data 		pointer to the result struct.
		*/
        virtual void GetResult(GpsData_t& Data) = 0;
};

#ifdef UNIT_TESTING
#include "gpsMock.hpp"

class TestGps : public Gps {
    public:
        static TestGps* GetInstance();

        void Begin_Measuring();
        void GetResult(GpsData_t& Data);
};

#endif

#ifdef SIMULATION
// This derived class hooks into the Simulink simulation rather than hardware
class SimulatedGps : public Gps
{
    public :
        void Begin_Measuring();
        void GetResult(GpsData_t& Data);
};
#endif

void GPS_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart); 
#endif