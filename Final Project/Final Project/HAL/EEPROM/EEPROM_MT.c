/*
 * EEPROM_MT.c
 *  EEPROM24C16 driver
 *  Created on: Sep 18, 2016
 *      Author: Mohamed Taha
 */

#include "EEPROM_MT.h"


void EEPROM_INIT(void)
{
	i2c_init();
}

void EEPROM_write (uint8_t memory_location, uint8_t slave_address , uint8_t data)
{
	i2c_init();
	i2c_start();
	i2c_write(slave_address); //slave address 0xa0
	i2c_write(memory_location); //memory location
	// This step can be repeated
	i2c_write(data);   //data
	i2c_stop();
	_delay_ms(15);
}



uint8_t EEPROM_READ(uint8_t memory_location, uint8_t slave_address)
{
	uint8_t data=0;


	i2c_start();                      /* Send Start Bit 						 */
	i2c_write(slave_address);         /* Send Slave address with Operation Write */
	i2c_write(memory_location);       /* Send Memory Location Address 			 */

	i2c_start();                      /* Send Restart Bit 						 */
	i2c_write(slave_address | 1);     /* Send Slave address with Operation read  */
	data = i2c_read(1);
	
	
	i2c_stop();

	return data;
}



//void EEPROM_SaveString (uint8 * str);

