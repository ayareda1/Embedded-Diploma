/*
 * UART.h
 *
 *  Created on: Sep 27, 2021
 *      Author: HP
 */

#ifndef UART_H_
#define UART_H_

#include "UTILS/common_macros.h"
#include "UTILS/Std_Types.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr/delay.h"

// UART Driver Baud Rate
#define USART_BAUDRATE 9600


/***************** Functions Prototypes *****************/
void USART_INIT(void); 							// function to initialize USART
void USART_SendByte(u8 data); 					// function to send data byte
u8 USART_ReceiveByte(void); 					//function to receive byte
void USART_SendString(const u8 *str); 			// function to send string
void USART_RecieveString(u8 *str); 			// function to receive string



#endif /* UART_H_ */
