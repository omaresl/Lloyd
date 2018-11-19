#include "Arduino.h"
#include "application/app_LCD.h"
#include "application/app_Buttons.h"
#include "application/app_Menu.h"
#include "application/app_Temperature.h"
#include "application/app_PID.h"
#include "application/app_Display.h"
#include "application/app_LimitSwitch.h"
#include "application/app_StepperMotor.h"

//#define TEST
#ifdef TEST
#include "test/Test_Cases.h"
#endif

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

}

// The loop function is called in an endless loop
void loop()
{
	while(true)
	{
		if(IS_VALVE_FULLY_CLOSED)
		{
			/* Do Nothing */
		}
		else
		{
			app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
		}
		app_LimitSwitch_Task();
		delay(500u);
	}
	app_Temperature_Task();
	app_Display_Task();
#ifdef TEST
	//	Test_Case_LCD();
	//	Test_Case_Buttons();
#endif
}
