#include "Arduino.h"
#include "application/app_LCD.h"
#include "application/app_Buttons.h"
#include "application/app_Menu.h"
#include "application/app_Temperature.h"
#include "application/app_PID.h"
#include "application/app_Display.h"

//#define TEST
#ifdef TEST
#include "test/Test_Cases.h"
#endif

//The setup function is called once at startup of the sketch
void setup()
{
	/* Temperature Init */
	app_Temperature_Init();
	/* Init LCD Module */
	app_LCD_Init();
	/* Init Buttons Module */
	app_Buttons_init();
	/* Menu Init */
	app_Menu_init();

}

// The loop function is called in an endless loop
void loop()
{
	app_Menu_Task();
#ifdef TEST
//	Test_Case_LCD();
//	Test_Case_Buttons();
#endif
}
