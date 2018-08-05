#include "StairsLedDriver.h"

StairsLedDriver stairsLedDriver;
InfraredDistanceRangingSensor bottomStairsSensor(14); //D5
InfraredDistanceRangingSensor upperStairsSensor(12); //D6

void setup() {
	Serial.begin(9600);
	stairsLedDriver.Begin(3);
}

void loop() {
	stairsLedDriver.Update();

	if (bottomStairsSensor.IsCollisionDetected())
	{
		Serial.println("Bottom stairs collision detected");
		stairsLedDriver.GoUp();
	}

	if (upperStairsSensor.IsCollisionDetected())
	{
		Serial.println("Upper stairs collision detected");
		stairsLedDriver.GoDown();
	}
}