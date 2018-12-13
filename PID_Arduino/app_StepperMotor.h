/*
 * app_StepperMotor.h
 *
 *  Created on: 18 nov 2018
 *      Author: Admin
 */

/* Interfaces */
#include <Arduino.h>
#include "app_LimitSwitch.h"
#include "app_LCD.h"
#include "app_Eeprom.h"

/* Public Type definitions */

/* Public Macros */
#define APP_STEPPERMOTOR_CLK_DIR		false
#define APP_STEPPERMOTOR_CNTCLK_DIR		true

/* Public Variables */
extern unsigned int rul_LimitPosition;

/* Public Prototypes */
extern void app_StepperMotor_Init(void);
extern void app_StepperMotor_OneStep(unsigned char lub_dir);
extern void app_StepperMotor_GoHome(void);
extern void app_StepperMotor_GoLimit(void);
extern void app_StepperMotor_GoToPosition(float lul_Pos);




