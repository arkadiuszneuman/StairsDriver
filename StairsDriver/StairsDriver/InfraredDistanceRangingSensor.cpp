#include "InfraredDistanceRangingSensor.h"

InfraredDistanceRangingSensor::InfraredDistanceRangingSensor(int pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT);
}

bool InfraredDistanceRangingSensor::IsCollisionDetected()
{
	int read = digitalRead(this->pin);
	if (read == LOW)
	{
		++readCount;
		if (readCount == SENSOR_VALID_READ_COUNT)
		{
			readCount = 0;
			return true;
		}

		return false;
	}
	
	readCount = 0;
	return false;
}
