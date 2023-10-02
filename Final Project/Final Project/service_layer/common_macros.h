/*
 * common_macros.h
 *
 *  Created on: 1 Sep 2016
 *      Author: SAMEH
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* shift right the register value with specific number of shifts */
#define SHIFT_RIGHT(REG,num) ( REG= (REG>>num) )
/* shift left the register value with specific number of shifts */
#define SHIFT_LEFT(REG,num) ( REG= (REG>>num) )

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT)>>BIT )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !((REG & (1<<BIT))>>BIT) )



#endif /* COMMON_MACROS_H_ */
