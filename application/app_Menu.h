/*
 * app_Menu.h
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

#ifndef APPLICATION_APP_MENU_H_
#define APPLICATION_APP_MENU_H_

/* Interfaces */
#include <Arduino.h>
#include "app_LCD.h"
#include "app_Buttons.h"
#include "app_Temperature.h"
#include "app_PID.h"
#include "app_Display.h"
#include "app_Eeprom.h"

/* Public Macros */
#define APP_MENU_N_ITEMS	(6u)
#define APP_MENU_ITEMS	\
		{\
	&rul_DesiredTemperature,\
	&re_TempAddMode,\
	&rub_TempSamples,\
	&rub_ConstP,\
	&rub_ConstI,\
	&rub_ConstD,\
		}

#define APP_MENU_ITEMSTEXT	\
		{\
	{"Desired Temp:   "},\
	{"                "},\
	{"Samples:        "},\
	{"P:              "},\
	{"I:              "},\
	{"D:              "},\
		}

#define APP_MENU_APP_MAXLIMITS\
		{\
	99.0,\
	(float)ADD_HEAT,\
	(float)APP_TEMP_MAX_SAMPLES,\
	10.0,\
	10.0,\
	10.0,\
		}

#define APP_MENU_APP_MINLIMITS\
		{\
	0.0,\
	(float)ADD_COLD,\
	(float)APP_TEMP_MIN_SAMPLES,\
	0.0,\
	0.0,\
	0.0,\
		}

#define APP_MENU_EEP_ADDR\
		{\
	EEP_ADDR_FIXED_TEMP	,\
	EEP_ADDR_TEMP_MODE	,\
	EEP_ADDR_SAMPLES	,\
	EEP_ADDR_P			,\
	EEP_ADDR_I			,\
	EEP_ADDR_D			,\
		}

/* Public Prototypes */
extern void app_Menu_init(void);
extern void app_Menu_Task(void);

#endif /* APPLICATION_APP_MENU_H_ */
