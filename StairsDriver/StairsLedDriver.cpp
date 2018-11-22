#include "StairsLedDriver.h"

void StairsLedDriver::Begin(Logger &logger, ConfigManager &configManager)
{
	this->logger = logger;
	this->timeForLedsSwitchedOn = configManager.TimeForLedsSwitchedOn;
	this->delayForNextStairToSwitchOn = configManager.DelayForNextStairToSwitchOn;
	this->millisCountForFullBrightness = configManager.MillisCountForFullBrightness;
	this->stairsCount = configManager.StairsCount;

	int stairsMap[15];
	stairsMap[0] = configManager.Channel1;
	stairsMap[1] = configManager.Channel2;
	stairsMap[2] = configManager.Channel3;
	stairsMap[3] = configManager.Channel4;
	stairsMap[4] = configManager.Channel5;
	stairsMap[5] = configManager.Channel6;
	stairsMap[6] = configManager.Channel7;
	stairsMap[7] = configManager.Channel8;
	stairsMap[8] = configManager.Channel9;
	stairsMap[9] = configManager.Channel10;
	stairsMap[10] = configManager.Channel11;
	stairsMap[11] = configManager.Channel12;
	stairsMap[12] = configManager.Channel13;
	stairsMap[13] = configManager.Channel14;
	stairsMap[14] = configManager.Channel15;
	stairsMap[15] = configManager.Channel16;

	this->logger.Log("Stairs count: ");
	this->logger.LogLine(this->stairsCount);
	pwm.begin();
	pwm.setPWMFreq(1000);

	this->ledStrips = new LedStrip*[this->stairsCount];
	for (int i = 0; i < this->stairsCount; i++)
		this->ledStrips[i] = new LedStrip(logger, pwm, stairsMap[i], this->millisCountForFullBrightness);

	this->logger.LogLine("Outputs initialized");

	//switch off all leds
	for (int i = 0; i < 16; i++)
	{
		pwm.setPWM(i, 0, 4096);
	}
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
			bool allStairsAreOff = true;

			if (state == STAIRS_GO_UP)
			{
				for (int i = 0; i < stairsCount; ++i)
				{
					if (ledStrips[i]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[i]->Fade(0, i * this
							->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_DOWN)
			{
				for (int i = 0; i < stairsCount; ++i)
				{
					if (ledStrips[stairsCount - i - 1]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[stairsCount - i - 1]
							->Fade(0, i * this->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_UP_AND_DOWN)
			{
				int middleStair = stairsCount / 2;

				for (int i = middleStair; i >= 0; --i)
				{
					if (ledStrips[i]->IsFadePlanned())
						allStairsAreOff = false;
					else
					{
						if (ledStrips[i]->GetCurrentBrightness() > 0)
						{
							ledStrips[i]
								->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);
						}
					}

					if (ledStrips[stairsCount - i - 1]->IsFadePlanned())
						allStairsAreOff = false;
					else
					{
						if (ledStrips[stairsCount - i - 1]->GetCurrentBrightness() > 0)
						{
							ledStrips[stairsCount - i - 1]
								->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);
						}
					}
				}
			}

			if (allStairsAreOff)
				this->state = STAIRS_OFF;
		}
	}
}