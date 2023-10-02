/*
 * lcd.c
 *
 * Created: 03/12/2022 10:50:08
 *  Author: Ayaya
 */ 


#include "lcd.h"


// LCD initialization function
	{
		LCD_sendCharacter(str[i]);
	}
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
	}
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
