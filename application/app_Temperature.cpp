/*
 * app_Temperature.cpp
 *
 *  Created on: 16/11/2018
 *      Author: Omar Sevilla
 */

/* Interfaces */
#include "app_Temperature.h"
#include <DallasTemperature.h>

/* Variables */
unsigned long rul_DesiredTemperature;
unsigned long rul_DecDesiredTemperature;
unsigned long re_TempAddMode;
unsigned long rub_TempSamples;
float ruw_AverageTemp;
unsigned char rub_DecAverageTemp;
unsigned long raul_Samples[APP_TEMP_MAX_SAMPLES];
unsigned char rub_SampleIndex;
unsigned char rub_IsBufferFull;

OneWire	SensorPin(36u); //Data Pin
DallasTemperature TempSensor(&SensorPin);

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
	/* Init Desired Temperature */
	rul_DesiredTemperature = 25u;
	rul_DecDesiredTemperature = 0u;
	/* Table index clear */
	rub_SampleIndex = 0u;
	/* Clear Buffer Flag */
	rub_IsBufferFull = false;
	/* Init Temp Sensor */
	TempSensor.begin();
}

/*************************************
 * Name: app_Temperature_Task
 * Description: Temperature Sampling
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Temperature_Task(void)
{
	DeviceAddress laub_DeviceAddress;
	unsigned char lub_i;

	/* Request data */
	TempSensor.requestTemperatures();
	/* Store Temperatures */
	TempSensor.getAddress(laub_DeviceAddress,0);
	ruw_AverageTemp = TempSensor.getTempC(laub_DeviceAddress);
//	raul_Samples[rub_SampleIndex] = TempSensor.getTemp(laub_DeviceAddress);

//	/* Validity of max num samples */
//	if(0u == rub_TempSamples)
//	{
//		rub_TempSamples = 1u;
//	}
//	else
//	{
//		/* Num Samples Valid */
//	}
//
//	/* Increase Sample counter */
//	if(rub_SampleIndex < (rub_TempSamples - 1u))
//	{
//		rub_SampleIndex++;
//	}
//	else
//	{
//		/* Buffer Filled */
//		rub_IsBufferFull = true;
//		rub_SampleIndex = 0u;
//	}
//
//	/* Averaging */
//	if(true == rub_IsBufferFull)
//	{
//		ruw_AverageTemp = (unsigned int)raul_Samples[0u];
//		for(lub_i = 1u; lub_i < rub_TempSamples; lub_i++)
//		{
//			ruw_AverageTemp += raul_Samples[lub_i];
//			ruw_AverageTemp /= 2u;
//		}
//	}
//	else
//	{
//		/* Wait for first run */
//	}
}

/*************************************
 * Name: app_Temperature_GetTemp
 * Description: Temperature Getting
 * Parameters: N/A
 * Return: N/A
 *************************************/
unsigned int app_Temperature_GetTemp(void)
{
	return ruw_AverageTemp;
}
