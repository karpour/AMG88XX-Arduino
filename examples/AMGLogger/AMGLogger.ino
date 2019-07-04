/**
 * @file AMGLogger.ino
 * @author Thomas Novotny
 * @brief Test program that logs sensor values to serial port
 * @version 0.1
 * 
 * Test program that logs the sensor values via the serial port at 115200baud
 * Once any character is received over serial, the AMG wakes up, stabilizes (15sec!)
 * and data is sent back.
 */

#include "AMG88XX.h"

char addr = 0x68;

void setup() {
	// Setup I2C with 400khz
	Wire.setClock(400000);
	Wire.begin();

	// Initialize UART with 115200 baud
	Serial.begin(115200);

	reset();
	setFrameRate(AMG_FPSC_FRAMERATE_1);

	pinMode(13, OUTPUT);
}

void loop() {
	while(Serial.read()==-1); // Wait for input

	wakeUp();
	delay(15000); // AMG needs ~15 seconds to stabilize after waking up

	float data[64];

	readValues(data);

	float variance = calculateVariance(data);
	for (int pixel = 0; pixel < 64; pixel++) {
		Serial.print(data[pixel]);
		Serial.print(",");
	}
	Serial.print(";");
	Serial.print(readThermistor());
	Serial.println();

	digitalWrite(13, variance>0.8);

	sleep();

	//standBy10();
	//delay(500);
}
