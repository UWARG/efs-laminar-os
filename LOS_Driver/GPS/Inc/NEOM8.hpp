/*
 * CPS.hpp
 *
 *  Created on: Feb 8, 2023
 *      Author: Hardy
 */

#ifndef INC_GPS_HPP_
#define INC_GPS_HPP_

#include <stm32l5xx.h> //for the UART_HandlerTypeDef, is there a more general library?
#include "NMEA.h"
#include "gps.hpp"


#define MESSAGE_SIZE 100

extern UART_HandleTypeDef huart1;

class NEO_GPS: public Gps
{
	private:
	uint8_t rx_raw[GPS_UART_BUFFER_SIZE];	//raw char array
	char GGA[MESSAGE_SIZE];	//raw GGA message, location info
	char RMC[MESSAGE_SIZE]; //raw RMC message, time info
	GPSSTRUCT gpsData;	//the struct that stores the gps data right after parsing
	GpsData_t outputData;	//the struct that can be send to SensorFusion etc.
	UART_HandleTypeDef *UART;

	/*
	 * "string" is the key word of the protocol we are searching
	 * "container" is the output container
	 * "length" is the length of the key word
	 */
	bool get_sentense(const char* string, char* container, int length);


	/*
	 * call decode function from NMEA
	 * set flags of new data
	 */
	void parseRawDate();

	/*
	 * should fetch raw data from gps sensor
	 * call parseRawData function
	 * parse from gpsData to outputDate, which is parse form GPSSTRUCT to GPSData_t
	 */

	void refreshGPS();

	public:

	NEO_GPS();
    NEO_GPS(UART_HandleTypeDef* dev);
    ~NEO_GPS();



	void GetResult(GpsData_t& Data);

};



#endif /* INC_GPS_HPP_ */
