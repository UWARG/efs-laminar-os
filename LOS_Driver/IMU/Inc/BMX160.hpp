#ifndef INC_BMX160_HPP_
#define INC_BMX160_HPP_

#include "imu.hpp";

class BMX160: public IMU {

public:

	static IMU& getInstance();

	BMX160(const BMX160*) = delete;

	void GetResult(IMUData_t &Data);
	void updateData();

private:

	BMX160();
	void setAllPowerModesToNormal(void);
	void configAcc(void);
	void configGyro(void);
	void configMag(void);

	void writeRegister(uint8_t reg, uint8_t val);
	void readRegister(uint8_t const regAddr, uint8_t *data, uint8_t len);

	void calibrate(void);

	void IMUInit(void);

	bool scan(void); // Check that the slave device exists

	// Variables:
	uint8_t rawImuData[20];
	IMUData_t IMUCalibration;
	uint8_t powerStatus;
};

#endif 