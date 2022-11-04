#ifndef INC_BMX160_HPP_
#define INC_BMX160_HPP_

#include "imu.hpp"

class MPU6050: public IMU {

public:

	static IMU& getInstance();

	MPU6050(const MPU6050*) = delete;

	void GetResult(IMUData_t &Data);

private:

	MPU6050();

	void IMUInit(void);


};

#endif /* INC_MPU6050_HPP_ */