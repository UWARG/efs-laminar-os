#ifndef SENSOR_FUSION_INTERFACE_H
#define SENSOR_FUSION_INTERFACE_H

#include "LOS_Position.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void SensorFusionInterfaceInit(void);
void SensorFusionInterfaceExecute(IMUData_t, GpsData_t, AltimeterData_t, airspeedData_t);

#ifdef __cplusplus
}
#endif 

#endif