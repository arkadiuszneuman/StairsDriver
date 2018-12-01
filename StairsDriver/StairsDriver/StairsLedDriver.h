// StairsLedDriver.h

#ifndef _STAIRSLEDDRIVER_h
#define _STAIRSLEDDRIVER_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "LedStrip.h"
#include "InfraredDistanceRangingSensor.h"
#include "Logger.h"
#include "ConfigManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define STAIRS_OFF 0
#define STAIRS_GO_UP 1
#define STAIRS_GO_DOWN 2
#define STAIRS_GO_UP_AND_DOWN 3

class StairsLedDriver
{
private:
	Adafruit_PWMServoDriver pwm;
	LedStrip** ledStrips;
	Logger logger;
	int stairsCount;
	unsigned long int timeOfLastSensorDetected = 0;
	int timeForLedsSwitchedOn = 15000;
	int delayForNextStairToSwitchOn = 2000;
	int millisCountForFullBrightness = 10000;
	int state = STAIRS_OFF;
	bool ShouldFadeLed(LedStrip* ledStrip, int delay, bool ignoreFullBrightness = false);
public:
	void Begin(Logger &logger, ConfigManager &configManager);
	void Update();
	void GoUp();
	void GoDown();
	void InstantlyOffAllLeds();
	void SetMinLevel(int minLevel);
	void SetMaxLevel(int maxLevel);
};

#endif

