/*
 * app_Display.h
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

#ifndef APPLICATION_APP_DISPLAY_H_
#define APPLICATION_APP_DISPLAY_H_

#include "app_LCD.h"
#include "app_Menu.h"
#include "app_Temperature.h"

/* Typedefs */
typedef enum
{
	DISPLAY_NORMAL,
	DISPLAY_MANUAL,
	DISPLAY_CONFIG
}T_DISPLAY;

extern T_DISPLAY re_DisplayMode;

/* Public functions */
extern void app_Display_Init(void);
extern void app_Display_Task(void);
extern void app_Display_Mode(T_DISPLAY le_Mode);


#endif /* APPLICATION_APP_DISPLAY_H_ */
