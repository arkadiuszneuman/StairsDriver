// DistanceRangingSensor.h

#ifndef _DISTANCERANGINGSENSOR_h
#define _DISTANCERANGINGSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SENSOR_VALID_READ_COUNT 3

class InfraredDistanceRangingSensor
{
private:
	int pin;
	int readCount = 0;
public:
	InfraredDistanceRangingSensor(int pin);
	bool IsCollisionDetected();
};

#endif

