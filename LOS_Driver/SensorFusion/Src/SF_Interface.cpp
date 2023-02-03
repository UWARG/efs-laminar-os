#include "../Inc/SF_Interface.h"

#include "../Inc/SensorFusion.hpp"


void SensorFusionInterfaceInit(void) {
	SF_Init();
}

void SensorFusionInterfaceExecute(void) {
	// will not be used (should call on los pos instead)
	//SFError_t err = SF_GenerateNewResult();
}
