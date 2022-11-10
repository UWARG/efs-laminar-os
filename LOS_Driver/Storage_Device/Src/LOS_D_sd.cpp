#include "LOS_D_sd.hpp"

SDCard::SDCard()
{
	/* Mount FatFS to default drive */
	f_mount(&fs, "", 1);

	memset(cur_open_file_path, '\0', MAX_FILE_PATH_LEN);
}

uint8_t SDCard::open(const char* location)
{
	uint8_t res = 0;

	if (!(has_file_open && strcmp(location, cur_open_file_path) == 0)) {
		if (has_file_open) {
			/* The current opened file is NOT the file we are trying to open */
			res = f_close(&cur_open_file);
		}

		if (res == 0) {
			res = f_open(&cur_open_file, location, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
		}

		if (res == 0) {
			has_file_open = true;
			memset(cur_open_file_path, '\0', MAX_FILE_PATH_LEN);
			strcpy(cur_open_file_path, location);
		}
	}

	return res;
}

bool SDCard::checkExist(const char* location)
{
	FIL tmp_file;
	uint8_t res = f_open(&tmp_file, location, FA_READ);

	if (res == 0) {
		res = f_close(&tmp_file);
	}

	return res == 0;
}

uint8_t SDCard::read(const char* location, char data[], size_t size, size_t offset)
{
	uint8_t res = open(location);

	if (res == 0) {
		res = f_lseek(&cur_open_file, offset);
	}

	if (res == 0) {
		size_t bytes_read;
		res = f_read(&cur_open_file, data, size, &bytes_read);
	}

	return res;
}

uint8_t SDCard::write(const char* location, const char data[], size_t size, size_t offset)
{
	uint8_t res = open(location);

	if (res == 0) {
		res = f_lseek(&cur_open_file, offset);
	}

	if (res == 0) {
		size_t bytes_written;
		res = f_write(&cur_open_file, data, size, &bytes_written);
	}

	return res;
}

size_t SDCard::length(const char* location)
{
	size_t res = open(location);

	if (res == 0) {
		res = f_size(&cur_open_file);
	}

	return res;
}

uint8_t SDCard::cleanup()
{
	uint8_t res = 0;

	if (has_file_open) {
		res = f_close(&cur_open_file);
		has_file_open = false;
		memset(cur_open_file_path, '\0', MAX_FILE_PATH_LEN);
	}

	return res;
}

SDCard::~SDCard()
{
	cleanup();

	/* Dismount FatFS */
	f_mount(NULL, "", 0);
}
