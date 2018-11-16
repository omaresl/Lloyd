#include "Arduino.h"
#include "application/app_LCD.h"
#define TEST_LCD
#ifdef TEST_LCD
#include "test/Test_Cases.h"
#endif

//The setup function is called once at startup of the sketch
void setup()
{
	/* Init LCD Module */
	app_LCD_Init();
}

// The loop function is called in an endless loop
void loop()
{
#ifdef TEST_LCD
	Test_Case_LCD();
#endif
}
