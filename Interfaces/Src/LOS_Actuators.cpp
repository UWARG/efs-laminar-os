/*
 * LOS_Actuators.cpp
 *
 *  Created on: May 25, 2022
 *      Author: anthony
 */




#include "../Inc/LOS_Actuators.hpp"

LOS_Actuators::LOS_Actuators() {
    this->pwm = new PWMChannel();
}

void LOS_Actuators::set(uint8_t channel, float percent) {
    this->pwm->set(channel, percent);
}

void LOS_Actuators::set(PID_Output_t * quad_out) {
    this->pwm->set(front_left, quad_out->frontLeftMotorPercent);
    this->pwm->set(front_right, quad_out->frontRightMotorPercent);
    this->pwm->set(back_right, quad_out->backRightMotorPercent);
    this->pwm->set(back_left, quad_out->backLeftMotorPercent);
}

void LOS_Actuators::__configure_quadrotor(uint8_t front_left, uint8_t front_right, uint8_t back_right, uint8_t back_left){
    this->front_left = front_left;
    this->front_right = front_right;
    this->back_right = back_right;
    this->back_left = back_left;
}
