#include "StairsLedDriver.h"

void StairsLedDriver::Begin(Logger &logger, ConfigManager &configManager)
{
	this->logger = logger;
	this->timeForLedsSwitchedOn = configManager.TimeForLedsSwitchedOn;
	this->delayForNextStairToSwitchOn = configManager.DelayForNextStairToSwitchOn;
	this->millisCountForFullBrightness = configManager.MillisCountForFullBrightness;
	this->stairsCount = configManager.StairsCount;

	this->stairsMap[0] = configManager.Channel1;
	this->stairsMap[1] = configManager.Channel2;
	this->stairsMap[2] = configManager.Channel3;
	this->stairsMap[3] = configManager.Channel4;
	this->stairsMap[4] = configManager.Channel5;
	this->stairsMap[5] = configManager.Channel6;
	this->stairsMap[6] = configManager.Channel7;
	this->stairsMap[7] = configManager.Channel8;
	this->stairsMap[8] = configManager.Channel9;
	this->stairsMap[9] = configManager.Channel10;
	this->stairsMap[10] = configManager.Channel11;
	this->stairsMap[11] = configManager.Channel12;
	this->stairsMap[12] = configManager.Channel13;
	this->stairsMap[13] = configManager.Channel14;
	this->stairsMap[14] = configManager.Channel15;
	this->stairsMap[15] = configManager.Channel16;

	this->logger.Log("Stairs count: ");
	this->logger.LogLine(this->stairsCount);
	pwm.begin();
	pwm.setPWMFreq(1000);

	this->ledStrips = new LedStrip*[this->stairsCount];
	for (int i = 0; i < this->stairsCount; i++)
		this->ledStrips[i] = new LedStrip(logger, pwm, i, this->millisCountForFullBrightness);

	this->logger.LogLine("Outputs initialized");

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
			if (!ledStrips[stairsMap[i]]->IsFading() || !ledStrips[stairsMap[i]]->IsBrightnessGoingUp())
				ledStrips[stairsMap[i]]->Fade(100, i * this->delayForNextStairToSwitchOn);
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
			if (!ledStrips[stairsMap[currentLedStrip]]->IsFading() || !ledStrips[stairsMap[currentLedStrip]]->IsBrightnessGoingUp())
				ledStrips[stairsMap[currentLedStrip]]->Fade(100, i * this->delayForNextStairToSwitchOn);
		}
	}

	this->timeOfLastSensorDetected = millis();
}

void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stairsCount; ++i)
	{
		ledStrips[stairsMap[i]]->Update();
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
					if (ledStrips[stairsMap[i]]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[stairsMap[i]]->Fade(0, i * this
							->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_DOWN)
			{
				for (int i = 0; i < stairsCount; ++i)
				{
					if (ledStrips[stairsCount - stairsMap[i] - 1]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[stairsCount - stairsMap[i] - 1]
							->Fade(0, i * this->delayForNextStairToSwitchOn);
				}
			}
			else if (state == STAIRS_GO_UP_AND_DOWN)
			{
				int middleStair = stairsCount / 2;

				for (int i = middleStair; i >= 0; --i)
				{
					if (ledStrips[stairsMap[i]]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[stairsMap[i]]
							->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);

					if (ledStrips[stairsCount - stairsMap[i] - 1]->IsFadePlanned())
						allStairsAreOff = false;
					else
						ledStrips[stairsCount - stairsMap[i] - 1]
							->Fade(0, (middleStair - i) * this->delayForNextStairToSwitchOn);
				}
			}

			if (allStairsAreOff)
				this->state = STAIRS_OFF;
		}
	}
}