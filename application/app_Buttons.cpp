/*
 * app_Buttons.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "app_Buttons.h"


/* Function Definitions */

/*************************************
 * Name: app_Buttons_Init
 * Description: Buttons Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Buttons_init(void)
{

}

T_BUTTONS app_Buttons_GetButtonPressed(void)
{
	unsigned int lul_AnalogData;
	T_BUTTONS le_Return;

	lul_AnalogData = analogRead(A0);       // read the value from the sensor

	if (lul_AnalogData > 1000) return BUTTON_NONE;

	// For V1.1 us this threshold
	if (lul_AnalogData < 50)   le_Return = BUTTON_RIGHT;
	if (lul_AnalogData < 250)  le_Return = BUTTON_UP;
	if (lul_AnalogData < 450)  le_Return = BUTTON_DOWN;
	if (lul_AnalogData < 650)  le_Return = BUTTON_LEFT;
	if (lul_AnalogData < 850)  le_Return = BUTTON_SELECT;

	return le_Return;
}
