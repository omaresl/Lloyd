/*
 * app_Menu.c
 *
 *  Created on: 15/11/2018
 *      Author: Omar Sevilla
 */


/* Interfaces */
#include "app_Menu.h"

/* Variables */
unsigned long *	raul_Items[APP_MENU_N_ITEMS] = APP_MENU_ITEMS;
const char raub_ItemText[APP_MENU_N_ITEMS][17u] = APP_MENU_ITEMSTEXT;
unsigned char rub_ItemSelected = 0u;
unsigned char rub_DigitSelected;
unsigned char rub_DigitHund,rub_DigitDec,rub_DigitUni;

/* Private Prototypes */
static void app_Menu_ToDigits(unsigned long lul_Value);

/* Function Definitions */

/*************************************
 * Name: app_Menu_Init
 * Description: Menu Module Init
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Menu_init(void)
{
	/* Item Index clear*/
	rub_ItemSelected = 0u;
}

/*************************************
 * Name: app_Menu_Task
 * Description: Menu Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Menu_Task(void)
{
	/* Fill digits */
	app_Menu_ToDigits(*raul_Items[rub_ItemSelected]);

	/* Set Cursor */
	LCD.setCursor(0u,1u);
	/* Print text for selected item */
	LCD.println(raub_ItemText[rub_ItemSelected]);
	/* Set Cursor */
	LCD.setCursor(14u,1u);
	/* Print digits */
	LCD.print(rub_DigitHund);
	LCD.print(rub_DigitDec);
	LCD.print(rub_DigitUni);
	/* Cursor Blink in digit selected */
	LCD.setCursor(15u,1u);
	LCD.blink();
}

/*************************************
 * Name: app_Menu_ToDigits
 * Description: Convert to independent digits
 * Parameters: N/A
 * Return: N/A
 *************************************/
static void app_Menu_ToDigits(unsigned long lul_Value)
{
	rub_DigitHund = lul_Value / 100u;
	lul_Value -= (rub_DigitHund*100u);
	rub_DigitDec = lul_Value / 10u;
	lul_Value -= (rub_DigitHund*10u);
	rub_DigitUni = lul_Value;
}
