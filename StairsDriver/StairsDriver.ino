
/***************************************************
This is an example for our Adafruit 16-channel PWM & Servo driver
****************************************************/

#include "StairsLedDriver.h"

StairsLedDriver stairsLedDriver;

void setup() {
	Serial.begin(9600);
	stairsLedDriver.Begin(3);
}

void loop() {
	stairsLedDriver.Update();
}