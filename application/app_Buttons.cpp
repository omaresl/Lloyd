/*
 * app_Buttons.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "app_Buttons.h"

/* Variables */
static T_BUTTONS rub_DebLastButtonPressed;
static T_BUTTONS rub_ValidButtonPressed;
static unsigned char rub_DebCounter;

/* Private Prototypes */
void app_Buttons_Debounce(T_BUTTONS lub_DebActualButtonPressed);

/* Function Definitions */

/*************************************
 * Name: app_Buttons_Init
 * Description: Buttons Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Buttons_init(void)
{
	analogReference(DEFAULT);

	/* Init Debounce Variables */
	rub_DebLastButtonPressed = BUTTON_NONE;
	rub_ValidButtonPressed = BUTTON_NONE;
	rub_DebCounter = 0u;
}

T_BUTTONS app_Buttons_GetButtonPressed(void)
{
	unsigned int lul_AnalogData;
	T_BUTTONS le_Return;

	lul_AnalogData = analogRead(0u);       // read the value from the sensor

	if (lul_AnalogData > 1000)
	{
		le_Return = BUTTON_NONE;
	}
	// For V1.1 us this threshold
	else if (lul_AnalogData < 50)
	{
		le_Return = BUTTON_RIGHT;
	}
	else if (lul_AnalogData < 250)
	{
		le_Return = BUTTON_UP;
	}
	else if (lul_AnalogData < 450)
	{
		le_Return = BUTTON_DOWN;
	}
	else if (lul_AnalogData < 650)
	{
		le_Return = BUTTON_LEFT;
	}
	else if (lul_AnalogData < 850)
	{
		le_Return = BUTTON_SELECT;
	}
	else
	{
		le_Return = BUTTON_INVALID;
	}

	app_Buttons_Debounce(le_Return);

	le_Return = rub_ValidButtonPressed;

	return le_Return;
}

/*************************************
 * Name: app_Buttons_Init
 * Description: Buttons Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Buttons_PrintButton(T_BUTTONS le_ButtonPressed)
{
	/* Print Button Pressed */
	switch(le_ButtonPressed)
	{
	case BUTTON_RIGHT:
	{
		/* Print Test Text */
		LCD.print("RIGHT BUTTON    ");
	}break;
	case BUTTON_UP:
	{
		/* Print Test Text */
		LCD.print("UP BUTTON       ");
	}break;
	case BUTTON_DOWN:
	{
		/* Print Test Text */
		LCD.print("DOWN BUTTON     ");
	}break;
	case BUTTON_LEFT:
	{
		/* Print Test Text */
		LCD.print("LEFT BUTTON     ");
	}break;
	case BUTTON_SELECT:
	{
		/* Print Test Text */
		LCD.print("SELECT BUTTON   ");
	}break;
	default:
	{
		/* Print Test Text */
		LCD.print("NO BUTTON PRESS ");
	}break;
	}
}

/*************************************
 * Name: app_Buttons_Debounce
 * Description: Debounce function
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Buttons_Debounce(T_BUTTONS lub_DebActualButtonPressed)
{
	/* Check if the same buttons still pressed */
	if(rub_DebLastButtonPressed == lub_DebActualButtonPressed)
	{
		/* Increase counter if equal */
		rub_DebCounter++;
		if(rub_DebCounter >= APP_BUTTONS_DEBOUNCE)
		{
			rub_ValidButtonPressed = lub_DebActualButtonPressed;
		}
		else
		{
			/* Wait for a valid button */
		}
	}
	else
	{
		/* Reset the counter if */
		rub_DebCounter = 0u;
	}

	/* Update Last Button */
	rub_DebLastButtonPressed = lub_DebActualButtonPressed;
}
