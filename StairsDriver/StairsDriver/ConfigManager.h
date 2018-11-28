// ConfigManager.h

#ifndef _CONFIGMANAGER_h
#define _CONFIGMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Logger.h"

class ConfigManager {
private:
	Logger logger;
public:
	void Init(Logger &logger);
	bool SaveConfig();
	bool LoadConfig();

	String WifiName = "";
	String WifiPass = "";
	int TimeForLedsSwitchedOn = 15000;
	int DelayForNextStairToSwitchOn = 2000;
	int MillisCountForFullBrightness = 10000;
	int StairsCount = 16;
	String InfoUrlSensorUp = "";
	String PortSensorUp = "";
	String UriSensorUp = "";
	String InfoUrlSensorDown = "";
	String PortSensorDown = "";
	String UriSensorDown = "";

	short Channel1 = 0;
	short Channel2 = 1;
	short Channel3 = 2;
	short Channel4 = 3;
	short Channel5 = 4;
	short Channel6 = 5;
	short Channel7 = 6;
	short Channel8 = 7;
	short Channel9 = 8;
	short Channel10 = 9;
	short Channel11 = 10;
	short Channel12 = 11;
	short Channel13 = 12;
	short Channel14 = 13;
	short Channel15 = 14;
	short Channel16 = 15;
};

#endif

