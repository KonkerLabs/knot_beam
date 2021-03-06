#include <Arduino.h>
#include <EEPROM.h>
/*
 * Copyright (c) 2017, CESAR.
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 *
 */

/*
 * The default behavior for a Thing is to send data every 30 seconds.
 * To change its behavior on the firmware side, use the function
 * registerDefaultConfig(). See the documentation and lib examples.
 */

#include <KNoTThing.h>

#define BEAM_SENSOR_1_ID      1
#define BEAM_SENSOR_1_NAME    "MY BEAM Sensor 1"
#define BEAM_SENSOR_1_PIN     2

#define BEAM_SENSOR_2_ID      2
#define BEAM_SENSOR_2_NAME    "MY BEAM Sensor 2"
#define BEAM_SENSOR_2_PIN     5

static KNoTThing thing;


void clearEEPROM(){
	// initialize the LED pin as an output.
	//pinMode(13, OUTPUT);

	/***
		Iterate through each byte of the EEPROM storage.

		Larger AVR processors have larger EEPROM sizes, E.g:
		- Arduno Duemilanove: 512b EEPROM storage.
		- Arduino Uno:        1kb EEPROM storage.
		- Arduino Mega:       4kb EEPROM storage.

		Rather than hard-coding the length, you should use the pre-provided length function.
		This will make your code portable to all AVR processors.
	***/

	for (int i = 0 ; i < EEPROM.length() ; i++) {
		EEPROM.write(i, 0);
	}
	Serial.println(F("EEPROM cleared!"));
	// turn the LED on when we're done
	//digitalWrite(13, HIGH);
}


static int beam_read_1(uint8_t *val)
{
	*val = digitalRead(BEAM_SENSOR_1_PIN);
	//Serial.println(F("Mudou beam 1"));
	return 0;
}

static int beam_read_2(uint8_t *val)
{
	*val = digitalRead(BEAM_SENSOR_2_PIN);
	//Serial.println(F("Mudou beam 2"));
	return 0;
}

void setup()
{
	Serial.begin(115200);

	//uncomment for tests
	//clearEEPROM();
	//delay(1000000);

	pinMode(BEAM_SENSOR_1_PIN, INPUT);
	pinMode(BEAM_SENSOR_2_PIN, INPUT);

	thing.init("Sensor MY BEAM");

	thing.registerBoolData(BEAM_SENSOR_1_NAME, BEAM_SENSOR_1_ID,
			KNOT_TYPE_ID_PRESENCE, KNOT_UNIT_NOT_APPLICABLE,
			beam_read_1, NULL);

	thing.registerBoolData(BEAM_SENSOR_2_NAME, BEAM_SENSOR_2_ID,
			KNOT_TYPE_ID_PRESENCE, KNOT_UNIT_NOT_APPLICABLE,
			beam_read_2, NULL);

	/*Every time the Beam sensor changes its value, it send data*/
	thing.registerDefaultConfig(BEAM_SENSOR_1_ID, KNOT_EVT_FLAG_CHANGE, 0, 0, 0, 0, 0);

	thing.registerDefaultConfig(BEAM_SENSOR_2_ID, KNOT_EVT_FLAG_CHANGE, 0, 0, 0, 0, 0);

	Serial.println(F("Beam Sensor KNoT Demo"));
}

void loop()
{

	thing.run();
}
