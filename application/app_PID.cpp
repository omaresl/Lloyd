/*
 * app_PID.c
 *
 *  Created on: 17 nov 2018
 *      Author: Admin
 */

/* Interfaces */
#include "app_PID.h"

/* Variables */
unsigned char rub_PastErrorsIndex;
float rf_PastErrors[APP_PID_N_PAST_ERRORS];

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
	/* Clean Past Error Index */
	rub_PastErrorsIndex = 0;

	/* Clean Past Errors Buffer */
	for(unsigned char lub_i = 0; lub_i < APP_PID_N_PAST_ERRORS; lub_i++)
	{
		rf_PastErrors[lub_i] = 0u;
	}
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
	float	lf_POut,lf_IOut, lf_DOut;
	float	lf_PIDOut;

	/* Calculate Error */
	lf_error = ruw_AverageTemp - rul_DesiredTemperature;

	/*******************************************************************************/
	/* Calculate Proportional Output */
	lf_POut = lf_error*rub_ConstP*5.00;//*((float)(rul_LimitPosition/100.0));

	/*******************************************************************************/
	/* Calculate Integral Output */
	/*Store Actual Error in the past errors buffer*/
	rf_PastErrors[rub_PastErrorsIndex] = lf_error;

	/* Increase Index */
	if(rub_PastErrorsIndex < (APP_PID_N_PAST_ERRORS - 1))
	{
		rub_PastErrorsIndex++;
	}
	else
	{
		rub_PastErrorsIndex = 0;
	}

	/* Average all errors */
	lf_IOut = 0.0;
	for(unsigned char lub_i = 0; lub_i < APP_PID_N_PAST_ERRORS; lub_i++)
	{
		lf_IOut += rf_PastErrors[lub_i];
	}
	lf_IOut /= (float)APP_PID_N_PAST_ERRORS;

	lf_IOut *= (rub_ConstI*5.00);

	/*******************************************************************************/
	/* Calculate Derivative Output */

	/*******************************************************************************/

	/* Add all PID outputs*/
	lf_PIDOut = (lf_POut + lf_IOut);

	/* Is a significative action? */
	if(abs((int)lf_PIDOut) >= APP_PID_MIN_OUT_VALID)
	{
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
	else
	{
		//Do nothing
	}
}
