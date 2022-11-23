#ifndef INC_BMX160_HPP_
#define INC_BMX160_HPP_

#include "imu.hpp"

class IMUMock : public IMU {

public:

	static IMU& getInstance();

	void GetResult(IMUData_t &Data);
	void updateData();
	IMUMock();
private:

	void setAllPowerModesToNormal(void);
	void configAcc(void);
	void configGyro(void);
	void configMag(void);

	void writeRegister(uint8_t reg, uint8_t val);
	void readRegister(uint8_t const regAddr, uint8_t *data, uint8_t len);

	void calibrate(void);

	void IMUInit(void);

	bool scan();

	// Variables:
	uint8_t rawImuData[20];
	IMUData_t IMUCalibration;
	uint8_t powerStatus;
};

#endif 
