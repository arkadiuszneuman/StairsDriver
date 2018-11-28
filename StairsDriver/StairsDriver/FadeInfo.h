// FadeInfo.h

#ifndef _FADEINFO_h
#define _FADEINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class FadeInfo
{
private:
	int brightnessPercent = 0;
	unsigned long startOnMillis = 0;
public:
	FadeInfo(int brightnessPercent, unsigned long startOnMillis);
	int GetBrightnessPercent();
	unsigned long GetStartOnMillis();
};

#endif

