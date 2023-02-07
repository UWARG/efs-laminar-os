/*
 * LOS_D_MAVLink.hpp
 *
 *  Created on: Feb 2, 2023
 *      Author: Stanley Tang
 */

#ifndef INC_LOS_D_MAVLINK_HPP_
#define INC_LOS_D_MAVLINK_HPP_

#include "MAVLink\ardupilotmega\mavlink.h"
#include "stm32l5xx_hal.h"

typedef struct MAVLink_Message {
	uint8_t message_id;
	mavlink_heartbeat_t heartbeat;
	mavlink_command_ack_t command_ack;
} MAVLink_Message_t;

class MAVLink {
	public:
		void sendHeartbeat();
		void sendNavCommand(float x, float y, float z, float radius);

		uint8_t receiveMessage(MAVLink_Message_t& mavlink_message);

		MAVLink(UART_HandleTypeDef* uart_handle);

		static MAVLink& getInstance(void);

	private:
        const UART_HandleTypeDef* uart_handle;
		/* We are representing ground station, so our system ID and
		 * component ID are 255 and 1. */
		const uint8_t system_id = 255;
		const uint8_t component_id = 1;
		/* Plane system ID and component ID */
		const uint8_t plane_system_id = 1;
		const uint8_t plane_component_id = 1;

		mavlink_status_t last_status;

		uint8_t readMessage(mavlink_message_t &msg);
		void writeMessage(const mavlink_message_t &msg);
};

#endif /* INC_LOS_D_MAVLINK_HPP_ */
