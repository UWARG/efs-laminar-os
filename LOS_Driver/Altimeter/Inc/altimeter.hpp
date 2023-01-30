/**
 * Altimeter Sensor Functions and Part Number Selection.
 * Available Altimeter driver(s): MPL3115A2
 * Authors: Lucy Gong, Anthony Berbari
 */

#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

#include <cstdint>
#include <stdint.h>
#include "CommonDataTypes.hpp"
/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

struct AltimeterData_t 
{
    float pressure, altitude, temp;
    
    bool isDataNew; 
    SensorErrorCodes status;
    uint32_t utcTime;
};

/**
 * This union is of no use to the user.
 * It is for internal use by the module only.
 * */
union AltimeterAltitudeRepresentation
{
    uint8_t byte[3];
    int32_t Q16point4;
};

/***********************************************************************************************************************
 * Prototypes
 *********************************************************************************************************************/

class Altimeter {
    public:
        /**
         * Begins a transaction with the Altimeter.
         * This function is non blocking and returns right away, data will be stored inside the module as it arrives.
         * To achieve synchronous data, this function must be called synchronously.
         * */
        virtual void Begin_Measuring() = 0; 

        /**
         * Retrieves any data already sent by the altimeter.
         * If no new data is available, the appropriate flag will be set in the return struct.
         * All contents of the return struct, apart from the isDataNew flag, are undefined unless isDataNew is set to 1.
         * This function is non blocking and returns right away.
         * @param[in]       Data        reference to the results struct.
         * */
        virtual void GetResult(AltimeterData_t& Data) = 0; //
};

#ifdef UNIT_TESTING
#include "airspeed_Mock.hpp"

class TestAltimeter : public Altimeter {
    public:
        static TestAltimeter* GetInstance();

        void Begin_Measuring();
        void GetResult(AltimeterData_t& Data);
};
#endif

#endif