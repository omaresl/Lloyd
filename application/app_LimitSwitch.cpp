/*
 * app_LimitSwitch.cpp
 *
 *  Created on: 18 nov 2018
 *      Author: Admin
 */

/* Interfaces */
#include "app_LimitSwitch.h"

/* Private Type definitions */

/* Private Macros */
#ifdef OmarBoard
#define APP_LIMITSWITCH_START_PIN	(3u)
#define APP_LIMITSWITCH_END_PIN		(4u)
#else
#define APP_LIMITSWITCH_START_PIN	(39u)
#define APP_LIMITSWITCH_END_PIN		(40u)
#endif

/* Public Variables */
T_LIMITSTATE re_LimitState;

/* Private Variables */

/* Private Prototypes */

/* Functions */

/*************************************
 * Name: app_LimitSwitch_Init
 * Description: Limit Switch Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_LimitSwitch_Init(void)
{
	/* Set pin as output */
	pinMode(APP_LIMITSWITCH_START_PIN,INPUT);
	pinMode(APP_LIMITSWITCH_END_PIN,INPUT);

	/* Initialize value as In Range */
	re_LimitState = LIMITSTATE_INRANGE;
	app_LimitSwitch_Task(); //Check limit state
}

/*************************************
 * Name: app_LimitSwitch_Task
 * Description: Limit Switch Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_LimitSwitch_Task(void)
{

	if(IS_VALVE_FULLY_CLOSED)
	{
		/* Set Limit State */
		re_LimitState = LIMITSTATE_LIMITS;
		if(DISPLAY_NORMAL == re_DisplayMode)
		{
			/* Print Limit State in LCD */
			LCD.setCursor(0u,1u);
			LCD.print("Full Closed     ");
		}
	}
	else if(IS_VALVE_FULLY_OPEN)
	{
		/* Set Limit State */
		re_LimitState = LIMITSTATE_LIMITS;

		if(DISPLAY_NORMAL == re_DisplayMode)
		{
			/* Print Limit State in LCD */
			LCD.setCursor(0u,1u);
			LCD.print("Full Open       ");
		}
	}
	else
	{
		/* Set Limit State as in Range */
		re_LimitState = LIMITSTATE_INRANGE;
	}
}
