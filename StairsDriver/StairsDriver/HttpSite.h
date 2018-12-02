// HttpSite.h

#ifndef _HTTPSITE_h
#define _HTTPSITE_h

#include <ESP8266WebServer.h>
#include "ConfigManager.h"
#include "SettingsContainer.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HttpSite 
{
private:
	ESP8266WebServer* server; //Server on port 80
	ConfigManager configManager;
	Logger logger;
	String status = "Idle";
	unsigned long lastInfoAboutSensor = 0;
	void(*receivedSettingsFunc)(SettingsContainer);
	void Index();
	void Config();
	void ConfigPost();
	void ChangeSettings();
	void ResetSettings();
	void Restart();
	void SendInfoAboutSensor(String url, String port, String uri);
public:
	void Init(ConfigManager &configManager, Logger &logger, void(*receivedSettingsFunc)(SettingsContainer));
	void Update();
	void SetStatus(String status);
	void SendInfoAboutTriggeredSensorDown();
	void SendInfoAboutTriggeredSensorUp();
};

#endif

