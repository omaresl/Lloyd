/*
 * app_Misc.cpp
 *
 *  Created on: 25 nov. 2018
 *      Author: Admin
 */


/* Interfaces */
#include "app_Misc.h"

/* Private Type definitions */

/* Private Macros */

/* Public Variables */

/* Private Variables */

/* Private Prototypes */


/* Functions */
/*************************************
 * Name: app_Misc_FloatMax
 * Description: Returns the max value of a float array
 * Parameters: N/A
 * Return: N/A
 *************************************/
float app_Misc_FloatMax(float* lp_FloatArray, unsigned int lul_size)
{
	float lf_Return;

	lf_Return = lp_FloatArray[0];
	for(unsigned int lub_i = 1; lub_i < lul_size; lub_i++)
	{
		if(lp_FloatArray[lub_i] > lf_Return)
		{
			lf_Return = lp_FloatArray[lub_i];
		}
		else
		{
			/* Keep Last Value */
		}
	}

	return lf_Return;
}

/*************************************
 * Name: app_Misc_FloatMin
 * Description: Returns the min value of a float array
 * Parameters: N/A
 * Return: N/A
 *************************************/
float app_Misc_FloatMin(float* lp_FloatArray, unsigned int lul_size)
{
	float lf_Return;

	lf_Return = lp_FloatArray[0];
	for(unsigned int lub_i = 1; lub_i < lul_size; lub_i++)
	{
		if(lp_FloatArray[lub_i] < lf_Return)
		{
			lf_Return = lp_FloatArray[lub_i];
		}
		else
		{
			/* Keep Last Value */
		}
	}

	return lf_Return;
}
