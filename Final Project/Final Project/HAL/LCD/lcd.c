/*
 * lcd.c
 *
 * Created: 03/12/2022 10:50:08
 *  Author: Ayaya
 */ 


#include "lcd.h"


// LCD initialization functionvoid LCD_init(){	// Initialize the control pins as outputs	DIO_init_pin(RS, OUTPUT);	DIO_init_pin(RW, OUTPUT);	DIO_init_pin(E, OUTPUT);		#if (LCD_DATA_BITS_MODE == 8)	// 8 bit mode initialize the data as output	DIO_init_port(LCD_DATA_PORT, 0xff);	// Wait more than 30 ms	_delay_ms(35);	// Function set	// Set two lines 8 bit mode	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);	_delay_us(40);	#elif (LCD_DATA_BITS_MODE == 4)	// 4 bit mode initialize the data as output		#ifdef UPPER_PORT_PINS		// Upper pins ----> pin 4 to 7		//DIO_init_port(LCD_DATA_PORT, 0xff);		DIO_init_upper_pins_port(LCD_DATA_PORT, OUTPUT);		#else		// Lower pins ----> pin 0 to 3		//DIO_init_port(LCD_DATA_PORT, 0xff);		DIO_write_lower_pins_port(LCD_DATA_PORT, OUTPUT);		#endif	// Wait more than 30 ms	_delay_ms(35);	// Function set	// Initialize 4 bit mode	LCD_sendCommand(FOUR_BITS_DATA_MODE);	// Set two lines 4 bit mode	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);	_delay_us(40);	#endif		// Display ON --- Cursor ON	LCD_sendCommand(CURSOR_ON);	_delay_us(40);	// Clear the display 	LCD_sendCommand(CLEAR_COMMAND);	_delay_ms(2);	LCD_sendCommand(SHIFT_CURSOR_RIGHT);}//function to send a command to the LCDvoid LCD_sendCommand(uint8_t command){	// Set RS 0 ---> Send a command	DIO_write_pin(RS, LOW);	// Write RW ---> 0	DIO_write_pin(RW, LOW);	#if (LCD_DATA_BITS_MODE == 8)		// In 8-bit mode ---> Send the command then enable		// Send the command		DIO_write_port(LCD_DATA_PORT, command);		// Enable LCD to read the command		DIO_write_pin(E, HIGH);		_delay_ms(1);		DIO_write_pin(E, LOW);		_delay_ms(1);	#elif (LCD_DATA_BITS_MODE == 4)		// In 4-bit mode 		// Send half the command (upper half)		#ifdef UPPER_PORT_PINS		DIO_write_upper_pins_port(LCD_DATA_PORT, (command & 0xf0));		#else		DIO_write_lower_pins_port(LCD_DATA_PORT, ((command & 0xf0)>>4));		#endif	// then enable	DIO_write_pin(E, HIGH);	_delay_ms(1);	DIO_write_pin(E, LOW);	_delay_ms(1);	// Send the lower half 		#ifdef UPPER_PORT_PINS		DIO_write_upper_pins_port(LCD_DATA_PORT, ((command & 0x0f)<<4));		#else		DIO_write_lower_pins_port(LCD_DATA_PORT, (command & 0x0f));		#endif	// enable	DIO_write_pin(E, HIGH);	_delay_ms(1);	DIO_write_pin(E, LOW);	_delay_ms(1);	#endif}//function to send data or a character to the LCDvoid LCD_sendCharacter(sint8_t data ){	// Set RS 1 ---> Send data	DIO_write_pin(RS, HIGH);	// Write RW ---> 0	DIO_write_pin(RW, LOW);	// Send the data	#if (LCD_DATA_BITS_MODE == 8)		// In 8-bit mode ---> Send the data then enable		// Send the data		DIO_write_port(LCD_DATA_PORT, data);		// Enable LCD to read the data		DIO_write_pin(E, HIGH);		_delay_ms(1);		DIO_write_pin(E, LOW);		_delay_ms(1);	#elif (LCD_DATA_BITS_MODE == 4)		// In 4-bit mode		// Send half the data (upper half)		#ifdef UPPER_PORT_PINS		DIO_write_upper_pins_port(LCD_DATA_PORT, (data & 0xf0));		#else		DIO_write_lower_pins_port(LCD_DATA_PORT, ((data & 0xf0)>>4));		#endif	// then enable	DIO_write_pin(E, HIGH);	_delay_ms(1);	DIO_write_pin(E, LOW);	_delay_ms(1);	// Send the lower half		#ifdef UPPER_PORT_PINS		DIO_write_upper_pins_port(LCD_DATA_PORT, ((data & 0x0f)<<4));		#else		DIO_write_lower_pins_port(LCD_DATA_PORT, (data & 0x0f));		#endif	// enable	DIO_write_pin(E, HIGH);	_delay_ms(1);	DIO_write_pin(E, LOW);	_delay_ms(1);	#endif}//function to send a string to the LCDvoid LCD_sendString(const sint8_t* str){	for (uint8_t i = 0; str[i] != 0; i++)
	{
		LCD_sendCharacter(str[i]);
	}}//function to clear the screenvoid LCD_clear_screen(){	// Clear the display	LCD_sendCommand(CLEAR_COMMAND);	_delay_ms(2);	LCD_sendCommand(SHIFT_CURSOR_RIGHT);}//function to display a string in a certain (x,y) positionvoid LCD_displayStringRowColumn(uint8_t row,uint8_t col,const sint8_t *Str){	LCD_goToRowColumn(row, col);	LCD_sendString(Str);}//function to display an integer in a certain (x,y) positionvoid LCD_displayIntegerRowColumn(uint8_t row,uint8_t col,sint32_t data){	LCD_goToRowColumn(row, col);	LCD_intgerToString(data);}//function to go to a certain position on the LCDvoid LCD_goToRowColumn(uint8_t row,uint8_t col){	uint8_t Address;	// First of all calculate the required address	switch (row)
	{
		case 0:
			Address = col;
			break;
		case 1:
			Address = col + 0x40;
			break;
		default:
			Address = col;
			break;
	}	// To write the specific address in the LCD	// We need to apply the corresponding command	// ob10000000 + Address	LCD_sendCommand(SET_CURSOR_LOCATION | Address);}//function to convert integer to string and display itvoid LCD_intgerToString(sint32_t data)
{
	sint8_t str[16];
	uint8_t i, rem, len = 0;
	sint32_t n;
	
	n= data;
	if(n == 0)
	{
		len = 1;
	}
	else
	{
		while (n != 0)
		{
			len++;
			n /= 10;
		}
	}
	if (len >= 15)
	{
		return;
	}
	for (i = 0; i < len ; i++)
	{
		rem = data % 10;
		data = data /10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	LCD_sendString(str);
}

