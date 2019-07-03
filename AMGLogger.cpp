#include "AMG88XX.h"

char addr = 0x68;

void setup() {
	// Setup I²C with 400khz
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
	delay(15000);

	long t_start = millis();

	float data[64];

	readValues(data);
	long t_1 = millis()-t_start;

	t_start = millis();
	float variance = calculateVariance(data);
	long t_2 = millis()-t_start;
	for (int pixel = 0; pixel < 64; pixel++) {
		Serial.print(data[pixel]);
		Serial.print(",");
	}
	Serial.print(";");
	Serial.print(readThermistor());
	Serial.println();

	/*Serial.print("V = ");
	Serial.println(variance);
	Serial.print("T = ");
	Serial.print(t_1);
	Serial.print("/");
	Serial.println(t_2);*/


	digitalWrite(13, variance>0.8);



	/*byte pixelTempL = AMG_REGISTER_T01L;
	for (int pixel = 0; pixel < 64; pixel++) {
		delay(1);
		Wire.beginTransmission(addr);
		Wire.write(pixelTempL);
		Wire.endTransmission();
		Wire.requestFrom(addr, 2);
		byte lowerLevel = Wire.read();
		byte upperLevel = Wire.read();

		int temperature = ((upperLevel << 8) | lowerLevel);
		if (temperature > 2047) {
			temperature = temperature - 4096;
		}

		float celsius = temperature * 0.25;
		Serial.print(celsius);
		Serial.print(",");
		pixelTempL = pixelTempL + 2;
	}
	Serial.print(";");
	Serial.print(readThermistor());
	Serial.println();
	*/


	sleep();

	//standBy10();
	//delay(500);
}
