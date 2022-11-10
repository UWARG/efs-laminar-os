#ifndef LOS_D_STORAGE_DEVICE_HPP_
#define LOS_D_STORAGE_DEVICE_HPP_

class StorageDevice {
	public:
		/* Check if a location exists in the storage device */
		virtual bool checkExist(const char* location) = 0;

		/* Read bytes from a location with an optional offset */
		virtual uint8_t read(const char* location, char data[], size_t size, size_t offset = 0) = 0;

		/* Write bytes from a location with an optional offset */
		virtual uint8_t write(const char* location, const char data[], size_t size, size_t offset = 0) = 0;

		/* Returns the length of the data at a location */
		virtual size_t length(const char* location) = 0;

		/* Clean up the storage device after I/O operations */
		virtual uint8_t cleanup() = 0;
};

#endif
