/*
 * Test_Cases.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "Test_Cases.h"


/*************************************
 * Name: Test_Case_LCD
 * Description: LCD Test Routine
 * Parameters: N/A
 * Return: N/A
 *************************************/
void Test_Case_LCD(void)
{
	/* Set Cursor */
	LCD.setCursor(0u,1u);
	/* Print Test Text */
	LCD.print("Omar Sevilla    ");
	/* Wait 1s */
	delay(1000u);
	/* Set Cursor */
	LCD.setCursor(0u,1u);
	/* Print Test Text */
	LCD.print("LCD Test Code   ");
	/* Wait 1s */
	delay(1000u);
	/* Set Cursor */
	LCD.setCursor(0u,1u);
	/* Activate Blink */
	LCD.blink();
	/* Print Test Text */
	LCD.print("Sucessfull      ");
	/* Wait 1s */
	delay(1000u);
	/* Stop Blink */
	LCD.noBlink();

}

/*************************************
 * Name: Test_Case_Buttons
 * Description: Buttons Test Routine
 * Parameters: N/A
 * Return: N/A
 *************************************/
void Test_Case_Buttons(void)
{
	T_BUTTONS le_ButtonPressed;

	/* Set Cursor */
	LCD.setCursor(0u,1u);
	/*  Read Buttons */
	le_ButtonPressed = app_Buttons_GetButtonPressed();

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
