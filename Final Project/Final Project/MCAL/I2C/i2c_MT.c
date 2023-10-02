/*
 * i2c_MT.c
 *
 *  Created on: Sep 16, 2016
 *      Author: Mohamed Taha
 */

#include "i2c_MT.h"


void i2c_init(void)
{
	TWSR = 0x00;         // make prescaler =1
	TWBR = (uint8_t)I2C_TWBR_VAL;         
	TWCR = (1<<TWEN);     // Enable I2C Module
}

void i2c_start(void)
{
	/*
	 * clear interrupt flag,start condition bit and enable module i2c
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/*
	 * Waiting until the start condition is transmitted
	 */
	while ((TWCR&(1<<TWINT))==0);
}


void i2c_stop(void)
{
	/*
	 * Enable stop bit
	 */
	TWCR = (1<< TWINT) | (1<< TWEN) | (1<<TWSTO);
	/*
	 * Waiting until the start condition is transmitted
	 */
	//while ((TWCR&(1<<TWINT))==0);

}

void i2c_write (unsigned char data)
{
	/*
	 * Put the data in TW data register
	 */
	TWDR = data;
	/*
	 * To start sending Byte
	 */
	TWCR = (1<<TWINT) | (1<< TWEN);
	/*
	 *waiting until the byte is transmitted completely
	 */
	while ((TWCR & (1<< TWINT)) == 0);
}



unsigned char i2c_read(unsigned char ACK)
{
	/*
	 * To start receiving Byte
	 */
	TWCR = (1<< TWINT) | (1<< TWEN) | (ACK<< TWEA);
	/*
	 *waiting until the byte is transmitted completely
	 */
	while ((TWCR & (1<< TWINT)) == 0);
	/*
	 * Return the data read
	 */
	
	return TWDR;
	
}


void i2c_slave_init(unsigned char My_Address)
{
	/* initiate the slave address */ 
	TWAR = My_Address;
	/* clear interrupt flag,start condition bit and enable module i2c */ 
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

unsigned char i2c_slave_available()
{
	TWCR |= (1<<TWINT) | (1<<TWEN)| (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	return ((TWSR & 0xF8));
}

uint8_t i2c_get_status()
{
	while (!(TWCR & (1<<TWINT)));
	return ((TWSR & 0xF8));
}