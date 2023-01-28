#include "../inc/LOS_Position_Interface.h"

#include "../inc/LOS_Position.hpp"


void LOS_Pos_Init(void) {
	LOS_Position* losPosObj = &LOS_Position::getInstance();
}

void LOS_Pos_Execute(void) {
	LOS_Position* losPosObj = &LOS_Position::getInstance();
    losPosObj->updatePosition();
}
