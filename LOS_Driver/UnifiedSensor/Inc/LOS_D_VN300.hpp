/*
 * vectorNav.hpp
 *
 *  Created on: Jun 23, 2022
 *      Author: Christopher Chung
 */

#ifndef INC_VECTORNAV_HPP_
#define INC_VECTORNAV_HPP_

#include <main.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "LOS_D_US.hpp"

/*
    This class inherits the UnifiedSensor class and is used for the VN300 operation
*/
class VN300: public UnifiedSensor{
    public:

        /**
         * @brief Gets the only instance of this class, following the singleton model
         *
         * @return The singleton instance
         */
        static UnifiedSensor& getInstance();

        /**
         * @brief Constructor that will instantly delete the object that was instantiated to protect the singleton model
         */
        VN300(const VN300*)=delete;

        /**
         * @brief Get the IMU and GPS data
         *
         * @param data Struct holding the IMU and GPS data
         */
        void GetResult(USData_t& data);

    private:

        //I think this calls the constructor and makes our single instance
        VN300();

        /**
         * @brief Initialization of the VN300
         */
        void VN300Init(void); //we may not need this

        /**
         * @brief Gets the GPS data from the VN300
         *
         * @param gpsData The struct holding the GPS data
         */
        void getGPSData(USGPSData_t& gpsData);

        void parse_gps_data(USGPSData_t& gpsData);

        float binary_to_float(uint64_t val);

        double binary_to_double(uint64_t val);

        /**
         * @brief Sends an ASCII command through UART
         *
         * @param command ASCII command string
         */

        void parse_imu_data(USIMUData_t& imuData);
        void sendCommand(const char* command, uint16_t size);

        void recieveResponse(void);

};

#endif /* INC_VECTORNAV_HPP_ */
