/*
 * keypad.c
 *
 *  Created on: Sep 8, 2021
 *      Author: HP
 */
#include "keypad.h"
#include "lcd.h"

static u8 KeyPad_KeyNumber_4_4(u8 Button_Number);
static int KeyPad_KeyNumber_3_4(u8 Button_Number);



int KeyPad_GetPressKey(u8 col,u8 row)
{
	while(1)
	{
		if(col ==4)
		{
			for(col = 0 ; col < 4 ; col++)
					{
						KEYPAD_PORT_DIR = (0b00010000<<col);
						KEYPAD_PORT_OUT = (~(0b00010000<<col));

						for(row = 0 ; row < 4 ; row++)
						{
							if(!(KEYPAD_PORT_IN &(1<<row)))
							{
								return (KeyPad_KeyNumber_4_4((row*N_COL4)+col+1));
							}
						}
					}
		}
		else if(col==3)
		{
			for(col = 0 ; col < 3 ; col++)
					{
						KEYPAD_PORT_DIR = (0b00010000<<col);
						KEYPAD_PORT_OUT = (~(0b00010000<<col));

						for(row = 0 ; row < 4 ; row++)
						{
							if(!(KEYPAD_PORT_IN &(1<<row)))
							{
								return (KeyPad_KeyNumber_3_4((row*N_COL3)+col+1));
							}
						}
					}
		}


	}
}

static u8 KeyPad_KeyNumber_4_4(u8 Button_Number)
{
	switch(Button_Number)
	{
	case 1: return '7';
		break;
	case 2: return '8';
		break;
	case 3: return '9';
		break;
	case 4: return '/';
		break;
	case 5: return '4';
		break;
	case 6: return '5';
		break;
	case 7: return '6';
		break;
	case 8: return '*';
		break;
	case 9: return '1';
		break;
	case 10: return '2';
		break;
	case 11: return '3';
		break;
	case 12: return '-';
		break;
	case 13: return 'C';
		break;
	case 14: return '0';
		break;
	case 15: return '=';
		break;
	case 16: return '+';
		break;
	default:
		return Button_Number;

	}
}

static int KeyPad_KeyNumber_3_4(u8 Button_Number)
{
	switch(Button_Number)
	{
	case 1: return 1;
		break;
	case 2: return 2;
		break;
	case 3: return 3;
		break;
	case 4: return 4;
		break;
	case 5: return 5;
		break;
	case 6: return 6;
		break;
	case 7: return 7;
		break;
	case 8: return 8;
		break;
	case 9: return 9;
		break;
	case 10: return '*';
		break;
	case 11: return 0;
		break;
	case 12: return '#';
		break;
	default:
		return Button_Number;

	}
}


