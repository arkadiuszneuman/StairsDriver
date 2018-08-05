#include "StairsLedDriver.h"
#include "Logger.h"

StairsLedDriver stairsLedDriver;
InfraredDistanceRangingSensor bottomStairsSensor(14); //D5
InfraredDistanceRangingSensor upperStairsSensor(12); //D6
Logger logger;

void setup() {
	logger.Init();
	stairsLedDriver.Begin(logger, 3);
}

void loop() {
	stairsLedDriver.Update();

	if (bottomStairsSensor.IsCollisionDetected())
	{
		logger.LogLine("Bottom stairs collision detected");
		stairsLedDriver.GoUp();
	}

	if (upperStairsSensor.IsCollisionDetected())
	{
		logger.LogLine("Upper stairs collision detected");
		stairsLedDriver.GoDown();
	}
}