/*
 * app_StepperMotor.cpp
 *
 *  Created on: 18 nov 2018
 *      Author: Admin
 */


/* Interfaces */
#include "app_StepperMotor.h"

/* Private Type definitions */

/* Private Macros */
#ifdef OmarBoard
#define APP_STEPPERMOTOR_EN_PIN		(3u)
#define APP_STEPPERMOTOR_PUL_PIN	(4u)
#define APP_STEPPERMOTOR_DIR_PIN	(5u)
#else
#define APP_STEPPERMOTOR_EN_PIN		(38u)
#define APP_STEPPERMOTOR_PUL_PIN	(37u)
#define APP_STEPPERMOTOR_DIR_PIN	(39u)
#endif

/* Public Variables */

/* Private Variables */

/* Private Prototypes */

/* Functions */

/*************************************
 * Name: app_StepperMotor_Init
 * Description: Stepper Motor Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_Init(void)
{
	/* Set pin configuration */
	pinMode(APP_STEPPERMOTOR_EN_PIN,OUTPUT);
	pinMode(APP_STEPPERMOTOR_DIR_PIN,OUTPUT);
	pinMode(APP_STEPPERMOTOR_PUL_PIN,OUTPUT);

	app_StepperMotor_GoHome();
}

/*************************************
 * Name: app_StepperMotor_Init
 * Description: Stepper Motor Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_OneStep(unsigned char lub_dir)
{
	unsigned int lub_i;

	for(lub_i = 0; lub_i < 40u; lub_i++)
	{
		digitalWrite(APP_STEPPERMOTOR_DIR_PIN,lub_dir);
		digitalWrite(APP_STEPPERMOTOR_EN_PIN,HIGH);
		digitalWrite(APP_STEPPERMOTOR_PUL_PIN,HIGH);
		delayMicroseconds(50);
		digitalWrite(APP_STEPPERMOTOR_PUL_PIN,LOW);
		delayMicroseconds(50);
	}
}

/*************************************
 * Name: app_StepperMotor_GoHome
 * Description: Stepper Motor Module Go Home Function
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_GoHome(void)
{
	/* Print Message */
	LCD.setCursor(0,1);
	LCD.print("Going Home");

	/* Close valve until Home swithc is activated */
	while(!IS_VALVE_FULLY_CLOSED)
	{
		/* Close valve one step */
		app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
	}
}
