#include "Logger.h"

void Logger::Init()
{
	Serial.begin(115200);
}

void Logger::Log(String text)
{
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
	Serial.println(text);
}

void Logger::LogLine(int text)
{
	char number[12];
	sprintf(number, "%d", text);
	LogLine(number);
}


