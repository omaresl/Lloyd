/*
 * app_Temperature.h
 *
 *  Created on: 16/11/2018
 *      Author: Omar Sevilla
 */

#ifndef APPLICATION_APP_TEMPERATURE_H_
#define APPLICATION_APP_TEMPERATURE_H_

/* Interfaces */
#include <Arduino.h>

/* Typedefs */

/* Macros */
#define 	ADD_COLD	false
#define 	ADD_HEAT	true

#define APP_TEMP_MAX_SAMPLES	(100u)
#define APP_TEMP_MIN_SAMPLES	(1u)

/* Extern variables */
extern unsigned long rul_DesiredTemperature;
extern unsigned long rul_DecDesiredTemperature;
extern unsigned long re_TempAddMode;
extern unsigned long rub_TempSamples;
extern unsigned int ruw_AverageTemp;
extern unsigned char rub_DecAverageTemp;

/* Public Funcitons */
extern void app_Temperature_Init(void);
extern void app_Temperature_Task(void);
extern unsigned int app_Temperature_GetTemp(void);


#endif /* APPLICATION_APP_TEMPERATURE_H_ */
