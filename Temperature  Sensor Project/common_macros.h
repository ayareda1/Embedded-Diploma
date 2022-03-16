/*
 * common_macros.h
 *
 *  Created on: Sep 5, 2021
 *      Author: HP
 */

#ifndef UTILS_COMMON_MACROS_H_
#define UTILS_COMMON_MACROS_H_

#define SET_BIT(REG_NAME,BIT_NO) (REG_NAME |= (1<<BIT_NO) )
#define CLEAR_BIT(REG_NAME,BIT_NO) (REG_NAME &= (~(1<<BIT_NO)))
#define TOGGLE_BIT(REG_NAME,BIT_NO) (REG_NAME ^= (1<<BIT_NO))
#define BIT_IS_SET(REG_NAME,BIT_NO) (REG_NAME & (1<<BIT_NO))
#define BIT_IS_CLEAR(REG_NAME,BIT_NO) (!(REG_NAME & (1<<BIT_NO)))


#endif /* UTILS_COMMON_MACROS_H_ */
