#include "LOS_Telem.hpp"

LOS_Telem& LOS_Telem::getInstance() {
    static LOS_Telem instance;
    return instance;
}

LOS_Telem::LOS_Telem() {}

void LOS_Telem::init(){
    //TODO: Initialize telemetry
}

bool LOS_Telem::get_from_ground(Data_From_Ground_t &dataFromGround){
    //TODO: Call drivers to get data from ground
}

void LOS_Telem::send_to_ground(Data_To_Ground_t &dataToGround){
    //TODO: Call drivers to send data to ground
}