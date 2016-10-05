#include <EEPROM.h>

#define plusButton digitalRead(2)
#define minusButton digitalRead(4)
#define powerButton digitalRead(5)

int brightness=127;
bool power;
bool highBeam=false;
bool powerPressed;
bool powerLockout;
long time,eepromTime=0;
uint32_t counter;
byte divisor = 6;

void setup()
{

	Serial.begin(9600);

	for (int i = 2; i < 6; i++)
		pinMode(i, INPUT_PULLUP);
	
	pinMode(3, OUTPUT);
	digitalWrite(3, LOW);
	pinMode(11, OUTPUT);

	TCCR2B = TCCR2B & 0b11111000 | divisor;  // for pin 11
	//TCCR0B = TCCR0B & 0b11111000 | divisor; // for pin 5&6

	int freq = 31250;

	switch (divisor) {
	case 1: freq /= 1; break;
	case 2: freq /= 8; break;
	case 3: freq /= 32; break;
	case 4: freq /= 64; break;
	case 5: freq /= 128; break;
	case 6: freq /= 256; break;
	case 7: freq /= 1024; break;
	}
									 
	Serial.print(freq);
	Serial.println(" Hz");

	power = EEPROM.read(0);
	brightness = EEPROM.read(1);
}

void loop() {
	if (plusButton == false) {
		brightness++;
		delay(5);
	}
	if (minusButton == false) {
		brightness--;
		delay(5);
	}
	if (brightness > 255)
		brightness = 255;
	if (brightness<1)
		brightness = 1;

	time = millis();
	if (powerButton)
		powerLockout = false;
	while (!powerButton && !powerLockout) {
		powerPressed = true;
		if (millis() > time+500) {
			Serial.println(time);
			power = !power;
			time = millis();
			powerPressed = false;
			powerLockout = true;
			//break;
		}
	}
	if (powerPressed)
		highBeam = !highBeam;
	powerPressed = false;
	
	if (power) {
		if (highBeam)
			analogWrite(11, 255);
		else
			analogWrite(11, brightness);
	}
	else
		analogWrite(11, 0);
	
	if (millis() > eepromTime + 1000) {
		EEPROM.update(0, power);
		EEPROM.update(1, brightness);
		eepromTime = millis();
	}

}
