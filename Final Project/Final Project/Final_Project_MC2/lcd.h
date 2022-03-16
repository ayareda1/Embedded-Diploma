/*
 * lcd.h
 *
 *  Created on: Sep 5, 2021
 *      Author: HP
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "UTILS/common_macros.h"
#include "UTILS/Std_Types.h"
#include <avr/io.h>
#include <util/delay.h>

             /**************** PreProcessor Macros **************************/
/* LCD DATA PINS */
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC


/* LCD CONTROL PINS */
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD


#define RS PD3
#define RW PD4
#define E PD2

/* LCD COMMANDS */
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

             /**************** Functions Prototypes **************************/
void LCD_init(void); 						//function to initialize LCD
void LCD_SendCommand(u8 cmd); 				//function to send any specific command
void LCD_DisplayCharacter(u8 data); 		//function to display character
void LCD_DisplayString(u8 *str); 			//function to display strings
void LCD_GoToRowCol(u8 row,u8 col);			//function to decide specific column and row in LCD
void LCD_DisplayStringRowCol(u8 row,u8 col,u8 *str); //function to display strings in specific row and column
void LCD_IntToString (u32 value); 			//function to display integers on LCD
void LCD_ClearScreen(void);					//function to clear LCD
#endif /* HAL_LCD_LCD_H_ */
