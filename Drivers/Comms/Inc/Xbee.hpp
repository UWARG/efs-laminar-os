/*
 * Xbee.hpp
 *
 *  Created on: Aug 26, 2022
 *      Author: Aaditya
 */

#ifndef COMMS_INC_XBEE_HPP_
#define COMMS_INC_XBEE_HPP_

#include <stdint.h>

#define GROUND_ADDRESS 0x0013A20041B16D1C

/*
 *  Contains competition/drone agnostic data that will be needed regardless
 *  of drone type and competition requirements. GPS and IMU data as well as the
 *  current motor outputs.
 *
 */
struct __attribute__ ((packed)) DroneBasicPayload {

		float latitude;
		float longitude;
		float altitude;

		float yaw;
		float pitch;
		float roll;

		uint8_t motorOutputs[12];
};

/*
 * Header to specify what type of payload is being sent, as well as the time its being sent at.
 *
*/
struct __attribute__ ((packed)) Packet {
	uint32_t time;
	uint8_t payloadType;

	//TODO add CRC
};

/*
 * Zigbee 3.0 transmit frame. Used to send data from one xbee to another.
 *
 */

struct __attribute__ ((packed)) TransmitFrameHeader {
	uint8_t startDelim = 0x7E;
	uint16_t messageLength;
	uint8_t frameType = 0x10;
	uint8_t frameID = 0x01;
	uint64_t destAddress = GROUND_ADDRESS;
	uint16_t shortAddress = 0xFFFE; // FFFE in little endian
	uint8_t broadcastRadius = 0x00;
	uint8_t options = 0x00;


};

void TransmitMessage(DroneBasicPayload* payload);


#endif /* COMMS_INC_XBEE_HPP_ */
