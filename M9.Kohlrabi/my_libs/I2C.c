/*
 * I2C.c
 *
 * Created: 28/01/2015 21:07:44
 *  Author: czop.m
 */ 
#include <avr/io.h>
#include "I2C.h"

void TWI_init_baud(void){
	TWBR = 1;
	TWSR = (1<<TWPS0) | (1<<TWPS1);
}
void TWI_start(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while (!(TWCR & (1<<TWSTO)));
}

void TWI_write(uint8_t byte){
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	
}

uint8_t TWI_read(uint8_t ack){
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<<TWEA);
	/*if (ack )
	{
		TWCR |= (1<<TWEA);
	} 
	else
	{
		TWCR &= ~(1<<TWEA);
	} */
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t TWIReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t TWIReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

void TWI_write_buffer(uint8_t SLA, uint8_t addr, uint8_t lenght, uint8_t *buffer)
{
	TWI_start();
	TWI_write(SLA);
	TWI_write(addr);
	while (lenght--) TWI_write(*buffer++);
	TWI_stop();
}


void TWI_read_buffer(uint8_t SLA, uint8_t addr, uint8_t lenght, uint8_t *buffer){
	
	TWI_start();
	TWI_write(SLA);
	TWI_write(addr);
	TWI_start();
	TWI_write(SLA + 1);
	while (lenght>0){
		lenght--;
		*buffer++ = TWI_read(lenght ? ACK : NACK);
		
	}
	//buffer [0]=TWIReadACK();
	//buffer [1]=TWIReadACK();
	//buffer [2]=TWIReadNACK();
	
	
	TWI_stop();
}

