/*
 * dhtxx_v2.h
 *
 * Created: 03/03/2015 16:03:13
 *  Author: czop.m
 */ 


#ifndef DHTXX_H_
#define DHTXX_H_

#define DHTxx_PORT PORTA
#define DHTxx_PIN PINA
#define DHTxx_DIR DDRA

extern uint8_t sensor_id;

void dhtxx_reset(uint8_t sensor_id);
void dhtxx_check(uint8_t sensor_id);
int dhtxx_byte_read(uint8_t sensor_id);
void dhtxx_message_read(uint8_t *table, uint8_t sensor_id);
void dhtxx_convert2int16(uint16_t *table);
int8_t dhtxx_trunc(uint16_t *table);


#endif /* DHTXX_V2_H_ */