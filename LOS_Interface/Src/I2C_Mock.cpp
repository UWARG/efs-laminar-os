/*
	I2C mocked interface
	Author: Jack Greenwood
	Date: November 10, 2022
	Inspired from https://github.com/PascalPolygon/stm32_bitbang_i2c
*/

#include "I2C_Mock.hpp"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2c.h"
#include <cstdint>

void I2C_Comms::I2C_Init() {
	I2C_SDA_HIGH;
	I2C_SCL_HIGH;
	I2C_Delay;
}

void I2C_Comms::I2C_Start_Comms() {
	I2C_SDA_HIGH;   // Make sure the SDA,
	I2C_SCL_HIGH;   // and SCL lines are high
	I2C_Delay;      // Delay for assurance

	I2C_SDA_LOW;    // SDA low first
	I2C_Delay;      // Delay for assurance

	I2C_SCL_LOW;    // SCL low after SDA
	I2C_Delay;      // Delay for assurance
}

void I2C_Comms::I2C_Stop_Comms() {
	I2C_SDA_LOW;    // Make sure the SDA is low
	I2C_Delay;      // Delay for assurance
	I2C_SCL_HIGH;   // SCL high before SDA
	I2C_Delay;      // Delay for assurance

	I2C_SDA_HIGH;     // SDA high after SCL
	I2C_Delay;       // Delay for assurance
}


void I2C_Comms::I2C_Write_Bit(uint8_t bit) {

	if (bit > 0 ) {
		I2C_SDA_HIGH;
	} else {
		I2C_SDA_LOW;
	}

	I2C_Delay;
	I2C_SCL_HIGH;
	I2C_Delay;
	I2C_SCL_LOW;
}

uint8_t I2C_Comms::I2C_Read_SDA()
{
    if (HAL_GPIO_ReadPin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin) == GPIO_PIN_SET) {
        return 1;
    } else {
        return 0;
    }

    return 0;
}

uint8_t I2C_Comms::I2C_Read_Bit() {
	uint8_t read; // thing we would like to read

	I2C_SDA_HIGH;
	I2C_Delay;
	I2C_SCL_HIGH;
	I2C_Delay;

	read = I2C_Read_SDA();

	I2C_SCL_LOW;

	return read;
}


bool I2C_Comms::I2C_Write_Byte(uint8_t data, bool start, bool stop) {
	uint8_t ack = 0;
	if (start) {
		I2C_Start_Comms();
	}

	for (uint8_t i = 0; i < 8; i++) {
		I2C_Write_Bit(data & 80); // I2C uses big endian, so we want to isolate MSB
		data <<= 1;
	}

	ack = I2C_Read_Bit();

	if (stop) {
		I2C_Stop_Comms();
	}

	return !ack; // due to the nature of the ack bit, we invert
}


uint8_t I2C_Comms::I2C_Read_Byte(bool ack, bool stop) {
	uint8_t byte = 0;

	for (uint8_t i = 0; i < 8; i++) {
		byte <<= 1;
		byte |= I2C_Read_Bit();
	}

	if (ack) {
		I2C_Write_Bit(0);
	} else {
		I2C_Write_Bit(1);
	}

	if (stop) {
		I2C_Stop_Comms();
	}

	return byte;

}


bool I2C_Comms::I2C_Transmit_Byte(uint8_t data, uint8_t address) {

	if (I2C_Write_Byte(address, true, false)) {
		if (I2C_Write_Byte(address, true, false)) {
			return true;
		}
	}

	I2C_Stop_Comms();
	return false;
}


uint8_t I2C_Comms::I2C_Receive_Byte(uint8_t address) {

	if (I2C_Write_Byte(address << 1 | 0x01, true, false)) {
		return I2C_Read_Byte(false, true);
	}

	return 0;
}


bool I2C_Comms::I2C_Transmit_Byte_Data(uint8_t address, uint8_t reg, uint8_t data) {
	if (I2C_Write_Byte(address << 1, true, false)) {
		if (I2C_Write_Byte(reg, false, false)) {
			if (I2C_Write_Byte(data, true, false)) {
				return true;
			}
		}
	}
	I2C_Stop_Comms();
	return false;
}


uint8_t I2C_Comms::I2C_Receive_Byte_Data(uint8_t address, uint8_t reg) {
	if (I2C_Write_Byte(address << 1, true, false)) {
		if (I2C_Write_Byte(reg, false, false)) {
			if (I2C_Write_Byte((address << 1) | 0x01, true, false)) {
				return I2C_Read_Byte(false, true);
			}
		}
	}
	I2C_Stop_Comms();
	return 0;
}

bool I2C_Comms::I2C_Transmit(uint8_t address, uint8_t data[], uint8_t size)
{
    if (I2C_Write_Byte(address, true, false)) // first byte
    {
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                if (I2C_Write_Byte(data[i], false, true))
                    return true;
            }
            else
            {
                if (!I2C_Write_Byte(data[i], false, false))
                    break; //last byte
            }
        }
    }

    I2C_Stop_Comms();
    return false;
}

bool I2C_Comms::I2C_Receive(uint8_t address, uint8_t reg[], uint8_t *data, uint8_t reg_size, uint8_t size)
{
    if (I2C_Write_Byte(address, true, false))
    {
        for (int i = 0; i < reg_size; i++)
        {
            if (!I2C_Write_Byte(reg[i], false, false))
                break;
        }
        if (I2C_Write_Byte(address | 0x01, true, false)) // start again, send address, read (LSB signifies R or W)
        {
            for (int j = 0; j < size; j++)
            {
                *data++ = I2C_Read_Byte(false, false); // read data
            }
            I2C_Stop_Comms();
            return true;
        }
    }
    I2C_Stop_Comms();
    return false;
}