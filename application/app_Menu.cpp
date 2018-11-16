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

static T_BUTTONS re_LastButtonPressed;
static T_BUTTONS re_ButtonPressed;

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
	/* Clear button pressed */
	re_LastButtonPressed = BUTTON_NONE;
	re_ButtonPressed = BUTTON_NONE;
	/* Digit Selection Clear */
	rub_DigitSelected = 0u;
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
	LCD.setCursor((15u - rub_DigitSelected),1u);
	LCD.blink();

	/* Check if one button was pressed */
	if(BUTTON_NONE == re_LastButtonPressed)
	{
		/* Update Last Button Pressed */
		re_LastButtonPressed = re_ButtonPressed;

		/* Perform the corresponding action */
		switch(re_ButtonPressed)
		{
		case BUTTON_UP:
		{
			if(0u == rub_DigitSelected)
			{
				if(rub_DigitUni < 9u)
				{
					rub_DigitUni++;
				}
				else
				{
					rub_DigitUni = 0u;
				}
			}
			else if(1u == rub_DigitSelected)
			{
				if(rub_DigitDec < 9u)
				{
					rub_DigitDec++;
				}
				else
				{
					rub_DigitDec = 0u;
				}
			}
			else if(2u == rub_DigitSelected)
			{
				if(rub_DigitHund < 9u)
				{
					rub_DigitHund++;
				}
				else
				{
					rub_DigitHund = 0u;
				}
			}
			else
			{
				/* Invalid Selection */
				rub_DigitSelected = 0u; //Select units digit
			}

		}break;
		case BUTTON_DOWN:
		{

		}break;
		case BUTTON_RIGHT:
		{

		}break;
		case BUTTON_LEFT:
		{

		}break;
		case BUTTON_SELECT:
		{

		}break;
		default:
		{
			/* Do nothing - Invalid Button detection */
		}break;
		}
	}
	else
	{
		/* Button already pressed, wait for release */
	}


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
