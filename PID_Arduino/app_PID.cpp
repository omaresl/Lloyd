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
static float rf_LastColdPIDOut;
static float rf_LastHeatPIDOut;

float rub_ConstP;
float rub_ConstI;
float rub_ConstD;
float rf_Compansate;

/*************************************
 * Name: app_PID_Init
 * Description: PID Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_PID_Init(void)
{
	/* Clean Last PID Out Value */
	rf_LastColdPIDOut = 0;
	rf_LastHeatPIDOut = 0;

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
	signed int	lul_steps;

	/* Calculate Error */
	lf_error = ruw_AverageTemp - rul_DesiredTemperature - rf_Compansate;

	/*******************************************************************************/
	/* Calculate Proportional Output */
	lf_POut = lf_error*rub_ConstP;//*((float)(rul_LimitPosition/100.0));

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

	lf_IOut *= (rub_ConstI);

	/*******************************************************************************/
	/* Calculate Derivative Output */
	//Calculate pendant
	lf_DOut = (rf_PastErrors[APP_PID_N_PAST_ERRORS - 1] - rf_PastErrors[0]);
	lf_DOut *= (rub_ConstD);

	/*******************************************************************************/

	/* Add all PID outputs*/
	lf_PIDOut = (lf_POut + lf_IOut + lf_DOut);

	/* Execute Control */
	if(ADD_COLD == re_TempAddMode)
	{
		lul_steps = (signed int)(lf_PIDOut - rf_LastColdPIDOut);

		if(lf_PIDOut < 0)
		{
			rf_LastColdPIDOut = lf_PIDOut;

			app_StepperMotor_GoHome();
		}
		else if(lul_steps > APP_PID_MIN_COLD_VALID)
		{
			rf_LastColdPIDOut = lf_PIDOut;

			for(signed int lub_i = 0; (lub_i < lul_steps) && (!IS_VALVE_FULLY_OPEN); lub_i++)
			{
				app_StepperMotor_OneStep(APP_STEPPERMOTOR_CNTCLK_DIR);
			}
		}
		else if(lul_steps < APP_PID_MIN_HEAT_VALID)
		{
			rf_LastColdPIDOut = lf_PIDOut;

			for(signed int lub_i = lul_steps; (lub_i < 0) && (!IS_VALVE_FULLY_CLOSED); lub_i++)
			{
				app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
			}
		}
		else
		{
			//Do Nothing
		}
		//		if(lf_PIDOut > APP_PID_MIN_COLD_VALID)//Positive error
		//		{
		//			/* Open the valve depending on the calculated output */
		//			app_StepperMotor_GoToPosition(lf_PIDOut);
		//		}
		//		else if(lf_PIDOut < 0u)
		//		{//Negative error - low temperature - stop adding cold
		//			/* Close the valve */
		//			app_StepperMotor_GoHome();
		//		}
		//		else
		//		{
		//			/* Do nothing */
		//		}
	}
	else //ADD_HEAT
	{
		lul_steps = (signed int)(lf_PIDOut - rf_LastHeatPIDOut);

		if(lf_PIDOut > 0)
		{
			rf_LastHeatPIDOut = lf_PIDOut;

			app_StepperMotor_GoHome();
		}
		else if(lul_steps > APP_PID_MIN_COLD_VALID)
		{
			rf_LastHeatPIDOut = lf_PIDOut;

			for(signed int lub_i = 0; (lub_i < lul_steps) && (!IS_VALVE_FULLY_CLOSED); lub_i++)
			{
				app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
			}
		}
		else if(lul_steps < APP_PID_MIN_HEAT_VALID)
		{
			rf_LastHeatPIDOut = lf_PIDOut;

			for(signed int lub_i = lul_steps; (lub_i < 0) && (!IS_VALVE_FULLY_OPEN); lub_i++)
			{
				app_StepperMotor_OneStep(APP_STEPPERMOTOR_CNTCLK_DIR);
			}
		}
		else
		{
			//Do Nothing
		}
		//		if(lf_PIDOut < APP_PID_MIN_HEAT_VALID)//Negative error
		//		{
		//			lf_PIDOut *= -1.0;
		//			/* Open the valve depending on the calculated output */
		//			app_StepperMotor_GoToPosition(lf_PIDOut);
		//		}
		//		else if( lf_PIDOut > 0)
		//		{//Positive error - high temperature - stop adding heat
		//			/* Close the valve */
		//			app_StepperMotor_GoHome();
		//		}
		//		else
		//		{
		//			/* Do nothing */
		//		}
	}
}
