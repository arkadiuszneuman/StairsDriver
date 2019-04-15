#include "SettingsContainer.h"
#include "StairsLedDriver.h"
#include "Logger.h"
#include "OtaDriver.h"
#include "ConfigManager.h"
#include "WifiConnector.h"
#include "HttpSite.h"

StairsLedDriver stairsLedDriver;
InfraredDistanceRangingSensor bottomStairsSensor(13); //D7
InfraredDistanceRangingSensor upperStairsSensor(14); //D5
Logger logger;
OtaDriver otaDriver;
ConfigManager configManager;
WifiConnector wifiConnector;
HttpSite httpSite;

bool isOff = false;

void setup() {
	logger.Init();

	configManager.Init(logger);
	configManager.LoadConfig();

	wifiConnector.Init(logger);
	wifiConnector.ConnectToWifi(configManager);
	httpSite.Init(configManager, logger, onReceiveSettings);

	otaDriver.Init(logger);
	stairsLedDriver.Begin(logger, configManager);
}

void loop() {
	httpSite.Update();
	otaDriver.Update();

	if (!isOff)
	{
		stairsLedDriver.Update();

		if (bottomStairsSensor.IsCollisionDetected())
		{
			logger.LogLine("Bottom stairs collision detected");
			stairsLedDriver.GoUp();
			httpSite.SendInfoAboutTriggeredSensorDown();
		}

		if (upperStairsSensor.IsCollisionDetected())
		{
			logger.LogLine("Upper stairs collision detected");
			stairsLedDriver.GoDown();
			httpSite.SendInfoAboutTriggeredSensorUp();
		}
	}

	delay(10);
}

void onReceiveSettings(SettingsContainer receivedSettings) {
	isOff = receivedSettings.GetStatus() == "off";
	if (isOff)
		stairsLedDriver.InstantlyOffAllLeds();
	else
	{
		if (receivedSettings.GetMaxLevel() >= 0)
			stairsLedDriver.SetMaxLevel(receivedSettings.GetMaxLevel());

		if (receivedSettings.GetMinLevel() >= 0)
			stairsLedDriver.SetMinLevel(receivedSettings.GetMinLevel());
	}
}