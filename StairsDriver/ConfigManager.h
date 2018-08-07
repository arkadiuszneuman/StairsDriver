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
};

#endif

