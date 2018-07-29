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
	if (this->brightnessToSet <= 0)
		this->brightnessToSet = 1;
	if (this->brightnessToSet >= MAX_LED_BRIGHTNESS)
		this->brightnessToSet = MAX_LED_BRIGHTNESS - 1;
	this->brightnessGoingUp = this->brightnessToSet > this->currentBrightness;
	Serial.print("Setting percent ");
	Serial.println(brightnessPercent);
	Serial.print("Setting brightness ");
	Serial.println(brightnessToSet);
	Serial.print("GoingUp ");
	Serial.println(brightnessGoingUp);
	delay(3000);
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
			Serial.print("End current brightness ");
			Serial.println(MAX_LED_BRIGHTNESS - currentBrightness);
			this->pwm.setPWM(this->channel, MAX_LED_BRIGHTNESS - this->brightnessToSet, 0);
			return;
		}

		Serial.print("GoingUp ");
		Serial.println(brightnessGoingUp);

		if (this->brightnessGoingUp)
			this->currentBrightness = timeLeftPercent * MAX_LED_BRIGHTNESS / 100;
		else
			this->currentBrightness = MAX_LED_BRIGHTNESS - (timeLeftPercent * MAX_LED_BRIGHTNESS / 100);

		Serial.print("Current brightness ");
		Serial.println(MAX_LED_BRIGHTNESS - currentBrightness);
		this->pwm.setPWM(0, MAX_LED_BRIGHTNESS - currentBrightness, 0);
	}
}


