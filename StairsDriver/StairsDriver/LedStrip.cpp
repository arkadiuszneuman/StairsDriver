#include "LedStrip.h"

LedStrip::LedStrip(Logger &logger, Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness)
{
	this->logger = logger;
	this->pwm = pwm;
	this->channel = channel;
	this->milisCountForFullBrightness = milisCountForFullBrightness;
	this->SetPWM(0);
	this->fadePlan = NULL;
}

void LedStrip::Fade(int brightnessPercent, int delay)
{
	unsigned long currentMillisStart = millis() + delay;

	if (brightnessPercent > this->maxLevel)
		brightnessPercent = this->maxLevel;
	if (brightnessPercent < this->minLevel)
		brightnessPercent = this->minLevel;

	this->brightnessToSet = brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100;

	this->brightnessGoingUp = this->brightnessToSet > this->currentBrightness;
	this->millisStart = currentMillisStart;
	this->isFadingPlanned = true;
	this->previousTimeLeftPercent = 0;

	logger.Log("Setting percent ");
	logger.LogLine(brightnessPercent);
	logger.Log("Setting brightness ");
	logger.LogLine(brightnessToSet);
	logger.Log("Current brightness ");
	logger.LogLine(currentBrightness);
	logger.Log("GoingUp ");
	logger.LogLine(brightnessGoingUp);
}

void LedStrip::AddFadePlan(int brightnessPercent, int delay)
{
	if (this->fadePlan)
		delete this->fadePlan;
	this->fadePlan = new FadeInfo(brightnessPercent, millis() + delay);
}

void LedStrip::Update()
{
	if (fadePlan != NULL)
	{
		int delay = (int)(fadePlan->GetStartOnMillis() - millis());
		if (delay <= 0)
		{
			Fade(fadePlan->GetBrightnessPercent(), delay);
			delete fadePlan;
			fadePlan = NULL;
		}
	}

	if (!this->isFadingPlanned)
		return;

	long currentMillis = millis();
	if (currentMillis >= millisStart)
	{
		this->isFading = true;
		long difference = currentMillis - millisStart;

		double timeLeftPercent = difference * 1.0 * 100 / this->milisCountForFullBrightness;

		if (timeLeftPercent - this->previousTimeLeftPercent > 0)
		{
			if (this->brightnessGoingUp)
				this->currentBrightness += round((timeLeftPercent - this->previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100);
			else
				this->currentBrightness -= round((timeLeftPercent - this->previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100);

			this->previousTimeLeftPercent = timeLeftPercent;

			if (timeLeftPercent >= 100 ||
				(brightnessGoingUp && currentBrightness >= brightnessToSet) ||
				(!brightnessGoingUp && currentBrightness <= brightnessToSet))
			{
				this->currentBrightness = this->brightnessToSet;
				this->isFadingPlanned = this->isFading = false;
				this->millisStart = 0;
			}

			SetPWM(this->currentBrightness);
		}
	}
}

void LedStrip::SetPWM(int pwmValue)
{
	if (pwmValue >= MAX_LED_BRIGHTNESS)
		pwmValue = MAX_LED_BRIGHTNESS;
	else if (pwmValue <= 0)
		pwmValue = 0;
	else
		pwmValue = MAX_LED_BRIGHTNESS - pwmValue;

	logger.Log("[");
	logger.Log(this->channel);
	logger.Log("] current brightness: ");
	logger.LogLine(pwmValue);

	this->pwm.setPWM(this->channel, pwmValue, 0);
}

bool LedStrip::IsBrightnessGoingUp()
{
	return this->brightnessGoingUp;
}

bool LedStrip::IsFading()
{
	return this->isFading;
}

bool LedStrip::IsFadePlanned()
{
	return this->isFadingPlanned;
}

FadeInfo* LedStrip::GetFadePlan()
{
	return fadePlan;
}

double LedStrip::GetCurrentBrightness()
{
	return this->currentBrightness;
}

void LedStrip::SetMinLevel(int minLevel)
{
	this->minLevel = minLevel;
	Fade(this->minLevel, 0);
}

void LedStrip::SetMaxLevel(int maxLevel)
{
	this->maxLevel = maxLevel;
}

int LedStrip::GetMinLevelPwm()
{
	return this->minLevel * 1.0 * MAX_LED_BRIGHTNESS / 100;
}

int LedStrip::GetMaxLevelPwm()
{
	return this->maxLevel * 1.0 * MAX_LED_BRIGHTNESS / 100;
}

bool LedStrip::IsFadedToMinLevel()
{
	return GetCurrentBrightness() == GetMinLevelPwm();
}

bool LedStrip::IsFadedToMaxLevel()
{
	return GetCurrentBrightness() == GetMaxLevelPwm();
}