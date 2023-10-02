/*
 * EEPROM.h
 *	EEPROM24C16 driver
 *  Created on: Sep 18, 2016
 *      Author: Mohamed Taha
 */

#ifndef EEPROM_MT_H_
#define EEPROM_MT_H_
#include "../../service_layer/MCU_config.h"
#include "../../service_layer/std_types_MT.h"
#include "../../MCAL/I2C/i2c_MT.h"



#define EEPROM_ADRESS 0xA0


/*
 * function declarations
 */

void EEPROM_INIT(void);
void EEPROM_write (uint8_t memory_location, uint8_t slave_address , uint8_t data);
uint8_t EEPROM_READ(uint8_t memory_location, uint8_t slave_address);




#endif /* EEPROM_MT_H_ */
