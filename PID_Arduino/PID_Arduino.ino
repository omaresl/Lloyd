#include "Arduino.h"
#include "app_LCD.h"
#include "app_Buttons.h"
#include "app_Menu.h"
#include "app_Temperature.h"
#include "app_Display.h"
#include "app_LimitSwitch.h"
#include "app_StepperMotor.h"
#include "app_Eeprom.h"
#include "app_PID.h"

//#define TEST

//The setup function is called once at startup of the sketch
void setup()
{
	/* Limit Switch */
	app_LimitSwitch_Init();
	/* Temperature Init */
	app_Temperature_Init();
	/* Init LCD Module */
	app_LCD_Init();
	/* Display init */
	app_Display_Init();
	/* Init Buttons Module */
	app_Buttons_init();
	/* Menu Init */
	app_Menu_init();
	/* Stepper Init */
	app_StepperMotor_Init();
	/* Eeprom Init */
	app_Eeprom_Init();
	/* PID Init */
	app_PID_Init();
}

// The loop function is called in an endless loop
void loop()
{
#ifdef TEST
	LCD.setCursor(0,0);
	LCD.print("ADC Value of button pressed");
	LCD.setCursor(0,1);
	LCD.print(analogRead(A0));
	LCD.print("            ");

#else
	app_LimitSwitch_Task();
	app_Temperature_Task();
	app_Display_Task();
	if(DISPLAY_NORMAL == re_DisplayMode)
	{
		app_PID_Task();
	}
	else
	{
		/* PID Disabled */
	}
#endif
}
