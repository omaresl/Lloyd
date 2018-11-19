/*
 * app_StepperMotor.h
 *
 *  Created on: 18 nov 2018
 *      Author: Admin
 */

/* Interfaces */
#include <Arduino.h>

/* Public Type definitions */

/* Public Macros */
#define APP_STEPPERMOTOR_CLK_DIR		false
#define APP_STEPPERMOTOR_CNTCLK_DIR		true

/* Public Variables */

/* Public Prototypes */
extern void app_StepperMotor_Init(void);
extern void app_StepperMotor_OneStep(unsigned char lub_dir);




