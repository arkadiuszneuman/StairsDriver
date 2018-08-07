#include "HttpSite.h"
#include "index.h"
#include "config.h"

void HttpSite::Init(ConfigManager &configManager, Logger &logger)
{
	server = new ESP8266WebServer(80);
	this->configManager = configManager;
	this->logger = logger;

	server->on("/", std::bind(&HttpSite::Index, this));
	server->on("/config", std::bind(&HttpSite::Config, this));
	server->on("/save", HTTPMethod::HTTP_POST, std::bind(&HttpSite::ConfigPost, this));
	server->on("/resetsettings", HTTPMethod::HTTP_POST, std::bind(&HttpSite::ResetSettings, this));

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

	configManager.SaveConfig();

	Config();
}
