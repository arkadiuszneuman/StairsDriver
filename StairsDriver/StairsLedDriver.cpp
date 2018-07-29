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
	this->goingUp = false;
}

void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stripsCount; ++i)
	{
		ledStrips[i]->Update();
	}

	if (millis() - temp > 15000)
	{
		temp = millis();
		goingUp = !goingUp;

		if (goingUp)
		{
			ledStrips[0]->Fade(100);
			ledStrips[1]->Fade(100, 1000);
			ledStrips[2]->Fade(100, 2000);
		}
		else
		{
			ledStrips[0]->Fade(0);
			ledStrips[1]->Fade(0, 1000);
			ledStrips[2]->Fade(0, 2000);
		}

	}
}