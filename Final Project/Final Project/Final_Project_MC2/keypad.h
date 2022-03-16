/*
 * keypad.h
 *
 *  Created on: Sep 8, 2021
 *      Author: HP
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "UTILS/common_macros.h"
#include "UTILS/Std_Types.h"
#include<avr/io.h>
#include<util/delay.h>

/****************** PreProcessor Macros **************************/
 /*KeyPad Port Configiration*/
#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_OUT PORTA


#define N_COL3 3
#define N_COL4 4

/****************** Functions ProtoTypes **************************/
int KeyPad_GetPressKey(u8 col,u8 row);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
