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
	StaticJsonBuffer<800> jsonBuffer;
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

	json["channel1"] = Channel1;
	json["channel2"] = Channel2;
	json["channel3"] = Channel3;
	json["channel4"] = Channel4;
	json["channel5"] = Channel5;
	json["channel6"] = Channel6;
	json["channel7"] = Channel7;
	json["channel8"] = Channel8;
	json["channel9"] = Channel9;
	json["channel10"] = Channel10;
	json["channel11"] = Channel11;
	json["channel12"] = Channel12;
	json["channel13"] = Channel13;
	json["channel14"] = Channel14;
	json["channel15"] = Channel15;
	json["channel16"] = Channel16;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile)
	{
		logger.LogLine("Failed to open config file for writing");
		return false;
	}
	json.prettyPrintTo(Serial);
	json.printTo(configFile);

	configFile.close();

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

	StaticJsonBuffer<800> jsonBuffer;
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

	const char* channel1 = json["channel1"];
	const char* channel2 = json["channel2"];
	const char* channel3 = json["channel3"];
	const char* channel4 = json["channel4"];
	const char* channel5 = json["channel5"];
	const char* channel6 = json["channel6"];
	const char* channel7 = json["channel7"];
	const char* channel8 = json["channel8"];
	const char* channel9 = json["channel9"];
	const char* channel10 = json["channel10"];
	const char* channel11 = json["channel11"];
	const char* channel12 = json["channel12"];
	const char* channel13 = json["channel13"];
	const char* channel14 = json["channel14"];
	const char* channel15 = json["channel15"];
	const char* channel16 = json["channel16"];

	logger.LogLine("Loaded config");

	if (wifiname)
		WifiName = wifiname;
	if (wifipass)
		WifiPass = wifipass;
	if (timeForLedsSwitchedOn)
		TimeForLedsSwitchedOn = atoi(timeForLedsSwitchedOn);
	if (delayForNextStairToSwitchOn)
		DelayForNextStairToSwitchOn = atoi(delayForNextStairToSwitchOn);
	if (millisCountForFullBrightness)
		MillisCountForFullBrightness = atoi(millisCountForFullBrightness);
	if (stairsCount)
		StairsCount = atoi(stairsCount);

	if (infoUrlSensorUp)
		InfoUrlSensorUp = infoUrlSensorUp;
	if (portSensorUp)
		PortSensorUp = portSensorUp;
	if (uriSensorUp)
		UriSensorUp = uriSensorUp;
	if (infoUrlSensorDown)
		InfoUrlSensorDown = infoUrlSensorDown;
	if (portSensorDown)
		PortSensorDown = portSensorDown;
	if (uriSensorDown)
		UriSensorDown = uriSensorDown;

	if (channel1)
		Channel1 = atoi(channel1);
	if (channel2)
		Channel2 = atoi(channel2);
	if (channel3)
		Channel3 = atoi(channel3);
	if (channel4)
		Channel4 = atoi(channel4);
	if (channel5)
		Channel5 = atoi(channel5);
	if (channel6)
		Channel6 = atoi(channel6);
	if (channel7)
		Channel7 = atoi(channel7);
	if (channel8)
		Channel8 = atoi(channel8);
	if (channel9)
		Channel9 = atoi(channel9);
	if (channel10)
		Channel10 = atoi(channel10);
	if (channel11)
		Channel11 = atoi(channel11);
	if (channel12)
		Channel12 = atoi(channel12);
	if (channel13)
		Channel13 = atoi(channel13);
	if (channel14)
		Channel14 = atoi(channel14);
	if (channel15)
		Channel15 = atoi(channel15);
	if (channel16)
		Channel16 = atoi(channel16);

	configFile.close();

	return true;
}
