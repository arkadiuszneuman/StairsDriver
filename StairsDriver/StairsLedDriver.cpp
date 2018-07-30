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
	this->upperStairsSensor = new InfraredDistanceRangingSensor(12); //D6
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

	if (this->upperStairsSensor->IsCollisionDetected())
	{
		state = 3;
		Serial.println("Upper stairs collision detected");
	}

	if (state > 0)
	{
		if (millis() - temp > 15000)
		{
			temp = millis();

			if (state == 1)
			{
				for (int i = 0; i < stripsCount; ++i)
				{
					ledStrips[i]->Fade(100, i * 2000);
				}
			}
			else if (state == 2)
			{
				for (int i = 0; i < stripsCount; ++i)
				{
					ledStrips[i]->Fade(0, i * 2000);
				}
			}
			else if (state == 3)
			{
				Serial.println("State 3 started");

				for (int i = 0; i < stripsCount; ++i)
				{
					ledStrips[stripsCount - i - 1]->Fade(100, i * 2000);
				}
			}
			else if (state == 4)
			{
				Serial.println("State 4 started");

				for (int i = 0; i < stripsCount; ++i)
				{
					ledStrips[stripsCount - i - 1]->Fade(0, i * 2000);
				}
			}

			if (state == 2 || state == 4)
				state = 0;
			else
				++state;

			Serial.print("Current state ");
			Serial.println(state);
		}
	}
}