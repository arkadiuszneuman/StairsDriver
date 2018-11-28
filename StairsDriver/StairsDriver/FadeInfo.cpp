#include "FadeInfo.h"

FadeInfo::FadeInfo(int brightnessPercent, unsigned long startOnMillis)
{
	this->brightnessPercent = brightnessPercent;
	this->startOnMillis = startOnMillis;
}

int FadeInfo::GetBrightnessPercent()
{
	return this->brightnessPercent;
}

unsigned long FadeInfo::GetStartOnMillis()
{
	return this->startOnMillis;
}