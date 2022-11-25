#include "SF_Interface.h"

#include "SensorFusion.hpp"

void SensorFusionInterfaceInit(void) {
	SF_Init();
}

void SensorFusionInterfaceExecute(IMUData_t imuData, GpsData_t GpsData, AltimeterData_t altimeterData, AirspeedData_t airspeedData) {
	SFError_t err = SF_GenerateNewResult(imuData,  GpsData, altimeterData, airspeedData);
}