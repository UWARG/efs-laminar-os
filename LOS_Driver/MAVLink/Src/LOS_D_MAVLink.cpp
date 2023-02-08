/*
 * LOS_D_MAVLink.cpp
 *
 *  Created on: Feb 2, 2023
 *      Author: Stanley Tang
 */

#include "LOS_D_MAVLink.hpp"

MAVLink::MAVLink(UART_HandleTypeDef* uart_handle)
    :
    uart_handle(uart_handle)
{
	memset(&last_status, 0, sizeof(mavlink_status_t));
}

uint8_t MAVLink::readMessage(mavlink_message_t &message)
{
	uint8_t byte = 0;
	uint8_t end_of_msg = 0;
	mavlink_status_t status = {};
	uint8_t success = 1;

	/* Parse incoming packet one byte at a time. */
	for (uint16_t i = 0; i < MAVLINK_MAX_PACKET_LEN; ++i) {
		HAL_UART_Receive(uart_handle, &byte, 1, 100);

		end_of_msg = mavlink_parse_char(MAVLINK_COMM_1, byte, &message, &status);

		if (last_status.packet_rx_drop_count != status.packet_rx_drop_count) {
			/* Packet dropped! */
			success = 0;
		}

		last_status = status;

		if (end_of_msg) {
			break;
		}
	}

	return success;
}

void MAVLink::writeMessage(const mavlink_message_t &msg)
{
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

	HAL_UART_Transmit(uart_handle, buf, len, 1000);
}

void MAVLink::sendCommandLong(mavlink_command_long_t command_long)
{
    command_long.target_system = plane_system_id;
	command_long.target_component = plane_component_id;

    mavlink_message_t message = {};
	mavlink_msg_command_long_encode(system_id, component_id, &message, &command_long);

	writeMessage(message);
}

void MAVLink::sendHeartbeat()
{
	mavlink_heartbeat_t heartbeat = {};
	heartbeat.type = MAV_TYPE_GCS; /* We are representing ground (control) station. */
	heartbeat.autopilot = MAV_AUTOPILOT_INVALID;

	mavlink_message_t message = {};
	mavlink_msg_heartbeat_encode(system_id, component_id, &message, &heartbeat);

	writeMessage(message);
}

void sendInitialConfigs()
{
    /* Tell the plane to VTOL hover over a waypoint when it's reached in guided mode. */
    mavlink_param_set_t vtol_hover_param = {};
    vtol_hover_param.target_system = plane_system_id;
    vtol_hover_param.target_system = plane_component_id;
    vtol_hover_param.param_id = "Q_GUIDED_MODE";
    vtol_hover_param.param_value = 1;
    vtol_hover_param.param_type = MAV_PARAM_TYPE_UINT8;

    mavlink_message_t message = {};
    mavlink_msg_param_set_encode(system_id, component_id, &message, &vtol_hover);

    writeMessage(message);
}

void MAVLink::sendArmDisarm(const bool arm)
{
    mavlink_command_long_t command_long = {};
    command_long.command = MAV_CMD_COMPONENT_ARM_DISARM;
    command_long.param1 = (float)arm;

    sendCommandLong(command_long);
}

void MAVLink::sendFlightModeChange(const PLANE_MODE flight_mode)
{
    mavlink_command_long_t command_long = {};
    command_long.command = MAV_CMD_DO_SET_MODE;
    command_long.param2 = (float)flight_mode;

    sendCommandLong(command_long);
}

void MAVLink::sendVTOLTakeOff(const float altitude)
{
    mavlink_command_long_t command_long = {};
    command_long.command = MAV_CMD_NAV_VTOL_TAKEOFF;
    command_long.param7 = altitude;

    sendCommandLong(command_long);
}

void MAVLink::sendWaypointNav(const float x, const float y, const float z, const float acceptable_range)
{
	mavlink_command_long_t command_long = {};
	command_long.command = MAV_CMD_NAV_WAYPOINT;
	command_long.confirmation = 1;
	command_long.param2 = acceptable_range;
	command_long.param5 = x;
	command_long.param6 = y;
	command_long.param7 = z;

	sendCommandLong(command_long);
}

void MAVLink::sendClearMissions()
{
    mavlink_mission_clear_all_t clear_all = {};
    clear_all.target_system = plane_system_id;
    clear_all.target_component = plane_component_id;
    clear_all.mission_type = MAV_MISSION_TYPE_ALL;

    mavlink_message_t message = {};
    mavlink_msg_mission_clear_all_encode(system_id, component_id, &message, &clear_all);

    writeMessage(message);
}

uint8_t MAVLink::receiveMessage(MAVLink_Message_t& mavlink_message)
{
	mavlink_message_t message = {};
	uint8_t success = 0;

	if (readMessage(message)) {
		success = 1;
		mavlink_message.message_id = message.msgid;

		switch (message.msgid) {
			case MAVLINK_MSG_ID_HEARTBEAT:
				mavlink_msg_heartbeat_decode(&message, &(mavlink_message.heartbeat));
				break;
			case MAVLINK_MSG_ID_COMMAND_ACK:
				mavlink_msg_command_ack_decode(&message, &(mavlink_message.command_ack));
				break;
			default:
				success = 0;
		}
	}

	return success;
}
