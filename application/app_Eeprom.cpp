/*
 * app_Eeprom.cpp
 *
 *  Created on: 20 nov. 2018
 *      Author: Admin
 */


/* Interfaces */
#include "app_Eeprom.h"

/* Private Type definitions */

/* Private Macros */

/* Public Variables */

/* Private Variables */

/* Private Prototypes */


/* Functions */
/*************************************
 * Name: app_Eeprom_Init
 * Description: Eeprom Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Eeprom_Init(void)
{
	/* Read Eeprom values */
	if(EEPROM.read(EEP_ADDR_CAL) != 0x55u)
	{
		EEPROM.write(EEP_ADDR_CAL,0x55u);
		EEPROM.write(EEP_ADDR_FIXED_TEMP,EEP_DEF_FIXED_TEMP);
		EEPROM.write(EEP_ADDR_TEMP_MODE,EEP_DEF_TEMP_MODE);
		EEPROM.write(EEP_ADDR_SAMPLES,EEP_DEF_SAMPLES);
		EEPROM.write(EEP_ADDR_P,EEP_DEF_P);
		EEPROM.write(EEP_ADDR_I,EEP_DEF_I);
		EEPROM.write(EEP_ADDR_D,EEP_DEF_D);
	}

	EEPROM.get(EEP_ADDR_FIXED_TEMP,rul_DesiredTemperature);
	EEPROM.get(EEP_ADDR_TEMP_MODE,re_TempAddMode);
	EEPROM.get(EEP_ADDR_SAMPLES,rub_TempSamples);
	EEPROM.get(EEP_ADDR_P,rub_ConstP);
	EEPROM.get(EEP_ADDR_I,rub_ConstI);
	EEPROM.get(EEP_ADDR_D,rub_ConstD);
}
