
/***************************************************
This is an example for our Adafruit 16-channel PWM & Servo driver
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {

	Serial.begin(9600);
	pwm.begin();
	pwm.setPWMFreq(500);  // This is the maximum PWM frequency
}

void loop()
{

	for (int j = 0; j < 3; j++)
	{
		for (int i = 1; i < 4095; i += 5)
		{
			if (i > 4095)
				i = 4095;
			pwm.setPWM(j, 1, i);
			delay(1);
		}

		for (int i = 4095 - 1; i > 1; i -= 5)
		{
			if (i < 1)
				i = 1;
			pwm.setPWM(j, 1, i);
			delay(1);
		}
	}
}