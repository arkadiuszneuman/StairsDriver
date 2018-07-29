// DistanceRangingSensor.h

#ifndef _DISTANCERANGINGSENSOR_h
#define _DISTANCERANGINGSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class InfraredDistanceRangingSensor
{
private:
	int pin;
public:
	InfraredDistanceRangingSensor(int pin);
	bool IsCollisionDetected();
};

#endif

