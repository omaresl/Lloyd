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
const unsigned long raul_MaxLimit[APP_MENU_N_ITEMS] = APP_MENU_APP_MAXLIMITS;
const unsigned long raul_MinLimit[APP_MENU_N_ITEMS] = APP_MENU_APP_MINLIMITS;
unsigned char rub_ItemSelected = 0u;
unsigned char rub_DigitSelected;
unsigned char rub_DigitHund,rub_DigitDec,rub_DigitUni;

static T_BUTTONS re_LastButtonPressed;
static T_BUTTONS re_ButtonPressed;
static unsigned char rub_DisplayFlag;

static unsigned long rul_MenuTaskLastSnapTime;

/* Private Prototypes */
static void app_Menu_ToDigits(unsigned long lul_Value);
static void app_Menu_ToData(void);
static void app_Menu_CheckLimits(void);

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
	/* Prepare Display Flag */
	rub_DisplayFlag = true;
	/* Init Time counter */
	rul_MenuTaskLastSnapTime = millis();
}

/*************************************
 * Name: app_Menu_Task
 * Description: Menu Module Task
 * Parameters: N/A
 * Return: N/A
 *************************************/
void app_Menu_Task(void)
{
	if(true == rub_DisplayFlag)
	{
		/* Fill digits */
		app_Menu_ToDigits(*raul_Items[rub_ItemSelected]);

		/* Set Cursor */
		LCD.setCursor(0u,1u);

		if(1u == rub_ItemSelected)
		{
			LCD.noBlink();
			LCD.print("Temp Add: ");
			if(ADD_COLD == *raul_Items[rub_ItemSelected])
			{
				LCD.print("COLD  ");
			}
			else
			{
				LCD.print("HEAT  ");
			}
		}
		else
		{
			/* Print text for selected item */
			LCD.println(raub_ItemText[rub_ItemSelected]);
			/* Set Cursor */
			LCD.setCursor(13u,1u);

			/* Print digits */
			LCD.print(rub_DigitHund);
			LCD.print(rub_DigitDec);
			LCD.print(rub_DigitUni);

			/* Cursor Blink in digit selected */
			LCD.setCursor((15u - rub_DigitSelected),1u);
			LCD.blink();
		}

		/* Clear Flag */
		rub_DisplayFlag = false;
	}
	else
	{
		/* Do Not Display */
	}

	//	/* Check if a period of 10 ms has been passed */
	//	if((millis() - rul_MenuTaskLastSnapTime) > 10u)
	//	{
	//		/* Update time snap */
	//		rul_MenuTaskLastSnapTime = millis();

	/* Update Buttons */
	re_ButtonPressed = app_Buttons_GetButtonPressed();
#ifdef PRINT_BUTTONS
	if((re_LastButtonPressed != re_ButtonPressed))
	{
		LCD.setCursor(0,0);
		app_Buttons_PrintButton(re_ButtonPressed);
	}
	else
	{
		/* Do Nothing */
	}
#endif

	/* Check if one button was pressed */
	if((BUTTON_NONE == re_LastButtonPressed) &&
			(re_LastButtonPressed != re_ButtonPressed))
	{
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
			if(0u == rub_DigitSelected)
			{
				if(rub_DigitUni > 0u)
				{
					rub_DigitUni--;
				}
				else
				{
					rub_DigitUni = 9u;
				}
			}
			else if(1u == rub_DigitSelected)
			{
				if(rub_DigitDec > 0u)
				{
					rub_DigitDec--;
				}
				else
				{
					rub_DigitDec = 9u;
				}
			}
			else if(2u == rub_DigitSelected)
			{
				if(rub_DigitHund > 0u)
				{
					rub_DigitHund--;
				}
				else
				{
					rub_DigitHund = 9u;
				}
			}
			else
			{
				/* Invalid Selection */
				rub_DigitSelected = 0u; //Select units digit
			}
		}break;
		case BUTTON_RIGHT:
		{
			if(rub_DigitSelected > 0u)
			{
				rub_DigitSelected--;
			}
			else
			{
				rub_DigitSelected = 2u;
			}
		}break;
		case BUTTON_LEFT:
		{
			if(rub_DigitSelected < 2u)
			{
				rub_DigitSelected++;
			}
			else
			{
				rub_DigitSelected = 0u;
			}
		}break;
		case BUTTON_SELECT:
		{
			if(rub_ItemSelected < (APP_MENU_N_ITEMS - 1u))
			{
				rub_ItemSelected++;
			}
			else
			{
				rub_ItemSelected = 0u;
			}
		}break;
		default:
		{
			/* Do nothing - Invalid Button detection */
		}break;
		}

		/* Save New Data Config */
		app_Menu_ToData();

		/* Refresh Display */
		rub_DisplayFlag = true;

	}
	else
	{
		/* Button already pressed, wait for release */
	}

	/* Update Last Button Pressed */
	re_LastButtonPressed = re_ButtonPressed;
	//	}
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
	lul_Value -= (rub_DigitDec*10u);
	rub_DigitUni = lul_Value;
}

/*************************************
 * Name: app_Menu_ToData
 * Description: Convert to ditits to data
 * Parameters: N/A
 * Return: N/A
 *************************************/
static void app_Menu_ToData(void)
{
	*raul_Items[rub_ItemSelected] = 	(rub_DigitHund*100u) + (rub_DigitDec*10u) + (rub_DigitUni);
	app_Menu_CheckLimits();
}

/*************************************
 * Name: app_Menu_CheckLimits
 * Description: Check limits of each variable type;
 * Parameters: N/A
 * Return: N/A
 *************************************/
static void app_Menu_CheckLimits(void)
{
	if(*raul_Items[rub_ItemSelected] > raul_MaxLimit[rub_ItemSelected])
	{
		*raul_Items[rub_ItemSelected] = raul_MaxLimit[rub_ItemSelected];
	}
	else if(*raul_Items[rub_ItemSelected] < raul_MinLimit[rub_ItemSelected])
	{
		*raul_Items[rub_ItemSelected] = raul_MinLimit[rub_ItemSelected];
	}
	else
	{
		/* Variable in Range */
	}
}
