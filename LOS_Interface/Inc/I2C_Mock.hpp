/*
 *	I2C mocked interface
 * 	Author: Jack Greenwood
 *	Date: November 10, 2022
 */

#ifndef I2C_MOCK_HPP_
#define I2C_MOCK_HPP_

#include "stm32f4xx_hal_gpio.h" // fix these later" // ^
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2c.h"
#include <cstdint>

// Could use cleaning
#define I2C_SDA_LOW  HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_RESET);
#define I2C_SDA_HIGH HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET);

#define I2C_SCL_LOW HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_RESET);
#define I2C_SCL_HIGH HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET);

#define I2C_Delay HAL_Delay(0.005); // 5 microseconds delay time

class I2C_Comms {

  private:


  public:
    /**
     * @brief Initialize I2C interface
    */
	void I2C_Init(); // adopted from the HAL I2C init function

	/*
     * @brief I2C communication start condition
     */
	void I2C_Start_Comms();

	/*
     * @brief I2C communication stop condition
	*/
	void I2C_Stop_Comms();

    /*
     * @brief Writing a bit in I2C, breakdown of writing a byte
     *
     * @param writing individual bits to somewhere?
	*/
	void I2C_Write_Bit(uint8_t bit);

    /*
     * @brief Ensure the SDA line is high
	*/
	uint8_t I2C_Read_SDA();

    /*
     * @brief Reading a bit in I2C, breakdown of reading a byte
	*/
	uint8_t I2C_Read_Bit();

    /*
     * @brief Writing a byte in I2C
     *
     * @param Data (byte) we are sending over I2C
     *
     * @param Check if I2C communication has started
     *
     * @param Check if I2C communication has stopped
	*/
	bool I2C_Write_Byte(uint8_t data, bool start, bool stop);

    /*
     * @brief Writing a bit in I2C, breakdown of writing a byte
     *
     * @param Ack used to send more data
     *
     * @param Specify if we would like to stop I2C comms
	*/
	uint8_t I2C_Read_Byte(bool ack, bool stop);

    /*
     * @brief Transmitting a byte in I2C
     *
     * @param Data we would like to send
     *
     * @param Address we would like to send data to (change to bool?)
	*/
	bool I2C_Transmit_Byte(uint8_t data, uint8_t address);

    /*
     * @brief Receiving a byte in I2C
     *
     * @param Address we would like to receive from
	*/
	uint8_t I2C_Receive_Byte(uint8_t address);

    /*
     * @brief Transmit function - sending one more byte than prior
     *
     * @param Address of our slave device
     *
     * @param Register we would like to transmit to
     *
     * @param Data (byte) we would like to transmit (change from pointer?)
     *
     * @param Size of data we would like to transmit
     *
     * @param Max acceptable time until timeout
	*/
	bool I2C_Transmit_Byte_Data(uint8_t address, uint8_t reg, uint8_t data);

    /*
     * @brief Recieve function for data from specified register
     *
     * @param Register we would like to receive from
	*/
	uint8_t I2C_Receive_Byte_Data(uint8_t address, uint8_t reg);

    /*
     * @brief Top of the chain transmit function
     *
     * @param Adress we would like to transmit to
     *
     * @param data we would like to send represesnted as an array
     *
     * @param size of data we are sending
     *
     * @param Max acceptable time until timeout
	*/
	bool I2C_Transmit(uint8_t address, uint8_t data[], uint8_t size);

    /*
     * @brief Recieve function for data from specified register
     *
     * @param Register we would like to receive from
     * 
     * @param place we would like to store our bytes 
     *
     * @param Size of register we are receiving from 
     *
     * @param Number of bytes we would like to receive
	*/
	bool I2C_Receive(uint8_t address, uint8_t reg[], uint8_t *data, uint8_t reg_size, uint8_t size);

};

#endif /* I2C_MOCK_HPP_  Mock I2C interface */
