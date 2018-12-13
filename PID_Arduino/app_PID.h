/*
 * app_PID.h
 *
 *  Created on: 17 nov 2018
 *      Author: Admin
 */

#ifndef APPLICATION_APP_PID_H_
#define APPLICATION_APP_PID_H_

/* Interfaces */
#include "app_Temperature.h"
#include "app_StepperMotor.h"
#include "app_Misc.h"

/* Public Macros */
#define APP_PID_N_PAST_ERRORS	10
#define APP_PID_MIN_COLD_VALID	10
#define APP_PID_MIN_HEAT_VALID	-10

/* External Variables */
extern float rub_ConstP;
extern float rub_ConstI;
extern float rub_ConstD;
extern float rf_Compansate;

/* Public Functions */
extern void app_PID_Init(void);
extern void app_PID_Task(void);

#endif /* APPLICATION_APP_PID_H_ */
