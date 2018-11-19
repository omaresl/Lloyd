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

/* Public Type definitions */

/* Public Macros */
#define APP_STEPPERMOTOR_CLK_DIR		true
#define APP_STEPPERMOTOR_CNTCLK_DIR		false

/* Public Variables */

/* Public Prototypes */
extern void app_StepperMotor_Init(void);
extern void app_StepperMotor_OneStep(unsigned char lub_dir);
extern void app_StepperMotor_GoHome(void);




