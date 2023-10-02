/*
 * DIO.c
 *
 * Created: 11/12/2022 1:02:30 PM
 *  Author: Mohamed Taha Gabriel
 */ 

#include "DIO.h"



EN_DIO_state_t DIO_init_pin(uint8_t port_number , uint8_t pin_number ,uint8_t direction )
{
	switch(port_number)
	{
		case 'a':
			switch(direction)
			{
				case INPUT:
					DDRA &=~(1<<pin_number);
					break;
				case OUTPUT:
					DDRA |=(1<<pin_number);
					break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'b':
			switch(direction)
			{
				case INPUT:
				DDRB &=~(1<<pin_number);
				break;
				case OUTPUT:
				DDRB |=(1<<pin_number);
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'c':
			switch(direction)
			{
				case INPUT:
				DDRC &=~(1<<pin_number);
				break;
				case OUTPUT:
				DDRC |=(1<<pin_number);
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'd':
			switch(direction)
			{
				case INPUT:
				DDRD &=~(1<<pin_number);
				break;
				case OUTPUT:
				DDRD |=(1<<pin_number);
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		default:
			return DIO_NOT_OK;
			break;
	}
	return DIO_OK;
	
}

//EN_DIO_state_t DIO_init_port(uint8_t port_number ,uint8_t direction ); // 0b11110000


//function to write digital high or digital low
EN_DIO_state_t DIO_write_pin(uint8_t port_number , uint8_t pin_number , uint8_t value)
{
	switch(port_number)
	{
		case 'a':
		switch(value)
		{
			case LOW:
			PORTA &=~(1<<pin_number);
			break;
			case HIGH:
			PORTA |=(1<<pin_number);
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'b':
		switch(value)
		{
			case LOW:
			PORTB &=~(1<<pin_number);
			break;
			case HIGH:
			PORTB |=(1<<pin_number);
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'c':
		switch(value)
		{
			case LOW:
			PORTC &=~(1<<pin_number);
			break;
			case HIGH:
			PORTC |=(1<<pin_number);
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'd':
		switch(value)
		{
			case LOW:
			PORTD &=~(1<<pin_number);
			break;
			case HIGH:
			PORTD |=(1<<pin_number);
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
	
}



//function to toggle a pin
EN_DIO_state_t DIO_toggle_pin(uint8_t port_number , uint8_t pin_number)
{
	switch(port_number)
	{
		case 'a':
		PORTA ^=(1<<pin_number);
		break;
		case 'b':
		PORTB ^=(1<<pin_number);
		break;
		case 'c':
		PORTC ^=(1<<pin_number);
		break;
		case 'd':
		PORTD ^=(1<<pin_number);
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
	
}

//function to read the value of the pin
EN_DIO_state_t DIO_read_pin(uint8_t port_number , uint8_t pin_number, uint8_t* retValue )
{
	switch(port_number)
	{
		case 'a':
			*retValue = ( (PINA&(1<<pin_number))>>pin_number );
			break;
		case 'b':
			*retValue = ( (PINB&(1<<pin_number))>>pin_number );
			break;
		case 'c':
			*retValue = ( (PINC&(1<<pin_number))>>pin_number );
			break;
		case 'd':
			*retValue = ( (PIND&(1<<pin_number))>>pin_number );
			break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
}

// function to initialize all pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_port(uint8_t port_number ,uint8_t direction ) // 0b11110000
{
	switch(port_number)
	{
		case 'a':
		DDRA = direction;
		break;
		case 'b':
		DDRB = direction;
		break;
		case 'c':
		DDRC = direction;
		break;
		case 'd':
		DDRD = direction;
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
}


//function to initialize multiple pins
EN_DIO_state_t DIO_init_multiple_pins(uint8_t port_number,uint8_t pin_numbers ,uint8_t direction )
{
	switch(port_number)
	{
		case 'a':
			switch (direction)
			{
				case OUTPUT:
				DDRA |= pin_numbers;
				break;
				case INPUT:
				DDRA &= ~ pin_numbers;
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'b':
			switch (direction)
			{
				case OUTPUT:
				DDRB |= pin_numbers;
				break;
				case INPUT:
				DDRB &= ~ pin_numbers;
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'c':
			switch (direction)
			{
				case OUTPUT:
				DDRC |= pin_numbers;
				break;
				case INPUT:
				DDRC &= ~ pin_numbers;
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		case 'd':
			switch (direction)
			{
				case OUTPUT:
				DDRD |= pin_numbers;
				break;
				case INPUT:
				DDRD &= ~ pin_numbers;
				break;
				default:
				return DIO_NOT_OK;
				break;
			}
			break;
		default:
			return DIO_NOT_OK;
			break;
	}
	return DIO_OK;
}

//function to write a certain value on the whole port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_port(uint8_t port_number , uint8_t value) //0b1111000
{
	switch(port_number)
	{
		case 'a':
		PORTA = value;
		break;
		case 'b':
		PORTB = value;
		break;
		case 'c':
		PORTC = value;
		break;
		case 'd':
		PORTD = value;
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
}

// function to initialize upper pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_upper_pins_port(uint8_t port_number ,uint8_t direction ) // 0b11110000
{
	switch(port_number)
	{
		case 'a':
		switch(direction)
		{
			case INPUT:
				DDRA &= 0x0f;
				break;
			case OUTPUT:
				DDRA |= 0xf0;
				break;
			default:
				return DIO_NOT_OK;
				break;
		}
		break;
		case 'b':
		switch(direction)
		{
			case INPUT:
			DDRB &= 0x0f;
			break;
			case OUTPUT:
			DDRB |= 0xf0;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'c':
		switch(direction)
		{
			case INPUT:
			DDRC &= 0x0f;
			break;
			case OUTPUT:
			DDRC |= 0xf0;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'd':
		switch(direction)
		{
			case INPUT:
			DDRD &= 0x0f;
			break;
			case OUTPUT:
			DDRD |= 0xf0;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;
	
}

// function to initialize lower pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_lower_pins_port(uint8_t port_number ,uint8_t direction ){	switch(port_number)
	{
		case 'a':
		switch(direction)
		{
			case INPUT:
			DDRA &= 0xf0;
			break;
			case OUTPUT:
			DDRA |= 0x0f;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'b':
		switch(direction)
		{
			case INPUT:
			DDRB &= 0xf0;
			break;
			case OUTPUT:
			DDRB |= 0x0f;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'c':
		switch(direction)
		{
			case INPUT:
			DDRC &= 0xf0;
			break;
			case OUTPUT:
			DDRC |= 0x0f;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		case 'd':
		switch(direction)
		{
			case INPUT:
			DDRD &= 0xf0;
			break;
			case OUTPUT:
			DDRD |= 0x0f;
			break;
			default:
			return DIO_NOT_OK;
			break;
		}
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;}//function to write a certain value on the upper pins of the port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_upper_pins_port(uint8_t port_number , uint8_t value){	switch(port_number)
	{
		case 'a':
		PORTA = (PORTA & 0x0f) | value ;
		break;
		case 'b':
		PORTB = (PORTB & 0x0f) | value ;
		break;
		case 'c':
		PORTC = (PORTC & 0x0f) | value ;
		break;
		case 'd':
		PORTD = (PORTD & 0x0f) | value ;
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;}//function to write a certain value on the lower pins of the port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_lower_pins_port(uint8_t port_number , uint8_t value){	switch(port_number)
	{
		case 'a':
		PORTA = (PORTA & 0xf0) | value ;
		break;
		case 'b':
		PORTB = (PORTB & 0xf0) | value ;
		break;
		case 'c':
		PORTC = (PORTC & 0xf0) | value ;
		break;
		case 'd':
		PORTD = (PORTD & 0xf0) | value ;
		break;
		default:
		return DIO_NOT_OK;
		break;
	}
	return DIO_OK;}