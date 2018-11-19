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
		/* Display Actual Temperature */
		LCD.setCursor(0,0);
		LCD.print("Actual Temp: ");
		LCD.print(ruw_AverageTemp);
		LCD.print('.');
		LCD.print(rub_DecAverageTemp);

		if(LIMITSTATE_INRANGE == re_LimitState)
		{
			/* Display Fixed Temperature */
			LCD.setCursor(0,1);
			LCD.print("Fixed Temp: ");
			LCD.print(rul_DesiredTemperature);
			LCD.print('.');
			LCD.print(rul_DecDesiredTemperature);
		}
		else
		{
			/* Keep the text left by LimitSwitch */
		}
	}
	else
	{
		app_Menu_Task();
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

