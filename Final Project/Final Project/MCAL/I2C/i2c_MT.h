/*
 * i2c_MT.h
 *
 *  Created on: Sep 16, 2016
 *      Author: Mohamed Taha
 */

#ifndef I2C_MT_H_
#define I2C_MT_H_

#include "../../service_layer/MCU_config.h"
#include <util/twi.h>

#define I2C_F 100000UL
#define I2C_PRESCALER 1 
#define I2C_TWBR_VAL ((F_CPU/I2C_F)-16)/(2*4)

void i2c_init(void);

void i2c_start(void);

void i2c_write(unsigned char data);

unsigned char i2c_read(unsigned char ACK);

void i2c_stop(void);



uint8_t i2c_get_status();


void i2c_slave_init(unsigned char My_Address);

unsigned char i2c_slave_available();

#endif /* I2C_MT_H_ */
