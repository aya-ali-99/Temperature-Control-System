/*
 * keypad.c
 *
 * Created: 02/12/2022 10:39:01
 *  Author: Ayaya
 */ 


#include "keypad.h"

// Keypad keys
static const uint8_t keypad_keys[NO_ROWS][NO_COLS] = KEYS_VALUES;

// Array of pins of rows & columns
#ifdef KEYPAD4x3
static const uint8_t rows[NO_ROWS] = {ROW_1, ROW_2, ROW_3, ROW_4};
static const uint8_t cols[NO_COLS] = {COL_1, COL_2, COL_3};
#else
static const uint8_t rows[NO_ROWS] = {ROW_1, ROW_2, ROW_3, ROW_4};
static const uint8_t cols[NO_COLS] = {COL_1, COL_2, COL_3, COL_4};
#endif

// Initialization function
void KPD_init()
{
	// Set all rows as output
	DIO_init_pin(KEYPAD_ROW_PORT, ROW_1, OUTPUT);
	DIO_init_pin(KEYPAD_ROW_PORT, ROW_2, OUTPUT);
	DIO_init_pin(KEYPAD_ROW_PORT, ROW_3, OUTPUT);
	DIO_init_pin(KEYPAD_ROW_PORT, ROW_4, OUTPUT);

	// Set all columns as input
	for (uint8_t j = 0; j < NO_COLS ; j++)
	{
		DIO_init_pin(KEYPAD_COLUMN_PORT,cols[j], INPUT);
	}
	// Set all inputs as internal pull up and all outputs as high
	for ( uint8_t i = 0; i < NO_ROWS ; i++)
	{
		DIO_write_pin(KEYPAD_ROW_PORT,rows[i], HIGH);
	}
	for (uint8_t k = 0; k < NO_COLS ; k++)
	{
		DIO_write_pin(KEYPAD_COLUMN_PORT,cols[k], HIGH);
	}
}

// Function to get the pressed key
uint8_t KPD_get_key()
{
	volatile uint8_t key_status = HIGH;
	for (uint8_t i = 0; i < NO_ROWS ; i++)
	{
		DIO_write_pin(KEYPAD_ROW_PORT, rows[i], LOW);
		for (uint8_t j = 0; j < NO_COLS ; j++)
		{
			// Enable the current row, low
			DIO_read_pin(KEYPAD_COLUMN_PORT, cols[j], &key_status);
			if (key_status == LOW)
			{
				// De bouncing
				_delay_ms(20);
				// Wait until the key is not pressed
				while (key_status == LOW)
				{
					DIO_read_pin(KEYPAD_COLUMN_PORT, cols[j], &key_status);
				}
				return keypad_keys[i][j];
			}
			else
			{
				//do nothing
			}
		}
		// Disable the current row, high
		DIO_write_pin(KEYPAD_ROW_PORT, rows[i], HIGH);
	}
	return 0;
}