/*
 * keypad.h
 *
 * Created: 02/12/2022 10:39:13
 *  Author: Ayaya
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/DIO/DIO.h"

//#define KEYPAD4x3

#define KEYPAD_ROW_PORT 'c'
#define KEYPAD_COLUMN_PORT 'd'

#define NO_ROWS 4

#ifdef KEYPAD4x3
#define NO_COLS 3
#else
#define NO_COLS 4
#endif
// Pins of rows
#define ROW_1 4
#define ROW_2 5
#define ROW_3 6
#define ROW_4 7
// Pins of columns
#define COL_1 4
#define COL_2 5
#define COL_3 6
#define COL_4 7

#ifdef KEYPAD4x3

#define KEYS_VALUES {{'1','2','3'},\
					 {'4','5','6'},\
					 {'7','8','9'},\
					 {'*','0','#'}}
#else // KEYPAD4x4
#define KEYS_VALUES {{'7','8','9','/'},\
					 {'4','5','6','*'},\
					 {'1','2','3','-'},\
					 {'c','0','=','+'}}
#endif

// Initialization function
void KPD_init(void);

// Function to get the pressed key
uint8_t KPD_get_key(void);


#endif /* KEYPAD_H_ */