#include "LedStrip.h"

LedStrip::LedStrip(Adafruit_PWMServoDriver &pwm, int channel, int milisCountForFullBrightness)
{
	this->pwm = pwm;
	this->channel = channel;
	this->milisCountForFullBrightness = milisCountForFullBrightness;
	this->brightnessToSet = 0;
	this->millisStart = 0;
	this->currentBrightness = 0;
}

void LedStrip::LightUp(int brightnessPercent)
{
	this->brightnessToSet = brightnessPercent * 1.0 * MAX_LED_BRIGHTNESS / 100;
	if (this->brightnessToSet <= 0)
		this->brightnessToSet = 1;
	this->brightnessGoingUp = this->brightnessToSet > this->currentBrightness;
	Serial.print("Setting brightness ");
	Serial.println(brightnessToSet);
	Serial.print("GoingUp ");
	Serial.println(brightnessGoingUp);
	delay(2000);
	this->millisStart = millis();
}

void LedStrip::Update()
{
	if (this->brightnessToSet != this->currentBrightness)
	{
		long currentMillis = millis();
		long difference = currentMillis - millisStart;

		double timeLeftPercent = difference * 1.0 * 100 / this->milisCountForFullBrightness;

		Serial.print("Time left percent ");
		Serial.println(timeLeftPercent);

		if (timeLeftPercent >= 100)
		{
			this->currentBrightness = this->brightnessToSet;
			this->pwm.setPWM(this->channel, this->brightnessToSet, 0);
			return;
		}

		Serial.print("GoingUp ");
		Serial.println(brightnessGoingUp);

		if (this->brightnessGoingUp)
			this->currentBrightness = timeLeftPercent * MAX_LED_BRIGHTNESS / 100;
		else
			this->currentBrightness = MAX_LED_BRIGHTNESS - (timeLeftPercent * MAX_LED_BRIGHTNESS / 100);

		Serial.print("Current brightness ");
		Serial.println(currentBrightness);
		this->pwm.setPWM(0, currentBrightness, 0);
	}
}


