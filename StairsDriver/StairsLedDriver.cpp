#include "StairsLedDriver.h"

void StairsLedDriver::Begin(int stripsCount)
{
	pwm.begin();
	pwm.setPWMFreq(1000);

	this->stripsCount = stripsCount;
	Serial.println("1");
	this->ledStrips = new LedStrip*[stripsCount];
	Serial.println("2");
	for (int i = 0; i < stripsCount; i++)
		this->ledStrips[i] = new LedStrip(pwm, i, MILLIS_COUNT_FOR_FULL_BRIGHTNESS);

	Serial.println("3");
	this->temp = 0;
	this->state = 1;
}

void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stripsCount; ++i)
	{
		ledStrips[i]->Update();
	}

	if (millis() - temp > 4000)
	{
		temp = millis();

		if (state == 1)
		{
			for (int i = 0; i < stripsCount; ++i)
			{
				ledStrips[i]->Fade(50, i * 1000);
			}
		}
		else if (state == 2)
		{
			for (int i = 0; i < stripsCount; ++i)
			{
				ledStrips[i]->Fade(100, i * 1000);
			}
		}
		else if (state == 3)
		{
			for (int i = 0; i < stripsCount; ++i)
			{
				ledStrips[i]->Fade(0, i * 1000);
			}
		}

		++state;
		if (state > 3)
			state = 1;
	}
}