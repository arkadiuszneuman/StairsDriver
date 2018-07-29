// StairsLedDriver.h

#ifndef _STAIRSLEDDRIVER_h
#define _STAIRSLEDDRIVER_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "LedStrip.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MILLIS_COUNT_FOR_FULL_BRIGHTNESS 1000

class StairsLedDriver
{
private:
	Adafruit_PWMServoDriver pwm;
	LedStrip** ledStrips;
	int stripsCount;
	unsigned long int temp;
	int state;
public:
	void Begin(int stripsCount);
	void Update();
};

#endif

