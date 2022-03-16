/*
 * P_MC2.c
 *
 *  Created on: Sep 30, 2021
 *      Author: HP
 */

#include "lcd.h"
#include "keypad.h"
#include "UART.h"
#define PASSWARD_SIZE 4
#define FLAG 0x20

void ADC_INIT(void)
{
	ADMUX = 0;
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

u16 adc_read(u8 channel)
{
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07); 		// set your passed channel
	SET_BIT(ADCSRA,ADSC); 							// start ADC conversion
	while (BIT_IS_CLEAR(ADCSRA,ADIF)); 				// Polling until conversion is finished (ADIF = 1)
	SET_BIT(ADCSRA,ADIF); 							// Clear ADIF by setting ADIF bit
	return ADC;
}

int main()
{
	LCD_init();
	USART_INIT();
	ADC_INIT();
	// Fan Pins Configurations
	DDRD |= (1<<6);
	DDRD |= (1<<7);
	PORTD &= ~(1<<6);
	PORTD &= ~(1<<7);

	//Temperature variable
	int temp=0;

	//Security Variables
	int Correct_Pass_AL=1 ,flag2=0 ,ALARM_PASSWARD[PASSWARD_SIZE]= {5,6,7,8} ,Entered_Passward_ALARM[PASSWARD_SIZE] ;

	//Buzzer and alarm Led
	DDRB = 0x1F;
	PORTB = 0x00;

	//Variable to receive the signal from the first microcontrollar at
	u8 HOME_ON =0;

	//receive signal from the first microcontrollar
	USART_SendByte(FLAG);
	HOME_ON = USART_ReceiveByte();

	while(1)
	{
		//when MC2 receives a signal from MC1
		if(HOME_ON == '1')
		{
			//turn on home lights
			PORTB |=(1<<0);
			//calculate the temperature to control the fan
			temp = (adc_read(7)/2.046);
			if(temp>=40)
			{
				PORTD &= (~(1<<7));
				PORTD |= (1<<6);
			}
			else if(temp<40)
			{
				PORTD &= (~(1<<7));
				PORTD &= (~(1<<6));
			}

			//Security Part
			if(flag2==0)
			{
				LCD_ClearScreen();
				LCD_DisplayString("Enter Password:");
				for(int i=0; i<PASSWARD_SIZE; i++)
				{
					Entered_Passward_ALARM[i] = KeyPad_GetPressKey(3,4);
					LCD_DisplayStringRowCol(1,i,"*");
					_delay_ms(300);
				}
				flag2=1;
			}

			if(flag2 == 1 )
			{
				for(int i=0; i<PASSWARD_SIZE; i++)
				{
					if(Entered_Passward_ALARM[i] == ALARM_PASSWARD[i])
					{
						Correct_Pass_AL=1;
					}
					else
					{
						Correct_Pass_AL=0;
						break;
					}
				}

				if(Correct_Pass_AL == 0)
				{
					LCD_ClearScreen();
					LCD_DisplayStringRowCol(0,0,"Wrong Password");
					_delay_ms(1000);
					LCD_DisplayStringRowCol(0,0,"Security Mode ON");
					_delay_ms(1000);
					LCD_ClearScreen();
					LCD_DisplayString("Enter Password:");
					Correct_Pass_AL = 1;
					//turn on Buzzer and alarm LED
					PORTB = 0x1F;
					flag2=0;
				}
				else if(Correct_Pass_AL == 1)
				{
					PORTB = 0x01;
					LCD_ClearScreen();
					LCD_DisplayString("Secured");
					flag2 = 3;

				}
			}


		}
	}


}
