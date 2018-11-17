/*
 * app_Temperature.cpp
 *
 *  Created on: 16/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "app_Temperature.h"

/* Variables */
unsigned long rul_DesiredTemperature = 0u;
unsigned long re_TempAddMode;
unsigned long rub_TempSamples;

/*************************************
 * Name: app_Temperature_Init
 * Description: Temperature Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Temperature_Init(void)
{
	/* Init Temp Add Mode */
	re_TempAddMode = 0u;
	/* Init Temp Samples */
	rub_TempSamples = 1u;
}
