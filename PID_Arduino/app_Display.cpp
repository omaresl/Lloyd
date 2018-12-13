/*
 * app_Display.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "app_Display.h"

/* Variables */
T_DISPLAY re_DisplayMode;
static T_BUTTONS re_ButtonPressed,re_LastButtonPressed;


/* Functions */

/*************************************
 * Name: app_Display_Init
 * Description: Display Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Display_Init(void)
{
	/* Init in Normal Mode */
	re_DisplayMode = DISPLAY_NORMAL;

	re_ButtonPressed = BUTTON_NONE;
	re_LastButtonPressed = BUTTON_NONE;
}

/*************************************
 * Name: app_Display_Task
 * Description: Display Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Display_Task(void)
{
	/* Show the corresponding data according the mode */
	if(DISPLAY_NORMAL == re_DisplayMode)
	{
		LCD.noBlink();
		/* Display Actual Temperature */
		LCD.setCursor(0,0);
		LCD.print("Temp:          ");
		LCD.setCursor(6,0);
		LCD.print(ruw_AverageTemp,1);
		if(ADD_COLD == re_TempAddMode)
		{
			LCD.print(" Mc");
		}
		else
		{
			LCD.print(" Mh");
		}

		//		if(LIMITSTATE_INRANGE == re_LimitState)
		//		{
		/* Display Fixed Temperature */
		LCD.setCursor(0,1);
		LCD.print("Fixed Temp: ");
		LCD.print(rul_DesiredTemperature,1);
		//		}
		//		else
		//		{
		//			/* Keep the text left by LimitSwitch */
		//		}
		re_ButtonPressed = app_Buttons_GetButtonPressed();
		if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_SELECT == re_ButtonPressed))
		{
			re_DisplayMode = DISPLAY_CONFIG;
			LCD.setCursor(0,0);
			LCD.print("Release Button  ");
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}
		}
		else if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_RIGHT == re_ButtonPressed))
		{
			re_DisplayMode = DISPLAY_MANUAL;
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}

		}
		else if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_LEFT == re_ButtonPressed))
		{
			re_DisplayMode = DISPLAY_MANUAL;
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}
		}
		else
		{
			/* Do nothing */
		}
		re_LastButtonPressed = re_ButtonPressed;
	}
	else if(DISPLAY_MANUAL == re_DisplayMode)
	{
		LCD.noBlink();
		/* Display Actual Temperature */
		LCD.setCursor(0,0);
		LCD.print("Manual Mode    ");
		LCD.setCursor(0,1);
		LCD.print("Temp:          ");
		LCD.setCursor(6,1);
		LCD.print(ruw_AverageTemp,1);

		re_ButtonPressed = app_Buttons_GetButtonPressed();
		if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_SELECT == re_ButtonPressed))
		{
			re_DisplayMode = DISPLAY_NORMAL;
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}
		}
		else if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_RIGHT == re_ButtonPressed))
		{
			app_StepperMotor_GoLimit();
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}

		}
		else if((BUTTON_NONE == re_LastButtonPressed) &&
				(BUTTON_LEFT == re_ButtonPressed))
		{
			app_StepperMotor_GoHome();
			while(BUTTON_NONE != re_ButtonPressed)
			{
				re_ButtonPressed = app_Buttons_GetButtonPressed();
			}
		}
	}
	else
	{
		LCD.setCursor(0,0);
		LCD.print("Config Mode     ");
		do
		{
			app_Menu_Task();

		}while(DISPLAY_CONFIG == re_DisplayMode);
		LCD.setCursor(0,0);
		LCD.print("Changing Mode   ");
	}
}

/*************************************
 * Name: app_Display_Mode
 * Description: Function for set display mode
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Display_Mode(T_DISPLAY le_Mode)
{
	re_DisplayMode = le_Mode;
}

