#include "InfraredDistanceRangingSensor.h"

InfraredDistanceRangingSensor::InfraredDistanceRangingSensor(int pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT);
}

bool InfraredDistanceRangingSensor::IsCollisionDetected()
{
	return digitalRead(this->pin) == LOW;
}
