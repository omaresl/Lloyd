/*
 * Test_Cases.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "test/Test_Cases.h"


/*************************************
 * Name: Test_Case_LCD
 * Description: LCD Test Routine
 * Parameters: N/A
 * Return: N/A
 *************************************/
void Test_Case_LCD(void)
{
	for(;;)
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
}
