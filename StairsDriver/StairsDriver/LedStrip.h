// LedStrip.h

#ifndef _LEDSTRIP_h
#define _LEDSTRIP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Logger.h"
#include "FadeInfo.h"

#define MAX_LED_BRIGHTNESS 4096

class LedStrip
{
private:
	Adafruit_PWMServoDriver pwm;
	Logger logger;
	FadeInfo* fadePlan;
	int milisCountForFullBrightness;
	int channel;
	int currentBrightness = 0;
	int brightnessToSet = 0;
	int minLevelPwm = 0;
	bool brightnessGoingUp = true;
	bool isFadingPlanned = false;
	bool isFading = false;
	double previousTimeLeftPercent = 0;
	unsigned long millisStart = 0;
	void SetPWM(int pwmValue);
	int minLevel = 0;
	int maxLevel = 100;
public:
	LedStrip(Logger &logger, Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness);
	void Fade(int brightnessPercent, int delay = 0);
	void Update();
	bool IsFading();
	bool IsFadePlanned();
	bool IsBrightnessGoingUp();
	double GetCurrentBrightness();
	void SetMinLevel(int minLevel);
	void SetMaxLevel(int maxLevel);
	int GetMinLevelPwm();
	int GetMaxLevelPwm();
	bool IsFadedToMinLevel();
	bool IsFadedToMaxLevel();
	void AddFadePlan(int brightnessPercent, int delay);
	FadeInfo* GetFadePlan();
};

#endif

