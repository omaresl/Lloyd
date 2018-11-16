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

/* Typedefs */
typedef enum
{
	BUTTON_NONE,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_SELECT
}T_BUTTONS;

/* External Functions */
extern void app_Buttons_init(void);
extern T_BUTTONS app_Buttons_GetButtonPressed(void);

#endif /* APPLICATION_APP_BUTTONS_H_ */
