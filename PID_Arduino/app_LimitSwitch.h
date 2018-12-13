/*
 * app_LimitSwitch.h
 *
 *  Created on: 18 nov 2018
 *      Author: Admin
 */
#ifndef APPLICATION_APP_LIMITSWITCH_H_
#define APPLICATION_APP_LIMITSWITCH_H_

/* Interfaces */
#include <Arduino.h>
#include "app_LCD.h"
#include "app_Display.h"

/* Public Type definitions */
typedef enum
{
	LIMITSTATE_INRANGE,
	LIMITSTATE_LIMITS
}T_LIMITSTATE;

/* Public Macros */
#ifdef OmarBoard
#define APP_LIMITSWITCH_START_PIN	(3u)
#define APP_LIMITSWITCH_END_PIN		(4u)
#else
#define APP_LIMITSWITCH_START_PIN	(40u)
#define APP_LIMITSWITCH_END_PIN		(41u)
#endif

#define IS_VALVE_FULLY_CLOSED	(true != digitalRead(APP_LIMITSWITCH_START_PIN))
#define IS_VALVE_FULLY_OPEN		(true != digitalRead(APP_LIMITSWITCH_END_PIN))

/* Public Variables */
extern T_LIMITSTATE re_LimitState;

/* Public Prototypes */
extern void app_LimitSwitch_Init(void);
extern void app_LimitSwitch_Task(void);

#endif



