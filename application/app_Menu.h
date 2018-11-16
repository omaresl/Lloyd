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

/* Public Macros */
#define APP_MENU_N_ITEMS	(1u)
#define APP_MENU_ITEMS	\
		{\
			&rul_DesiredTemperature\
		}

#define APP_MENU_ITEMSTEXT	\
		{\
			{"Desired Temp:   "},\
		}

/* Public Prototypes */
extern void app_Menu_init(void);
extern void app_Menu_Task(void);

#endif /* APPLICATION_APP_MENU_H_ */
