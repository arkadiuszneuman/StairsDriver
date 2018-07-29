#include "LedStrip.h"

LedStrip::LedStrip(Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness)
{
	this->pwm = pwm;
	this->channel = channel;
	this->milisCountForFullBrightness = milisCountForFullBrightness;
	this->brightnessToSet = 0;
	this->millisStart = 0;
	this->currentBrightness = 1;
}

void LedStrip::LightUp(int brightnessPercent)
{
	this->brightnessToSet = brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100;
	this->brightnessGoingUp = this->brightnessToSet > this->currentBrightness;
	Serial.print("Setting percent ");
	Serial.println(brightnessPercent);
	Serial.print("Setting brightness ");
	Serial.println(brightnessToSet);
	Serial.print("GoingUp ");
	Serial.println(brightnessGoingUp);
	this->millisStart = millis();
}

void LedStrip::Update()
{
	if (this->brightnessToSet != this->currentBrightness)
	{
		long currentMillis = millis();
		long difference = currentMillis - millisStart;

		double timeLeftPercent = difference * 1.0 * 100 / this->milisCountForFullBrightness;

		if (timeLeftPercent >= 100)
		{
			this->currentBrightness = this->brightnessToSet;
			SetPWM(this->currentBrightness);
			return;
		}

		if (this->brightnessGoingUp)
			this->currentBrightness = timeLeftPercent * MAX_LED_BRIGHTNESS / 100;
		else
			this->currentBrightness = MAX_LED_BRIGHTNESS - (timeLeftPercent * MAX_LED_BRIGHTNESS / 100);

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
	Serial.println(this->channel);
	Serial.print("] current brightness: ");
	Serial.println(pwmValue);

	this->pwm.setPWM(this->channel, pwmValue, 0);
}


