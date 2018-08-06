#include "ConfigManager.h"
#include <ArduinoJson.h>
#include "FS.h"

void ConfigManager::Init(Logger &logger)
{
	this->logger = logger;

	if (!SPIFFS.begin())
	{
		logger.LogLine("Failed to mount file system");
		return;
	}
}

bool ConfigManager::SaveConfig()
{
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();

	json["wifiname"] = WifiName;
	json["wifipass"] = WifiPass;
	json["timeForLedsSwitchedOn"] = TimeForLedsSwitchedOn;
	json["delayForNextStairToSwitchOn"] = DelayForNextStairToSwitchOn;
	json["millisCountForFullBrightness"] = MillisCountForFullBrightness;
	json["stairsCount"] = StairsCount;

	json["infoUrlSensorUp"] = InfoUrlSensorUp;
	json["portSensorUp"] = PortSensorUp;
	json["uriSensorUp"] = UriSensorUp;
	json["infoUrlSensorDown"] = InfoUrlSensorDown;
	json["portSensorDown"] = PortSensorDown;
	json["uriSensorDown"] = UriSensorDown;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile) 
	{
		logger.LogLine("Failed to open config file for writing");
		return false;
	}
	json.prettyPrintTo(Serial);
	json.printTo(configFile);

	configFile.close();

	ESP.restart();

	return true;
}

bool ConfigManager::LoadConfig()
{
	File configFile;
	for (int i = 0; i < 2; ++i)
	{
		configFile = SPIFFS.open("/config.json", "r");
		if (!configFile)
		{
			logger.LogLine("Config file doesn't exist. Creating new...");
			if (SaveConfig())
				continue;
		}
	}

	if (!configFile)
	{
		logger.LogLine("Failed to open config file");
		return false;
	}

	size_t size = configFile.size();
	if (size > 1024) 
	{
		logger.LogLine("Config file size is too large");
		return false;
	}

	// Allocate a buffer to store contents of the file.
	std::unique_ptr<char[]> buf(new char[size]);

	// We don't use String here because ArduinoJson library requires the input
	// buffer to be mutable. If you don't use ArduinoJson, you may as well
	// use configFile.readString instead.
	configFile.readBytes(buf.get(), size);

	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(buf.get());

	if (!json.success())
	{
		logger.LogLine("Failed to parse config file");
		configFile.close();
		return false;
	}

	const char* wifiname = json["wifiname"];
	const char* wifipass = json["wifipass"];
	const char* timeForLedsSwitchedOn = json["timeForLedsSwitchedOn"];
	const char* delayForNextStairToSwitchOn = json["delayForNextStairToSwitchOn"];
	const char* millisCountForFullBrightness = json["millisCountForFullBrightness"];
	const char* stairsCount = json["stairsCount"];

	const char* infoUrlSensorUp = json["infoUrlSensorUp"];
	const char* portSensorUp = json["portSensorUp"];
	const char* uriSensorUp = json["uriSensorUp"];
	const char* infoUrlSensorDown = json["infoUrlSensorDown"];
	const char* portSensorDown = json["portSensorDown"];
	const char* uriSensorDown = json["uriSensorDown"];

	logger.LogLine("Loaded config");
	
	WifiName = wifiname;
	WifiPass = wifipass;
	TimeForLedsSwitchedOn = atoi(timeForLedsSwitchedOn);
	DelayForNextStairToSwitchOn = atoi(delayForNextStairToSwitchOn);
	MillisCountForFullBrightness = atoi(millisCountForFullBrightness);
	StairsCount = atoi(stairsCount);

	InfoUrlSensorUp = infoUrlSensorUp;
	PortSensorUp = portSensorUp;
	UriSensorUp = uriSensorUp;
	InfoUrlSensorDown = infoUrlSensorDown;
	PortSensorDown = portSensorDown;
	UriSensorDown = uriSensorDown;

	configFile.close();

	return true;
}
