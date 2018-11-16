/*
 * app_LCD.cpp
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */

#include "app_LCD.h"

/* Private Macros */
#define APP_LCD_N_ROWS		(2u)
#define APP_LCD_N_COLUMNS	(16u)

/* Private Variables */
LiquidCrystal LCD(APP_LCD_RS_PIN,
		APP_LCD_EN_PIN,
		APP_LCD_D4_PIN,
		APP_LCD_D5_PIN,
		APP_LCD_D6_PIN,
		APP_LCD_D7_PIN);           // select the pins used on the LCD panel

/* Function Definitions */

/*************************************
 * Name: app_LCD_Init
 * Description: LCD Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_LCD_Init(void)
{
	/* LCD Initialization */
	LCD.begin(APP_LCD_N_COLUMNS,APP_LCD_N_ROWS);
	/* Set cursor to home */
	LCD.setCursor(0u,0u);
	/* Print first message */
	LCD.print("PID Controller");
}
