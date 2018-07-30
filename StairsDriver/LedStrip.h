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

#define MAX_LED_BRIGHTNESS 4096

class LedStrip
{
private:
	Adafruit_PWMServoDriver pwm;
	int milisCountForFullBrightness;
	int channel;
	int currentBrightness = 0;
	int brightnessToSet = 0;
	bool brightnessGoingUp = true;
	bool isFading = false;
	double previousTimeLeftPercent = 0;
	long millisStart = 0;
	void SetPWM(int pwmValue);
public:
	LedStrip(Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness);
	void Fade(int brightnessPercent, int delay = 0);
	void Update();
};

#endif

