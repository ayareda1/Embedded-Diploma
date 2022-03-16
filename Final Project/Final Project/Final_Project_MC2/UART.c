/*
 * UART.c
 *
 *  Created on: Sep 27, 2021
 *      Author: HP
 */
#include "UART.h"

#define USART_BAUDRATE 9600

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL)))-1)

void USART_INIT(void)
{
	/* Enable Double speed mode */

	UCSRA = (1<<U2X);

	/*
	 * Disable for RX complete interrupt
	 * Disable for TX complete interrupt
	 * Disable for UDR empty register interrupt
	 * Enable receiver (RXEN = 1)
	 * Enable Transmitter (TXEN = 1)
	 * RXB8 & TXB8 not used
	 */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*
	 * URSEL = 1 to select UCSRC register
	 * UMSEL = 0 for asynchronous
	 * UPM0:1 = 00 (disable parity)
	 * USBS = 0 for 1 stop bit
	 * UCSZ1:0 = 1 (8-bit data length)
	 * UCPOL = 0 (Used with synchronous mode only)
	 */

	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

	/* set value of UBRR reigster with defined baudrate (9600) */

	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;

}


void USART_SendByte(u8 data)
{

	while (BIT_IS_CLEAR(UCSRA,UDRE)); // Polling until UDR register is empty and ready to take data

	UDR = data; // set data to UDR register

	/****************** Another method **************/

	/*UDR = data;

	while (BIT_IS_CLEAR(UCSRA,TXC));

	SET_BIT(UCSRA,TXC);*/

}

u8 USART_ReceiveByte(void)
{
	while (BIT_IS_CLEAR(UCSRA,RXC)); // Polling until UDR register is full with data

	return UDR; // return the data from UDR register
}

void USART_SendString(const u8 *str)
{
	u8 i = 0;

	while (str[i] != '\0')
	{
		USART_SendByte(str[i]);
		i++;
	}
}

void USART_RecieveString(u8 *str)
{
	u8 i = 0;
	str[i] = USART_ReceiveByte();
	while(str[i] != '#')
	{
		i++;
		str[i] = USART_ReceiveByte();
	}
	str[i] = '\0';
}


