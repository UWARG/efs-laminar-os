#ifndef INC_NEOM8_HPP_
#define INC_NEOM8_HPP_

#include "gps.hpp"

/*
 * GPS spews data without us needing to ask for it
 */
class NEOM8 : public Gps
{
	public:
		NEOM8(const NEOM8*) = delete;
		static NEOM8* GetInstance();

		 /**GetResult should:
		 * 1. Reset dataIsNew flag
		 * 2. Transfers raw data from variables to struct
		 * 3. Updates utcTime and status values in struct as well
		 * */
		void GetResult(GpsData_t& Data);

		/**
		 * Returns the buffer used to receive GPS UART signals
		 */
		uint8_t* get_byte_collection_buffer();

		void set_uart_data_is_new(bool val);

	private:
		//Constructor
		NEOM8();

		//Static instance
		static NEOM8* gpsInstance;

		// Buffers
		uint8_t gga_buffer[GPS_UART_BUFFER_SIZE]; //buffer for pasing gga (positional packets)
		uint8_t vtg_buffer[GPS_UART_BUFFER_SIZE]; //buffer for parsing vtg packets (velocity packets)
		uint8_t uart_buffer[GPS_UART_BUFFER_SIZE]; //buffer for parsing vtg packets (velocity packets)
		uint8_t byte_collection_buffer[GPS_UART_BUFFER_SIZE];
		bool uartDataIsNew;

		bool dataAvailable;
		bool configured; //if the gps module has been initialized and configured
		GpsData_t gpsData;

		/**
		 * Given an NMEA string starting after the $, verifies the integrity of the string
		 * using the checksum
		 * @param string
		 * @return True if string is a valid gps string, false otherwise
		 */
		bool is_check_sum_valid(uint8_t* string);

		/**
		 * Methods used for simple conversions when parsing NMEA messages
		 */
		uint8_t uint8_to_hex(unsigned int checkSumHalf);
		uint8_t ascii_to_hex(uint8_t asciiSymbol);

		/**
		 * Parses the VTG NMEA message and populates the GpsData_t sruct
		 */
		void parse_vtg(uint8_t* data);

		/**
		 * Parses the GGA NMEA message and populates the GpsData_t sruct
		 */
		void parse_gga(uint8_t* data);

		/**
		 * Goes through byte_collection_buffer, finds the messages we care about, and calls the appropriate parsing functions
		 */
		void parse_gpsData();

};

#endif /* INC_NEOM8_HPP_ */