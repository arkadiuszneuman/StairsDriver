#include "Logger.h"

void Logger::Init()
{
	Serial.begin(115200);
}

void Logger::Log(String text)
{
	if (showMillis)
	{
		Serial.print(millis());
		Serial.print(": ");
		showMillis = false;
	}
	Serial.print(text);
}

void Logger::Log(int text)
{
	char number[12];
	sprintf(number, "%d", text);
	Log(number);
}

void Logger::LogLine(String text)
{
	if (showMillis)
	{
		Serial.print(millis());
		Serial.print(": ");
	}
	Serial.println(text);

	showMillis = true;
}

void Logger::LogLine(int text)
{
	char number[12];
	sprintf(number, "%d", text);
	LogLine(number);
}


