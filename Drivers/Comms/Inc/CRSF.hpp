
#ifndef INC_CRSF_HPP_
#define INC_CRSF_HPP_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>


/* Crossfire specifications and structs --------------------------------------*/

#define CRSF_BAUD_RATE 420000
#define CRSF_FRAME_SIZE_MAX 64
#define CRSF_PAYLOAD_SIZE_MAX (CRSF_FRAME_SIZE_MAX-4)


struct CRSFReceieveData {
	// populate the struct with things you want to receieve form the drone

};

struct CRSF_Frame {
	uint8_t gps = 0x02;
	uint8_t battery_sensor = 0x08;
	uint8_t link_statistics = 0x14;
	uint8_t rc_channels_packed = 0x16;
	uint8_t attitude = 0x1E;
	uint8_t flight_mode = 0x21;

	// Extended Header Frames range: 0x28 to 0x96
	uint8_t device_ping = 0x28;
	uint8_t device_info = 0x29;
	uint8_t parameter_settings_entry = 0x2B;
	uint8_t parameter_read = 0x2C;
	uint8_t parameter_write = 0x2D;
	uint8_t command = 0x32;
};

struct CRSF_Payload_Size {
	 uint8_t gps = 15;
	 uint8_t battery_sensor = 8;
	 uint8_t link_statistics = 10;
	 uint8_t rc_channels = 22; ///< 11 bits per channel * 16 channels = 22 bytes.
	 uint8_t attitude = 6;
};


struct CRSF_Address {
	 uint8_t broadcast = 0x00;
	 uint8_t usb = 0x10;
	 uint8_t tbs_core_pnp_pro = 0x80;
	 uint8_t reserved1 = 0x8A;
	 uint8_t current_sensor = 0xC0;
	 uint8_t gps = 0xC2;
	 uint8_t tbs_blackbox = 0xC4;
	 uint8_t flight_controller = 0xC8;
	 uint8_t reserved2 = 0xCA;
	 uint8_t race_tag = 0xCC;
	 uint8_t radio_transmitter = 0xEA;
	 uint8_t crsf_receiver = 0xEC;
	 uint8_t crsf_transmitter = 0xEE;
};

#pragma pack(push, 1)
struct crsf_payload_RC_channels_packed_t {
	// 176 bits of data (11 bits per channel * 16 channels) = 22 bytes
	unsigned chan0 : 11;
	unsigned chan1 : 11;
	unsigned chan2 : 11;
	unsigned chan3 : 11;
	unsigned chan4 : 11;
	unsigned chan5 : 11;
	unsigned chan6 : 11;
	unsigned chan7 : 11;
	unsigned chan8 : 11;
	unsigned chan9 : 11;
	unsigned chan10 : 11;
	unsigned chan11 : 11;
	unsigned chan12 : 11;
	unsigned chan13 : 11;
	unsigned chan14 : 11;
	unsigned chan15 : 11;
};



enum class crsf_parser_state_t : uint8_t {
	unsynced = 0,
	synced
};

/****************************************************************************
 *
 *	Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in
 *	the documentation and/or other materials provided with the
 *	distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *	used to endorse or promote products derived from this software
 *	without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file crsf.h
 *
 * RC protocol definition for CSRF (TBS Crossfire).
 * It is an uninverted protocol at 420000 baudrate.
 *
 * RC channels come in at 150Hz.
 *
 * @author Beat Küng <beat-kueng@gmx.net>
 */


struct crsf_frame_header_t {
	uint8_t device_address;             ///< @see crsf_address_t
	uint8_t length;                     ///< length of crsf_frame_t (including CRC) minus sizeof(crsf_frame_header_t)
};

struct crsf_frame_t {
	crsf_frame_header_t header;
	uint8_t type;                       ///< @see crsf_frame_type_t
	uint8_t payload[CRSF_PAYLOAD_SIZE_MAX + 1]; ///< payload data including 1 byte CRC at end
};

/**
 * Configure an UART port to be used for CRSF
 * @param uart_fd UART file descriptor
 * @return 0 on success, -errno otherwise
 */
int	crsf_config(int uart_fd);


/**
 * Parse the CRSF protocol and extract RC channel data.
 *
 * @param now current time
 * @param frame data to parse
 * @param len length of frame
 * @param values output channel values, each in range [1000, 2000]
 * @param num_values set to the number of parsed channels in values
 * @param max_channels maximum length of values
 * @return true if channels successfully decoded
 */
bool	crsf_parse(const uint64_t now, const uint8_t *frame, unsigned len, uint16_t *values,
			   uint16_t *num_values, uint16_t max_channels);


/**
 * Send telemetry GPS information
 * @param uart_fd UART file descriptor
 * @param latitude latitude [degree * 1e7]
 * @param longitude longitude [degree * 1e7]
 * @param groundspeed Ground speed [km/h * 10]
 * @param gps_heading GPS heading [degree * 100]
 * @param altitude Altitude [meters + 1000m offset]
 * @param num_satellites number of satellites used
 * @return true on success
 */
bool crsf_send_telemetry_gps(int uart_fd, int32_t latitude, int32_t longitude, uint16_t groundspeed,
				      uint16_t gps_heading, uint16_t altitude, uint8_t num_satellites);


/**
 * Send telemetry Attitude information
 * @param uart_fd UART file descriptor
 * @param pitch Pitch angle [rad * 1e4]
 * @param roll Roll angle [rad * 1e4]
 * @param yaw Yaw angle [rad * 1e4]
 * @return true on success
 */
bool crsf_send_telemetry_attitude(int uart_fd, int16_t pitch, int16_t roll, int16_t yaw);

/**
 * Send telemetry Flight Mode information
 * @param uart_fd UART file descriptor
 * @param flight_mode Flight Mode string (max length = 15)
 * @return true on success
 */
bool crsf_send_telemetry_flight_mode(int uart_fd, const char *flight_mode);

