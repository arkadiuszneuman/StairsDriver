// StairsLedDriver.h

#ifndef _STAIRSLEDDRIVER_h
#define _STAIRSLEDDRIVER_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "LedStrip.h"
#include "InfraredDistanceRangingSensor.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MILLIS_COUNT_FOR_FULL_BRIGHTNESS 10000
#define STAIRS_OFF 0
#define STAIRS_GO_UP 1
#define STAIRS_GO_DOWN 2
#define STAIRS_GO_UP_AND_DOWN 3

class StairsLedDriver
{
private:
	Adafruit_PWMServoDriver pwm;
	LedStrip** ledStrips;
	int stairsCount;
	unsigned long int timeOfLastSensorDetected = 0;
	unsigned long int timeForLedsSwitchedOn = 15000;
	int delayForNextStairToSwitchOn = 2000;
	int state = STAIRS_OFF;
public:
	void Begin(int stripsCount);
	void Update();
	void GoUp();
	void GoDown();
};

#endif

