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
unsigned int rul_LimitPosition;

/* Private Variables */
unsigned int rul_MotorPosition;

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
#ifdef CALIBRATION
	while(true)
	{
		app_StepperMotor_GoHome();
		app_StepperMotor_GoLimit();
	}
#else
	/* Print Message */
	LCD.setCursor(0,1);
	LCD.print("Going Home");
	app_StepperMotor_GoHome();
	app_StepperMotor_GoLimit();
	/* Print Message */
	LCD.setCursor(0,1);
	LCD.print("Going Home");
	app_StepperMotor_GoHome();
#endif
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
		delayMicroseconds(100);
		digitalWrite(APP_STEPPERMOTOR_PUL_PIN,LOW);
		delayMicroseconds(100);
	}
	/* Update Position */
	if(APP_STEPPERMOTOR_CLK_DIR == lub_dir)
	{
		if(rul_MotorPosition > 0u)
		{
			if(IS_VALVE_FULLY_CLOSED)
			{
				rul_MotorPosition = 0u;
			}
			else
			{
				rul_MotorPosition--;
			}
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{
		if(rul_MotorPosition < 2000u)
		{
			if(IS_VALVE_FULLY_OPEN)
			{
				/* Stop Counting */
			}
			else
			{
				rul_MotorPosition++;
			}
		}
		else
		{
			/* Do Nothing */
		}
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
	/* Close valve until Home swithc is activated */
	while(!IS_VALVE_FULLY_CLOSED)
	{
		/* Close valve one step */
		app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
	}
	rul_MotorPosition = 0u;
}

/*************************************
 * Name: app_StepperMotor_GoLimit
 * Description: Stepper Motor Module Go Limit Function
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_GoLimit(void)
{
	unsigned int luw_StepCounter;
	/* Print Message */
	LCD.setCursor(0,1);
	LCD.print("Calibrating     ");

	luw_StepCounter = 0u;
	/* Close valve until Home swithc is activated */
	while(!IS_VALVE_FULLY_OPEN)
	{
		luw_StepCounter++;
		/* Close valve one step */
		app_StepperMotor_OneStep(APP_STEPPERMOTOR_CNTCLK_DIR);
	}

	rul_LimitPosition = luw_StepCounter;
	EEPROM.put(EEP_ADDR_LIMIT_POS,rul_LimitPosition);
}

/*************************************
 * Name: app_StepperMotor_GoToPosition
 * Description: Stepper Motor Module Go To Position Function
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_StepperMotor_GoToPosition(float lul_Pos)
{
	/* Go Backward */
	if(lul_Pos < rul_MotorPosition)
	{
		while(lul_Pos < rul_MotorPosition &&
				(!IS_VALVE_FULLY_CLOSED))
		{
			app_StepperMotor_OneStep(APP_STEPPERMOTOR_CLK_DIR);
		}
	}
	else
	{//Greater or equal
		while((lul_Pos > rul_MotorPosition) &&
				(!IS_VALVE_FULLY_OPEN))
		{
			app_StepperMotor_OneStep(APP_STEPPERMOTOR_CNTCLK_DIR);
		}
	}
}
