/*
 * app_LCD.h
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

#ifndef APPLICATION_APP_LCD_H_
#define APPLICATION_APP_LCD_H_

#include <Arduino.h>
//#define OmarBoard
#ifdef OmarBoard
#include <LiquidCrystal_I2C.h>
#else
#include <LiquidCrystal.h>
#endif
#include "app_LimitSwitch.h"

/* Public Macros */
//Pin Definitions
#define APP_LCD_RS_PIN	(8u) //Pin Arduino D8
#define APP_LCD_EN_PIN	(9u) //Pin Arduino D9
#define APP_LCD_D4_PIN	(4u) //Pin Arduino D4
#define APP_LCD_D5_PIN	(5u) //Pin Arduino D5
#define APP_LCD_D6_PIN	(6u) //Pin Arduino D6
#define APP_LCD_D7_PIN	(7u) //Pin Arduino D7

/* Public Variables */
#ifdef OmarBoard
extern LiquidCrystal_I2C LCD;
#else
extern LiquidCrystal LCD;
#endif

/* External Prototypes */
extern void app_LCD_Init(void);

#endif /* APPLICATION_APP_LCD_H_ */
