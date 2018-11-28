#include "HttpSite.h"
#include "index.h"
#include "config.h"

void HttpSite::Init(ConfigManager &configManager, Logger &logger,
	void(*receivedSettingsFunc)(SettingsContainer))
{
	server = new ESP8266WebServer(80);
	this->configManager = configManager;
	this->logger = logger;
	this->receivedSettingsFunc = receivedSettingsFunc;

	server->on("/", std::bind(&HttpSite::Index, this));
	server->on("/config", std::bind(&HttpSite::Config, this));
	server->on("/changesettings", std::bind(&HttpSite::ChangeSettings, this));
	server->on("/save", HTTPMethod::HTTP_POST, std::bind(&HttpSite::ConfigPost, this));
	server->on("/resetsettings", HTTPMethod::HTTP_POST, std::bind(&HttpSite::ResetSettings, this));
	server->on("/restart", HTTPMethod::HTTP_POST, std::bind(&HttpSite::Restart, this));

	server->begin();
	logger.LogLine("HTTP server started");
}

void HttpSite::Update()
{
	server->handleClient();
}

void HttpSite::SetStatus(String status)
{
	this->status = status;
}

void HttpSite::Index()
{
	logger.LogLine("request for /");
	String html = page_index;
	html.replace("{status}", status);
	server->send(200, "text/html", html);
}

void HttpSite::Config()
{
	logger.LogLine("request for /config");
	String html = page_config;
	html.replace("{wifiname}", configManager.WifiName);
	html.replace("{wifipass}", configManager.WifiPass);
	html.replace("{TimeForLedsSwitchedOn}", String(configManager.TimeForLedsSwitchedOn));
	html.replace("{DelayForNextStairToSwitchOn}", String(configManager.DelayForNextStairToSwitchOn));
	html.replace("{MillisCountForFullBrightness}", String(configManager.MillisCountForFullBrightness));
	html.replace("{StairsCount}", String(configManager.StairsCount));
	html.replace("{InfoUrlSensorUp}", configManager.InfoUrlSensorUp);
	html.replace("{PortSensorUp}", configManager.PortSensorUp);
	html.replace("{UriSensorUp}", configManager.UriSensorUp);
	html.replace("{InfoUrlSensorDown}", configManager.InfoUrlSensorDown);
	html.replace("{PortSensorDown}", configManager.PortSensorDown);
	html.replace("{UriSensorDown}", configManager.UriSensorDown);

	html.replace("{channel1}", String(configManager.Channel1));
	html.replace("{channel2}", String(configManager.Channel2));
	html.replace("{channel3}", String(configManager.Channel3));
	html.replace("{channel4}", String(configManager.Channel4));
	html.replace("{channel5}", String(configManager.Channel5));
	html.replace("{channel6}", String(configManager.Channel6));
	html.replace("{channel7}", String(configManager.Channel7));
	html.replace("{channel8}", String(configManager.Channel8));
	html.replace("{channel9}", String(configManager.Channel9));
	html.replace("{channel10}", String(configManager.Channel10));
	html.replace("{channel11}", String(configManager.Channel11));
	html.replace("{channel12}", String(configManager.Channel12));
	html.replace("{channel13}", String(configManager.Channel13));
	html.replace("{channel14}", String(configManager.Channel14));
	html.replace("{channel15}", String(configManager.Channel15));
	html.replace("{channel16}", String(configManager.Channel16));

	server->send(200, "text/html", html);
}

