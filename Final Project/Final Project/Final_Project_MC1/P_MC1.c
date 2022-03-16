/*
 * P_MC1.c
 *
 *  Created on: Sep 29, 2021
 *      Author: HP
 */
#include "Keypad.h"
#include "lcd.h"
#include "UTILS/common_macros.h"
#include "UTILS/Std_Types.h"
#include "UART.h"

#define FLAG 0x20
#define PASSWARD_SIZE 4
#define FULL_WAVE_STEPS 2

int main()
{
	LCD_init();
	USART_INIT();
	//Stepper Motor Pins
	DDRB |=0x0F;
	PORTB &= 0xF0;
	unsigned char motor_steps[FULL_WAVE_STEPS] = {3};

	//PassWord Variables
	int PASSWARD[PASSWARD_SIZE]= {1,2,3,4} , Correct_Pass=1 ,flag=0;
	int Entered_Passward[PASSWARD_SIZE];


	LCD_DisplayString("Enter Password:");

	while(1)
	{
		//checking for the password
		if(flag==0)
		{
			for(int i=0; i<PASSWARD_SIZE; i++)
			{
				Entered_Passward[i] = KeyPad_GetPressKey(3,4);
				LCD_DisplayStringRowCol(1,i,"*");
				_delay_ms(300);
			}
		}

		flag=1;
		if(flag == 1 )
		{
			for(int i=0; i<PASSWARD_SIZE; i++)
			{
				if(Entered_Passward[i] == PASSWARD[i])
				{
					Correct_Pass=1;
				}
				else
				{
					Correct_Pass=0;
					break;
				}
			}
			//in case password is wrong ask the user to enter it again
			if(Correct_Pass == 0)
			{
				LCD_ClearScreen();
				LCD_DisplayStringRowCol(0,0,"Wrong Password");
				LCD_DisplayStringRowCol(1,0,"Try Again");
				_delay_ms(1000);
				LCD_ClearScreen();
				LCD_DisplayString("Enter Password:");
				Correct_Pass = 1;
			}
			else if(Correct_Pass == 1)
			{
				//in case password is correct
				LCD_ClearScreen();
				LCD_DisplayString("Welcome Home");
				//open the door
				PORTB = (PORTB & 0xF0) | (motor_steps[0] & 0x0F);
				_delay_ms(2000);
				PORTB &= 0xF0;
				//giving signal to the other microcontroler to handle the orders inside home
				while(USART_ReceiveByte() != FLAG);
				USART_SendByte('1');
			}
		}
		flag=0;


	}



}
