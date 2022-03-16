/*
 * lcd.c
 *
 *  Created on: Sep 5, 2021
 *      Author: HP
 */
#include "lcd.h"

/**************** Functions Definition **************************/

void LCD_SendCommand(u8 cmd){
	CLEAR_BIT(LCD_CTRL_PORT,RS);		//set RS=0 to choose command mode
	CLEAR_BIT(LCD_CTRL_PORT,RW);		//set RW=0 to choose write mode
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);			//set E=1 to enable LCD
	_delay_ms(1);
	LCD_DATA_PORT = cmd;				//send command through data pins
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);			//set E=0 to disable LCD
	_delay_ms(1);
}

void LCD_DisplayCharacter(u8 data){
	SET_BIT(LCD_CTRL_PORT,RS);			//set RS=1 to choose Data mode
	CLEAR_BIT(LCD_CTRL_PORT,RW);		//set RW=0 to choose write mode
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);			//set E=1 to enable LCD
	_delay_ms(1);
	LCD_DATA_PORT = data;				//send data through data pins
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);			//set E=0 to disable LCD
	_delay_ms(1);
}

void LCD_init(void){
	LCD_DATA_PORT_DIR = 0xFF; 							//set all data pins as o/p pins
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);	//set control pins as o/p pins
	LCD_SendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
	LCD_SendCommand(CURSOR_OFF);
	LCD_SendCommand(CLEAR_COMMAND);
}

void LCD_DisplayString(u8 *str){
	u8 i=0;
	while(str[i] != '\0'){
		LCD_DisplayCharacter(str[i]);
		i++;
	}
}

void LCD_GoToRowCol(u8 row,u8 col){
	u8 address;
	switch(row){
	case 0:
		address = col;
		break;
	case 1:
		address = col + 0x40;
		break;
	case 2:
		address = col + 0x10;
		break;
	case 3:
		address = col + 0x50;
		break;
	}
	LCD_SendCommand(SET_CURSOR_LOCATION | address);  	//set cursor location at the defined row&col
}

void LCD_ClearScreen(void){
	LCD_SendCommand(CLEAR_COMMAND);
}

void LCD_DisplayStringRowCol(u8 row,u8 col,u8 *str){
	LCD_GoToRowCol(row,col);
	LCD_DisplayString(str);
}

void LCD_IntToString (u32 value)
{
	/*
	int digits=0;
	if(value==0)
	{
		LCD_DisplayCharacter('0');
		return;
	}

	else
	{
		u8 Int_Str[32];
		for(u8 i=0;i<32;i++)
		{
			if(value==0)
				break;
			else
				digits++;
			Int_Str[i]='0' + (value%10);
			value=value/10;

		}
		for(int j=digits-1;j>=0;j--)
		{
			LCD_DisplayCharacter(Int_Str[j]);
		}
		return;
	}
*/
	u8 buff[16];
	itoa(value,buff,10);
	LCD_DisplayString(buff);
}
