#include "StairsLedDriver.h"

void StairsLedDriver::Begin(Logger &logger, ConfigManager &configManager)
{
	this->logger = logger;
	this->timeForLedsSwitchedOn = configManager.TimeForLedsSwitchedOn;
	this->delayForNextStairToSwitchOn = configManager.DelayForNextStairToSwitchOn;
	this->millisCountForFullBrightness = configManager.MillisCountForFullBrightness;
	this->stairsCount = configManager.StairsCount;
	this->logger.Log("Stairs count: ");
	this->logger.LogLine(this->stairsCount);
	pwm.begin();
	pwm.setPWMFreq(1000);

	this->ledStrips = new LedStrip*[this->stairsCount];
	for (int i = 0; i < this->stairsCount; i++)
		this->ledStrips[i] = new LedStrip(logger, pwm, i, this->millisCountForFullBrightness);

	//switch off all leds
	for (int i = 0; i < 16; i++)
	{
		pwm.setPWM(i, 0, 4096);
	}

	this->GoUp();
	this->GoDown();
}

void StairsLedDriver::GoUp()
{
	if (this->state == STAIRS_GO_DOWN || this->state == STAIRS_OFF)
	{
		if (this->state == STAIRS_GO_DOWN)
			this->state = STAIRS_GO_UP_AND_DOWN;
		else
			this->state = STAIRS_GO_UP;

		for (int i = 0; i < stairsCount; ++i)
		{
			if (!ledStrips[i]->IsFading() || !ledStrips[i]->IsBrightnessGoingUp())
				ledStrips[i]->Fade(100, i * this->delayForNextStairToSwitchOn);
		}
	}

	this->timeOfLastSensorDetected = millis();
}

void StairsLedDriver::GoDown()
{
	if (this->state == STAIRS_GO_UP || this->state == STAIRS_OFF)
	{
		if (this->state == STAIRS_GO_UP)
			this->state = STAIRS_GO_UP_AND_DOWN;
		else
			this->state = STAIRS_GO_DOWN;

		for (int i = 0; i < stairsCount; ++i)
		{
			int currentLedStrip = stairsCount - i - 1;
			if (!ledStrips[currentLedStrip]->IsFading() || !ledStrips[currentLedStrip]->IsBrightnessGoingUp())
				ledStrips[currentLedStrip]->Fade(100, i * this->delayForNextStairToSwitchOn);
		}
	}

	this->timeOfLastSensorDetected = millis();
}

void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stairsCount; ++i)
	{
		ledStrips[i]->Update();
	}

	if (state > STAIRS_OFF)
	{
		if (millis() - this->timeOfLastSensorDetected > this->timeForLedsSwitchedOn)
		{
			if (state == STAIRS_GO_UP)
			{
				for (int i = 0; i < stairsCount; ++i)
				{
					ledStrips[i]->Fade(0, i * this
						->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_DOWN)
			{
				for (int i = 0; i < stairsCount; ++i)
				{
					ledStrips[stairsCount - i - 1]
						->Fade(0, i * this->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_UP_AND_DOWN)
			{
				int middleStair = stairsCount / 2;

				for (int i = middleStair; i >= 0; --i)
				{
					ledStrips[i]
						->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);

					ledStrips[stairsCount - i - 1]
						->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);
				}
			}

			this->state = STAIRS_OFF;
		}
	}
}