#include "Arduino.h"
#include "application/app_LCD.h"
#include "application/app_Buttons.h"
#include "application/app_Menu.h"
#include "application/app_Temperature.h"
#include "application/app_Display.h"
#include "application/app_LimitSwitch.h"
#include "application/app_StepperMotor.h"
#include "application/app_Eeprom.h"
#include "application/app_PID.h"

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
	app_PID_Task();
#endif
}
