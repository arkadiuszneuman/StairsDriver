#include "SettingsContainer.h"

SettingsContainer::SettingsContainer(String status, int minLevel, int maxLevel)
{
	this->maxLevel = maxLevel;
	this->minLevel = minLevel;
	this->status = status;
}

String SettingsContainer::GetStatus()
{
	return status;
}

int SettingsContainer::GetMinLevel()
{
	return minLevel;
}

int SettingsContainer::GetMaxLevel()
{
	return maxLevel;
}