#include "Arduino.h"
#include "application/app_LCD.h"
#include "application/app_Buttons.h"
#define TEST
#ifdef TEST
#include "test/Test_Cases.h"
#endif

//The setup function is called once at startup of the sketch
void setup()
{
	/* Init LCD Module */
	app_LCD_Init();
	/* Init Buttons Module */
	app_Buttons_init();
}

// The loop function is called in an endless loop
void loop()
{
#ifdef TEST
//	Test_Case_LCD();
	Test_Case_Buttons();
#endif
}
