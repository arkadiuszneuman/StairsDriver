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

	InstantlyOffAllLeds();
}

void StairsLedDriver::GoUp()
{
	if ((this->state == STAIRS_GO_DOWN || this->state == STAIRS_OFF || ledStrips[0]->IsFadedToMinLevel() || !ledStrips[0]->IsBrightnessGoingUp())
		)
	{
		bool isAnyFaded = false;

		for (int i = 0; i < stairsCount; ++i)
		{
			int delay = i * this->delayForNextStairToSwitchOn;
			if (ShouldFadeLed(ledStrips[i], delay))
			{
				ledStrips[i]->AddFadePlan(100, delay);
				isAnyFaded = true;
			}
		}

		if (isAnyFaded)
		{
			if (this->state == STAIRS_GO_DOWN)
				this->state = STAIRS_GO_UP_AND_DOWN;
			else
				this->state = STAIRS_GO_UP;
		}
	}

	this->timeOfLastSensorDetected = millis();
}

void StairsLedDriver::GoDown()
{
	if ((this->state == STAIRS_GO_UP || this->state == STAIRS_OFF || ledStrips[stairsCount - 1]->IsFadedToMinLevel() || !ledStrips[stairsCount - 1]->IsBrightnessGoingUp())
		)
	{
		bool isAnyFaded = false;

		for (int i = 0; i < stairsCount; ++i)
		{
			int currentLedStrip = stairsCount - i - 1;

			int delay = i * this->delayForNextStairToSwitchOn;
			if (ShouldFadeLed(ledStrips[currentLedStrip], delay))
			{
				ledStrips[currentLedStrip]->AddFadePlan(100, delay);
				isAnyFaded = true;
			}
		}

		if (isAnyFaded)
		{
			if (this->state == STAIRS_GO_UP)
				this->state = STAIRS_GO_UP_AND_DOWN;
			else
				this->state = STAIRS_GO_DOWN;
		}
	}

	this->timeOfLastSensorDetected = millis();
}

bool StairsLedDriver::ShouldFadeLed(LedStrip* ledStrip, int delay, bool ignoreFullBrightness)
{
	if (!ledStrip->IsBrightnessGoingUp() ||
		(!ledStrip->IsFadePlanned() &&
			(ledStrip->GetCurrentBrightness() < ledStrip->GetMaxLevelPwm() || ignoreFullBrightness)))
	{
		FadeInfo* fadePlan = ledStrip->GetFadePlan();
		return fadePlan == NULL || fadePlan->GetStartOnMillis() > delay + millis();
	}

	return false;
}


void StairsLedDriver::Update()
{
	for (int i = 0; i < this->stairsCount; ++i)
	{
		ledStrips[i]->Update();
	}

	if (state > STAIRS_OFF)
	{
		if (millis() - this->timeOfLastSensorDetected >= this->timeForLedsSwitchedOn)
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
				bool isEven = stairsCount % 2 == 0;
				bool isFirstRun = true;

				for (int i = middleStair; i >= 0; --i)
				{
					int delay = (middleStair - i) * delayForNextStairToSwitchOn;
					if (isEven && !isFirstRun)
						delay -= delayForNextStairToSwitchOn;

					if (ledStrips[i]->IsFadePlanned())
						allStairsAreOff = false;
					else
					{
						int currentLedStrip = stairsCount - i - 1;

						if (ShouldFadeLed(ledStrips[i], delay, true))
						{
							ledStrips[i]->Fade(0, delay);
							ledStrips[currentLedStrip]->Fade(0, delay);
						}
					}

					if (isEven && isFirstRun)
					{
						isFirstRun = false;
						--i;
					}
				}
			}

			if (allStairsAreOff)
				this->state = STAIRS_OFF;
		}
	}
}

void StairsLedDriver::InstantlyOffAllLeds()
{
	for (int i = 0; i < 16; i++)
	{
		pwm.setPWM(i, 0, 4096);
	}
}

void StairsLedDriver::SetMinLevel(int minLevel)
{
	for (int i = 0; i < this->stairsCount; i++)
		this->ledStrips[i]->SetMinLevel(minLevel);
}

void StairsLedDriver::SetMaxLevel(int maxLevel)
{
	for (int i = 0; i < this->stairsCount; i++)
		this->ledStrips[i]->SetMaxLevel(maxLevel);
}