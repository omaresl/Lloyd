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
#define APP_STEPPERMOTOR_PUL_PIN	(32u)
#define APP_STEPPERMOTOR_DIR_PIN	(37u)
#endif

#define APP_STEPPERMOTOR_IDLESTATE		false
#define APP_STEPPERMOTOR_ACTIVESTATE	true

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
	digitalWrite(APP_STEPPERMOTOR_DIR_PIN,APP_STEPPERMOTOR_IDLESTATE);
	digitalWrite(APP_STEPPERMOTOR_EN_PIN,APP_STEPPERMOTOR_IDLESTATE);
	digitalWrite(APP_STEPPERMOTOR_PUL_PIN,APP_STEPPERMOTOR_IDLESTATE);
	pinMode(APP_STEPPERMOTOR_DIR_PIN,OUTPUT);
	pinMode(APP_STEPPERMOTOR_EN_PIN,OUTPUT);
	pinMode(APP_STEPPERMOTOR_PUL_PIN,OUTPUT);
}

/*************************************
 * Name: app_StepperMotor_Init
 * Description: Stepper Motor Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_OneStep(unsigned char lub_dir)
{
	digitalWrite(APP_STEPPERMOTOR_DIR_PIN,lub_dir);
	digitalWrite(APP_STEPPERMOTOR_EN_PIN,false);
	digitalWrite(APP_STEPPERMOTOR_PUL_PIN,APP_STEPPERMOTOR_IDLESTATE);
	delayMicroseconds(50);
	digitalWrite(APP_STEPPERMOTOR_PUL_PIN,APP_STEPPERMOTOR_ACTIVESTATE);
	delayMicroseconds(50);
	digitalWrite(APP_STEPPERMOTOR_EN_PIN,true);
}

