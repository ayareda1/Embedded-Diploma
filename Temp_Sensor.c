/*
 * Temp_Sensor.c
 *
 *  Created on: Sep 19, 2021
 *      Author: HP
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Std_Types.h"
#include "common_macros.h"
#include <avr/interrupt.h>

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
	DDRC = 0x0F;
	PORTC = 0x00;
	DDRB = 0x01;
	PORTB = 0x00;
	ADC_INIT();
	int temp=0;

	while(1)
	{

		temp = (adc_read(0)/2.046);
		if(temp <=20)
		{
			PORTB &= ~(1<<0);
			PORTC = 0x00;
			PORTC |= (1<<0);
		}
		else if(temp>20 && temp <40)
		{
			PORTB &= ~(1<<0);
			PORTC = 0x00;
			PORTC |=(1<<1);
		}
		else if(temp>=40)
		{
			PORTC = 0x00;
			PORTC |= (1<<2);
			PORTB |= (1<<0);
		}
	}
}
