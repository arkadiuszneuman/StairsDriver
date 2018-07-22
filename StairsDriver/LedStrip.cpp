#include "LedStrip.h"

LedStrip::LedStrip(Adafruit_PWMServoDriver pwm, int channel, int milisCountForFullBrightness)
{
	this->pwm = &pwm;
	this->channel = channel;
	this->milisCountForFullBrightness = milisCountForFullBrightness;
}

void LedStrip::LightUp(int brightnessPercent)
{
	this->brightnessToSet = brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100;
	this->millisStart = millis();
}

void LedStrip::Update()
{
	long currentMillis = millis();
	long difference = currentMillis - millisStart;

	double timeLeftPercent = difference * 1.0 * 100 / this->milisCountForFullBrightness;
	if (timeLeftPercent > 100)
	{
		this->pwm->setPWM(this->channel, 4096, 0);
		return;
	}

	double currentBrightness = timeLeftPercent * MAX_LED_BRIGHTNESS / 100;

	this->pwm->setPWM(this->channel, currentBrightness, 0);
}


