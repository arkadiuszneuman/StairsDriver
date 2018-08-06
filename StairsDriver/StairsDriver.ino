#include "StairsLedDriver.h"
#include "Logger.h"
#include "OtaDriver.h"
#include "ConfigManager.h"
#include "WifiConnector.h"

StairsLedDriver stairsLedDriver;
InfraredDistanceRangingSensor bottomStairsSensor(14); //D5
InfraredDistanceRangingSensor upperStairsSensor(12); //D6
Logger logger;
OtaDriver otaDriver;
ConfigManager configManager;
WifiConnector wifiConnector;

void setup() {
	logger.Init();
	stairsLedDriver.Begin(logger, configManager);

	configManager.Init(logger);
	configManager.LoadConfig();

	wifiConnector.Init(logger);
	wifiConnector.ConnectToWifi(configManager);

	otaDriver.Init(logger);
}

void loop() {
	stairsLedDriver.Update();
	otaDriver.Update();

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