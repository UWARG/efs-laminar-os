/*
 * LOS_D_MAVLink.hpp
 *
 *  Created on: Feb 2, 2023
 *      Author: Stanley Tang
 */

#ifndef INC_LOS_D_MAVLINK_HPP_
#define INC_LOS_D_MAVLINK_HPP_

#include "MAVLink/ardupilotmega/mavlink.h"
#include "main.h"
#include <string.h>

enum class MAVLinkACKType {
    PARAM,
    COMMAND,
    MISSION
};

enum class MAVLinkMessageType {
    ACK,
    HEARTBEAT
};

typedef struct MAVLinkACK {
    MAVLinkACKType type;
    mavlink_param_value_t param;
    uint8_t ack_result; /* Only applies to command and mission ACKs. */
    uint16_t command;
    uint16_t mission;
} MAVLinkACK_t;

typedef struct MAVLinkMessage {
	MAVLinkMessageType type;
	mavlink_heartbeat_t heartbeat;
	MAVLinkACK_t ack;
} MAVLinkMessage_t;

class MAVLink {
	public:
        /* Send a heartbeat message to sync with ArduPilot. This needs to be done
         * at ideally 1Hz and no less than 0.2Hz.
         */
		void sendHeartbeat();

        /* Set initial config parameters. This needs to be done before flight. */
        MAVLinkACK_t sendInitialConfigs();

        /* Arm (arm=1) or disarm (arm=0) the plane. */
        MAVLinkACK_t sendArmDisarm(const bool arm);

        /* Change the flight mode of the plane.
         * 
         * Plane flight modes we should use:
         * - PLANE_MODE_AUTO
         * - PLANE_MODE_GUIDED
         * - PLANE_MODE_QLOITER
         * - PLANE_MODE_QLAND
         * - PLANE_MODE_MANUAL
         */
        MAVLinkACK_t sendFlightModeChange(const PLANE_MODE flight_mode);

        /* Do a VTOL take-off. The plane must be in AUTO mode. */
        MAVLinkACK_t sendVTOLTakeOff(const float altitude);

        /* Add a waypoint to navigate. The plane will consider the waypoint reached when it's
         * within acceptable_range of the waypoint. The plane must be in GUIDED mode. */
		MAVLinkACK_t sendWaypointNav(const float x, const float y, const float z, const float acceptable_range);

        /* Clear all missions, including VTOL take-off and waypoint navigation. */
        MAVLinkACK_t sendClearMissions();

        /* Receive a message from ArduPilot. */
		bool receiveMessage(MAVLinkMessage_t& mavlink_message);

        /* Check an ACK message against an expected ACK results. */
        bool checkMessageACK(const MAVLinkMessage_t mavlink_message, const MAVLinkACK_t expected_ack);

        /* Constructor */
		MAVLink(UART_HandleTypeDef* uart_handle);

	private:
        UART_HandleTypeDef* uart_handle;
		/* We are representing ground station, so our system ID and
		 * component ID are 255 and 1. */
		const uint8_t system_id = 255;
		const uint8_t component_id = 1;
		/* Plane system ID and component ID */
		const uint8_t plane_system_id = 1;
		const uint8_t plane_component_id = 1;

		mavlink_status_t last_status;

		bool readMessage(mavlink_message_t &msg);
		void writeMessage(const mavlink_message_t &msg);
        void sendCommandLong(mavlink_command_long_t command_long);
        bool compareParamId(const char id1[16], const char id2[16]);
};

#endif /* INC_LOS_D_MAVLINK_HPP_ */
