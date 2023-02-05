/**
*   
*   Airspeed sensor functions
*
*   This header is an outline of basic functions of the airspeed
*   sensor. Generally, this sensor is a Pitot tube which uses a 
*   pressure differential to determine airspeed. 
*
*   Airspeed calculation should be done and returned in meters 
*   per second
*
*    Author: Annie LePage, Anthony Berbari
**/

#ifndef AIRSPEED_HPP
#define AIRSPEED_HPP

#include <cstdint>
#include <math.h>
#include <string.h>
//Perhaps we need to import the h file below.
#include <stm32l5xx.h>
#include <stdio.h>
#include "LOS_D_SF_CommonDataTypes.hpp"

#define MS4525D0_I2C_ADDR1 0x28
#define MS4525D0_I2C_ADDR2 0x36
#define MS4525D0_I2C_ADDR3 0x46
//#define P_MAX_TYPEA 0x399A
//#define P_MIN_TYPEA 0x0666
//#define P_MAX_TYPEB 0x3CCB
//#define P_MIN_TYPEB 0x0333
//#define psi_range 30


/*
    Currently there is only one airspeed sensor used, if this is 
    changed to a different sensor, part numbers and a selection
    option should be added
*/


struct airspeedData_t 
{
    double airspeed;        // in m/s
    SensorErrorCodes sensorStatus;       // report any errors, possible malfunctions 
    bool isDataNew;         // is the data fresh?
};

class Airspeed
{
	private:
		I2C_HandleTypeDef* I2C;
		float airspeed;
		float dif_pressure;
		float temperature;
		int16_t dp_raw; //raw pressure data
		int16_t dt_raw; //raw temperature data
        airspeedData_t airspeedData;

		void calculate_pressure();
		void calculate_temperature();
		void calculate_airspeed();

	public:
		/*
		 * Default constructor of this object need the I2C handler
		 */
        Airspeed();
	    Airspeed(I2C_HandleTypeDef* dev);
	    ~Airspeed();
	    /*
	     * init function has to be called before fetching any
	     * data from sensor
	     */
        //changed from bool to void, is it fine?
	    void init();
	    float get_pressure() const;
	    float get_temperature() const;
	    float get_airspeed( ) const;
        static getInstance();
        virtual void GetResult(airspeedData_t& Data) = 0; 
};




#ifdef UNIT_TESTING
#include "airspeed_Mock.hpp"

class TestAirspeed : public airspeed {
    public:
        static TestAirspeed* GetInstance();

        void Begin_Measuring();
        void GetResult(airspeedData_t& Data);
};
#endif

#ifdef SIMULATION
// This derived class hooks into the Simulink simulation rather than hardware
class SimulatedAirspeed : public airspeed
{
    public :
        void Begin_Measuring();
        void GetResult(airspeedData_t& Data);
};
#endif

#endif