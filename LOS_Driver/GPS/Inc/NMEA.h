/*
 * NMEA.h
 *
 *  Created on: 26-Feb-2022
 *      Author: arunr
 *      Edit by: Hardy Yu in Feb-2022
 */

#ifndef INC_NMEA_H_
#define INC_NMEA_H_


typedef struct {
	int hour;
	int min;
	int sec;
	int allinsec;
}TIME;

typedef struct {
	float latitude;
	char NS;
	float longitude;
	char EW;
}LOCATION;

typedef struct {
	float altitude;
	char unit;
}ALTITUDE;

typedef struct {
	int Day;
	int Mon;
	int Yr;
}DATE;

typedef struct {
	LOCATION lcation;
	TIME tim;
	int isfixValid; //0 = No GPS, 1 = GPS fix, 2 = DGSP Fix, 3 = Estimated/Dead Recoking Fix
	ALTITUDE alt;
	int numofsat;
}GGASTRUCT;

typedef struct {
	DATE date;
	float speed;
	float course;
	int isValid;
}RMCSTRUCT;

typedef struct {
	GGASTRUCT ggastruct;
	RMCSTRUCT rmcstruct;
}GPSSTRUCT;

int decodeGGA (char *GGAbuffer, GGASTRUCT *gga);

int decodeRMC (char *RMCbuffer, RMCSTRUCT *rmc);

#endif /* INC_NMEA_H_ */

