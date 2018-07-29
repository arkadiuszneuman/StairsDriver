#include "StairsLedDriver.h"

void StairsLedDriver::Begin(int stripsCount)
{
	pwm.begin();
	pwm.setPWMFreq(1000);

	this->stripsCount = stripsCount;
	this->ledStrips = new LedStrip*[stripsCount];
	for (int i = 0; i < stripsCount; i++)
		this->ledStrips[i] = new LedStrip(pwm, i, MILLIS_COUNT_FOR_FULL_BRIGHTNESS);

	this->bottomStairsSensor = new InfraredDistanceRangingSensor(14); //D5
	this->temp = 0;
	this->state = 0;
}

void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stripsCount; ++i)
	{
		ledStrips[i]->Update();
	}

	if (this->bottomStairsSensor->IsCollisionDetected())
	{
		state = 1;
		Serial.println("Bottom stairs collision detected");
	}

	if (state > 0)
	{
		if (millis() - temp > 4000)
		{
			temp = millis();

			if (state == 1)
			{
				for (int i = 0; i < stripsCount; ++i)
				{
					ledStrips[i]->Fade(5, i * 1000);
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
				state = 0;
		}
	}
}