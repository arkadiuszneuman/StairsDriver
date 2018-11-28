// SettingsContainer.h

#ifndef _SETTINGSCONTAINER_h
#define _SETTINGSCONTAINER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SettingsContainer
{
private:
	String status;
	int minLevel;
	int maxLevel;
public:
	SettingsContainer(String status, int minLevel, int maxLevel);
	String GetStatus();
	int GetMinLevel();
	int GetMaxLevel();
};

#endif

