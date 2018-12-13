/*
 * app_Eeprom.h
 *
 *  Created on: 20 nov. 2018
 *      Author: Admin
 */

#ifndef APPLICATION_APP_EEPROM_H_
#define APPLICATION_APP_EEPROM_H_

/* Interfaces */
#include <Arduino.h>
#include <EEPROM.h>
#include "app_Temperature.h"
#include "app_PID.h"
#include "app_StepperMotor.h"

/* Public Type definitions */

/* Public Macros */
/* Default Values */
#define EEP_DEF_FIXED_TEMP		(25.0f)
#define EEP_DEF_TEMP_MODE		(ADD_COLD)
#define EEP_DEF_SAMPLES			(10.0f)
#define EEP_DEF_P				(10.0f)
#define EEP_DEF_I				(00.0f)
#define EEP_DEF_D				(00.0f)
#define EEP_DEF_COMP			(00.0f)

/* Parameter Address */
#define EEP_ADDR_CAL 			(0u)
#define EEP_ADDR_FIXED_TEMP		(EEP_ADDR_CAL + sizeof(unsigned char))
#define EEP_ADDR_TEMP_MODE		(EEP_ADDR_FIXED_TEMP + sizeof(float))
#define EEP_ADDR_SAMPLES		(EEP_ADDR_TEMP_MODE + sizeof(float))
#define EEP_ADDR_P				(EEP_ADDR_SAMPLES + sizeof(float))
#define EEP_ADDR_I				(EEP_ADDR_P + sizeof(float))
#define EEP_ADDR_D				(EEP_ADDR_I + sizeof(float))
#define EEP_ADDR_LIMIT_POS		(EEP_ADDR_D + sizeof(float))
#define EEP_ADDR_COMPENSATE		(EEP_ADDR_LIMIT_POS + sizeof(float))

/* Public Variables */

/* Public Prototypes */
extern void app_Eeprom_Init(void);
extern unsigned char app_Eeprom_IsCalibrated(void);


#endif /* APPLICATION_APP_EEPROM_H_ */
