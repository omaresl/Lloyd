/*
 * app_Buttons.h
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

#ifndef APPLICATION_APP_BUTTONS_H_
#define APPLICATION_APP_BUTTONS_H_

/* Interfaces */
#include <Arduino.h>
#include "app_LCD.h"

/* Typedefs */
typedef enum
{
	BUTTON_NONE,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_SELECT,
	BUTTON_INVALID
}T_BUTTONS;

/* Macros */
#define APP_BUTTONS_DEBOUNCE	(2u)

/* External Functions */
extern void app_Buttons_init(void);
extern T_BUTTONS app_Buttons_GetButtonPressed(void);
extern void app_Buttons_PrintButton(T_BUTTONS le_ButtonPressed);

#endif /* APPLICATION_APP_BUTTONS_H_ */