void HttpSite::ConfigPost()
{
	logger.LogLine("post to /config");
	String wifiname = server->arg("wifiname");
	String wifipass = server->arg("wifipassword");
	String TimeForLedsSwitchedOn = server->arg("TimeForLedsSwitchedOn");
	String DelayForNextStairToSwitchOn = server->arg("DelayForNextStairToSwitchOn");
	String MillisCountForFullBrightness = server->arg("MillisCountForFullBrightness");
	String StairsCount = server->arg("StairsCount");
	String InfoUrlSensorUp = server->arg("InfoUrlSensorUp");
	String PortSensorUp = server->arg("PortSensorUp");
	String UriSensorUp = server->arg("UriSensorUp");
	String InfoUrlSensorDown = server->arg("InfoUrlSensorDown");
	String PortSensorDown = server->arg("PortSensorDown");
	String UriSensorDown = server->arg("UriSensorDown");
	String channel1 = server->arg("channel1");
	String channel2 = server->arg("channel2");
	String channel3 = server->arg("channel3");
	String channel4 = server->arg("channel4");
	String channel5 = server->arg("channel5");
	String channel6 = server->arg("channel6");
	String channel7 = server->arg("channel7");
	String channel8 = server->arg("channel8");
	String channel9 = server->arg("channel9");
	String channel10 = server->arg("channel10");
	String channel11 = server->arg("channel11");
	String channel12 = server->arg("channel12");
	String channel13 = server->arg("channel13");
	String channel14 = server->arg("channel14");
	String channel15 = server->arg("channel15");
	String channel16 = server->arg("channel16");

	configManager.WifiName = wifiname;
	configManager.WifiPass = wifipass;
	configManager.TimeForLedsSwitchedOn = atoi(TimeForLedsSwitchedOn.c_str());
	configManager.DelayForNextStairToSwitchOn = atoi(DelayForNextStairToSwitchOn.c_str());
	configManager.MillisCountForFullBrightness = atoi(MillisCountForFullBrightness.c_str());
	configManager.StairsCount = atoi(StairsCount.c_str());
	configManager.InfoUrlSensorUp = InfoUrlSensorUp;
	configManager.PortSensorUp = PortSensorUp;
	configManager.UriSensorUp = UriSensorUp;
	configManager.InfoUrlSensorDown = InfoUrlSensorDown;
	configManager.PortSensorDown = PortSensorDown;
	configManager.UriSensorDown = UriSensorDown;
	configManager.Channel1 = atoi(channel1.c_str());
	configManager.Channel2 = atoi(channel2.c_str());
	configManager.Channel3 = atoi(channel3.c_str());
	configManager.Channel4 = atoi(channel4.c_str());
	configManager.Channel5 = atoi(channel5.c_str());
	configManager.Channel6 = atoi(channel6.c_str());
	configManager.Channel7 = atoi(channel7.c_str());
	configManager.Channel8 = atoi(channel8.c_str());
	configManager.Channel9 = atoi(channel9.c_str());
	configManager.Channel10 = atoi(channel10.c_str());
	configManager.Channel11 = atoi(channel11.c_str());
	configManager.Channel12 = atoi(channel12.c_str());
	configManager.Channel13 = atoi(channel13.c_str());
	configManager.Channel14 = atoi(channel14.c_str());
	configManager.Channel15 = atoi(channel15.c_str());
	configManager.Channel16 = atoi(channel16.c_str());

	configManager.SaveConfig();

	Config();
}

void HttpSite::ResetSettings()
{
	logger.LogLine("post to /resetsettings");

	configManager.WifiName = "";
	configManager.WifiPass = "";
	configManager.TimeForLedsSwitchedOn = 0;
	configManager.DelayForNextStairToSwitchOn = 0;
	configManager.MillisCountForFullBrightness = 0;
	configManager.StairsCount = 0;
	configManager.InfoUrlSensorUp = "";
	configManager.PortSensorUp = "";
	configManager.UriSensorUp = "";
	configManager.InfoUrlSensorDown = "";
	configManager.PortSensorDown = "";
	configManager.UriSensorDown = "";

	configManager.Channel1 = 0;
	configManager.Channel2 = 1;
	configManager.Channel3 = 2;
	configManager.Channel4 = 3;
	configManager.Channel5 = 4;
	configManager.Channel6 = 5;
	configManager.Channel7 = 6;
	configManager.Channel8 = 7;
	configManager.Channel9 = 8;
	configManager.Channel10 = 9;
	configManager.Channel11 = 10;
	configManager.Channel12 = 11;
	configManager.Channel13 = 12;
	configManager.Channel14 = 13;
	configManager.Channel15 = 14;
	configManager.Channel16 = 15;

	configManager.SaveConfig();

	Config();
}

void HttpSite::Restart()
{
	logger.LogLine("post to /restart");

	ESP.restart();
}

void HttpSite::ChangeSettings()
{
	logger.LogLine("get from /changesettings");

	String status = server->arg("status");
	String minLevel = server->arg("minlevel");
	String maxLevel = server->arg("maxlevel");
	int minLevelInt = -1;
	int maxLevelInt = -1;

	if (minLevel != "")
		minLevelInt = atoi(minLevel.c_str());

	if (maxLevel != "")
		maxLevelInt = atoi(maxLevel.c_str());

	receivedSettingsFunc(SettingsContainer(status, minLevelInt, maxLevelInt));

	server->send(200, "text/html", "{ \"status\": \"Got settings\" }");
}
