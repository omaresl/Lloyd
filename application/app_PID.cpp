/*
 * app_PID.c
 *
 *  Created on: 17 nov 2018
 *      Author: Admin
 */

/* Interfaces */
#include "app_PID.h"

/* Variables */
float rub_ConstP;
float rub_ConstI;
float rub_ConstD;

/*************************************
 * Name: app_PID_Init
 * Description: PID Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_PID_Init(void)
{

}

/*************************************
 * Name: app_PID_Task
 * Description: PID Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_PID_Task(void)
{
	float	lf_error;
	float	lf_POut;
	float	lf_PIDOut;

	/* Calculate Error */
	lf_error = ruw_AverageTemp - rul_DesiredTemperature;

	/*******************************************************************************/
	/* Calculate Proportional Output */
	lf_POut = lf_error*rub_ConstP*10.00;//*((float)(rul_LimitPosition/100.0));

	/*******************************************************************************/
	/* Calculate Integral Output */

	/*******************************************************************************/
	/* Calculate Derivative Output */

	/*******************************************************************************/

	/* Add all PID outputs*/
	lf_PIDOut = lf_POut;

	/* Execute Control */
	if(ADD_COLD == re_TempAddMode)
	{
		if(lf_PIDOut > 0u)//Positive error
		{
			/* Open the valve depending on the calculated output */
			app_StepperMotor_GoToPosition(lf_PIDOut);
		}
		else
		{//Negative error - low temperature - stop adding cold
			/* Close the valve */
			app_StepperMotor_GoHome();
		}
	}
	else //ADD_HEAT
	{
		if(lf_PIDOut < 0u)//Negative error
		{
			lf_PIDOut *= -1.0;
			/* Open the valve depending on the calculated output */
			app_StepperMotor_GoToPosition(lf_PIDOut);
		}
		else
		{//Positive error - high temperature - stop adding heat
			/* Close the valve */
			app_StepperMotor_GoHome();
		}
	}
}
