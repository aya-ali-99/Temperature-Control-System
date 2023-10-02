/*
 * lcd.h
 *
 * Created: 03/12/2022 10:50:19
 *  Author: Ayaya
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO/DIO.h"/* LCD Data bits mode configuration */#define LCD_DATA_BITS_MODE 4/* Use higher 4 bits in the data port */#if (LCD_DATA_BITS_MODE == 4)#define UPPER_PORT_PINS#endif/* LCD HW Pins */#define RS 'b',0#define RW 'b',1#define E  'b',2#define LCD_CTRL_PORT 'b'#define LCD_DATA_PORT 'a'/* LCD Commands *///function set#define FOUR_BITS_DATA_MODE 0x02#define TWO_LINE_LCD_Four_BIT_MODE 0x28#define TWO_LINE_LCD_Eight_BIT_MODE 0x38//display on/off control#define CURSOR_OFF 0x0C#define CURSOR_ON 0x0E//display clear#define CLEAR_COMMAND 0x01//entry mode set#define SHIFT_CURSOR_RIGHT 0x06//set cursor location at position 0#define SET_CURSOR_LOCATION 0x80

#define SHIFT_LEFT_LCD 0x18
#define SHIFT_RIGHT_LCD 0x1c

// LCD initialization functionvoid LCD_init();//function to send a command to the LCDvoid LCD_sendCommand(uint8_t command);//function to send data or a character to the LCDvoid LCD_sendCharacter(sint8_t data );//function to send a string to the LCDvoid LCD_sendString(const sint8_t* str);//function to clear the screenvoid LCD_clear_screen();//function to display a string in a certain (x,y) positionvoid LCD_displayStringRowColumn(uint8_t row,uint8_t col,const sint8_t *Str);//function to display an integer in a certain (x,y) positionvoid LCD_displayIntegerRowColumn(uint8_t row,uint8_t col,sint32_t data);//function to go to a certain position on the LCDvoid LCD_goToRowColumn(uint8_t row,uint8_t col);//function to convert integer to string and display itvoid LCD_intgerToString(sint32_t data);




#endif /* LCD_H_ */