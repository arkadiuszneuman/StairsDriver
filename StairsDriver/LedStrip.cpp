#include "LedStrip.h"

LedStrip::LedStrip(Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness)
{
	this->pwm = pwm;
	this->channel = channel;
	this->milisCountForFullBrightness = milisCountForFullBrightness;
	this->SetPWM(0);
}

void LedStrip::Fade(int brightnessPercent, int delay)
{
	this->brightnessToSet = brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100;
	this->brightnessGoingUp = this->brightnessToSet > this->currentBrightness;
	this->millisStart = millis() + delay;
	this->isFadingPlanned = true;
	this->previousTimeLeftPercent = 0;

	Serial.print("Setting percent ");
	Serial.println(brightnessPercent);
	Serial.print("Setting brightness ");
	Serial.println(brightnessToSet);
	Serial.print("GoingUp ");
	Serial.println(brightnessGoingUp);
}

void LedStrip::Update()
{
	if (!this->isFadingPlanned)
		return;

	long currentMillis = millis();
	if (currentMillis >= millisStart)
	{
		this->isFading = true;
		long difference = currentMillis - millisStart;

		double timeLeftPercent = difference * 1.0 * 100 / this->milisCountForFullBrightness;
		Serial.println(timeLeftPercent);
		if (this->brightnessGoingUp)
			this->currentBrightness += (timeLeftPercent - this->previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100;
		else
			this->currentBrightness -= (timeLeftPercent - this->previousTimeLeftPercent) * MAX_LED_BRIGHTNESS / 100;

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

void LedStrip::SetPWM(int pwmValue)
{
	if (pwmValue >= MAX_LED_BRIGHTNESS)
		pwmValue = MAX_LED_BRIGHTNESS;
	else if (pwmValue <= 0)
		pwmValue = 0;
	else
		pwmValue = MAX_LED_BRIGHTNESS - pwmValue;

	Serial.print("[");
	Serial.print(this->channel);
	Serial.print("] current brightness: ");
	Serial.println(pwmValue);

	this->pwm.setPWM(this->channel, pwmValue, 0);
}

int LedStrip::GetCurrentBrightness()
{
	return this->currentBrightness;
}

bool LedStrip::IsFading()
{
	return this->isFading;
}
