/*
 * I2C.h
 *
 * Created: 28/01/2015 21:07:59
 *  Author: czop.m
 */ 


#ifndef I2C_H_
#define I2C_H_

#define ACK 1
#define NACK 0

//uint8_t TWI_read(uint8_t ack);
void TWI_init_baud(void);
void TWI_write_buffer(uint8_t SLA, uint8_t addr, uint8_t lenght, uint8_t *buffer);
void TWI_read_buffer(uint8_t SLA, uint8_t addr, uint8_t lenght, uint8_t *buffer);



#endif /* I2C_H_ */