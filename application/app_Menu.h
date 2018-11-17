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
	99u,\
	ADD_HEAT,\
	100u,\
	10u,\
	10u,\
	10u,\
		}

#define APP_MENU_APP_MINLIMITS\
		{\
	0u,\
	ADD_COLD,\
	10u,\
	0u,\
	0u,\
	0u,\
		}

/* Public Prototypes */
extern void app_Menu_init(void);
extern void app_Menu_Task(void);

#endif /* APPLICATION_APP_MENU_H_ */
