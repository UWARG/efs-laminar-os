/*
 * Xbee.cpp
 *
 *  Created on: Aug 20, 2022
 *      Author: Aaditya
 */

#include "Xbee.hpp"
#include "main.h"
#include "usart.h"

#define UART_TIMEOUT 100

#define DRONE_BASIC_PAYLOAD_TYPE 1

void changeEndian(uint8_t* val, int size) {
	uint8_t temp;
	for (int x = 0; x < size/2; x++) {
		temp = val[x];
		val[x] = val[size - 1 - x];
		val[size - 1 - x] = temp;
	}
}

void TransmitMessage(DroneBasicPayload* payload) {
	Packet packet = {};
	TransmitFrameHeader tf = {};

	packet.time = HAL_GetTick();
	packet.payloadType = DRONE_BASIC_PAYLOAD_TYPE;

	uint8_t checksum = 0xFF;

	uint8_t rawPacket[sizeof(TransmitFrameHeader) + sizeof(Packet) + sizeof(DroneBasicPayload) + sizeof(checksum)];


	uint8_t* tfArr = (uint8_t*)&tf;
	uint8_t* packetArr = (uint8_t*)&packet;
	uint8_t* payloadArr = (uint8_t*)payload;

	tf.messageLength = sizeof(TransmitFrameHeader) + sizeof(Packet) + sizeof(DroneBasicPayload) - 3;

	tf.shortAddress = (tf.shortAddress & 0xFF00) >> 8 | (tf.shortAddress & 0x00FF) << 8;

	changeEndian((uint8_t*)&tf.destAddress, sizeof(tf.destAddress));

	rawPacket[0] = tfArr[0];

	// this looks sketchy but it converts message length into big endian
	rawPacket[1] = tfArr[2];
	rawPacket[2] = tfArr[1];

	int index = 3;
	for (int x = 3; x < sizeof(TransmitFrameHeader); x++) {
			rawPacket[index] = tfArr[x];
			checksum -= tfArr[x];
			index++;
	}

	for (int x = 0; x < sizeof(Packet);x++) {
		rawPacket[index] = packetArr[x];
		checksum -= packetArr[x];
		index++;
	}

	for (int x = 0; x < sizeof(DroneBasicPayload);x++) {
			rawPacket[index] = payloadArr[x];
			checksum -= payloadArr[x];
			index++;
	}

	rawPacket[index] = checksum;

	HAL_UART_Transmit(&huart2, rawPacket, sizeof(rawPacket),UART_TIMEOUT);
}
