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

/* Extern variables */
extern unsigned long rul_DesiredTemperature;
extern unsigned long re_TempAddMode;
extern unsigned long rub_TempSamples;


#endif /* APPLICATION_APP_TEMPERATURE_H_ */
