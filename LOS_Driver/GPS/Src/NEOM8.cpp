/*
 * GPS.cpp
 *
 *  Created on: Feb 8, 2023
 *      Author: Hardy
 */

/*
* configuration for the uart
* RCC - crystal/ceramic resonator on
* DMA - UART-RX circular mode on
*/


#include "gps.hpp"
#include "NEOM8.hpp"

///////////////////// Constructor Destructor Portion /////////////////////

NEO_GPS::NEO_GPS()
{
	UART = &huart1;
	outputData.ggaDataIsNew = false;
	outputData.timeIsNew = false;
	outputData.vtgDataIsNew = false;
	outputData.fixStatus = 0;
	outputData.sensorStatus =  SENSOR_FAIL;
}


NEO_GPS::NEO_GPS(UART_HandleTypeDef* dev)
{
	UART = dev;
	outputData.ggaDataIsNew = false;
	outputData.timeIsNew = false;
	outputData.vtgDataIsNew = false;
	outputData.fixStatus = 0;
	outputData.sensorStatus =  SENSOR_FAIL;
}

NEO_GPS::~NEO_GPS()
{

}

///////////////////// Private Function Portion /////////////////////

/*
 * private function that get the GGA or RMC sentence from raw data
 * then it can be sent for parsing
 */
bool NEO_GPS::get_sentense(const char* string, char* container, int length)
{
	int counter = 0;
	int len = length;
	bool new_sentense = false;
	while(counter < GPS_UART_BUFFER_SIZE && !new_sentense)
	{
		if(rx_raw[counter] == string[0])
		{
			int i = 1;
			bool same = true;
			while(i < len && same)
			{
				if(rx_raw[counter + i] != string[i])
					same = false;
				i++;
			}
			if(same)
			{
				while(rx_raw[counter + i] != '*' && counter + i < GPS_UART_BUFFER_SIZE)
				{
					container[i - len] = rx_raw[counter + i];
					i++;
				}
				//new_sentense = true;
				return true;
			}

		}

		counter++;
	}

	return false;
}

void NEO_GPS::parseRawDate()
{
	const char GGAs[3] = {'G', 'G', 'A'};
	const char RMCs[3] = {'R', 'M', 'C'};

//GGA section
	if(get_sentense(GGAs, GGA, 3))
	{
		if(decodeGGA(GGA, &gpsData.ggastruct) != 0)
		{
			outputData.ggaDataIsNew = false;
			outputData.timeIsNew = false;
		}
		else
		{
			outputData.ggaDataIsNew = true;
			outputData.timeIsNew = true;
		}
	}
	else
	{
		outputData.ggaDataIsNew = false;
		outputData.timeIsNew = false;
	}


//RMC section
//I used RMC to get ground speed and course in stead of vtg
//But I am kinda lazy to change the name, let it be a misconception one day
	if(!get_sentense(RMCs, RMC, 3))
	{
		if(decodeRMC(RMC, &gpsData.rmcstruct) != 0)
			outputData.vtgDataIsNew = false;
		else
			outputData.vtgDataIsNew = true;
	}
	else
	{
		outputData.vtgDataIsNew = false;
	}

	if(outputData.vtgDataIsNew || outputData.ggaDataIsNew)
	{
		outputData.dataIsNew = true;
	}
	else 
	{
		outputData.dataIsNew = false;
	}

}

void NEO_GPS::refreshGPS()
{
	if (HAL_UART_Receive(UART, rx_raw, GPS_UART_BUFFER_SIZE, 500)!= HAL_OK)
	{
		outputData.sensorStatus = SENSOR_FAIL;
		return;
	}

	outputData.sensorStatus = SENSOR_SUCCESS;

	parseRawDate();

	//if get new gga data then update new data to output gps struct
	if(outputData.ggaDataIsNew == true)
	{
		outputData.latitude = gpsData.ggastruct.lcation.latitude;
		outputData.longitude = gpsData.ggastruct.lcation.longitude;
		outputData.utcTime =  gpsData.ggastruct.tim.allinsec;
		outputData.altitude = gpsData.ggastruct.alt.altitude;
		outputData.numSatellites = uint8_t(gpsData.ggastruct.numofsat);
		outputData.fixStatus = uint8_t(gpsData.ggastruct.isfixValid);
	}


	//if get new rmc data then update new data to output gps struct
	if(outputData.vtgDataIsNew == true)
	{
		outputData.groundSpeed = gpsData.rmcstruct.speed;
		outputData.heading = int16_t(gpsData.rmcstruct.course);
	}
}


///////////////////// Public Function Portion /////////////////////

void NEO_GPS::GetResult(GpsData_t& Data)
{
	refreshGPS();
	//is there anything more I can add? Probably no
}



