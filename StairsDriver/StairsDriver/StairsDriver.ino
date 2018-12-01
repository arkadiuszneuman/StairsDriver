#include "SettingsContainer.h"
#include "StairsLedDriver.h"
#include "Logger.h"
#include "OtaDriver.h"
#include "ConfigManager.h"
#include "WifiConnector.h"
#include "HttpSite.h"

StairsLedDriver stairsLedDriver;
InfraredDistanceRangingSensor bottomStairsSensor(12); //D6
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
	unsigned long starMillis = millis();
	httpSite.Update();
	otaDriver.Update();

	if (!isOff)
	{
		stairsLedDriver.Update();

		if (bottomStairsSensor.IsCollisionDetected())
		{
			logger.LogLine("Bottom stairs collision detected");
			stairsLedDriver.GoUp();
		}

		if (upperStairsSensor.IsCollisionDetected())
		{
			logger.LogLine("Upper stairs collision detected");
			stairsLedDriver.GoDown();
		}
	}

	delay(10);
	unsigned long loopTime = millis() - starMillis;
	logger.Log("Loop time: ");
	logger.LogLine(loopTime);
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