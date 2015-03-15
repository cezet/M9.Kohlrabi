/*
 * dhtxx_v2.c
 *
 * Created: 03/03/2015 16:02:54
 *  Author: cezet/MLYNY9
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "dhtxx.h"


void dhtxx_reset(uint8_t sensor_id){
	
	DHTxx_DIR |= (1 << sensor_id);
	DHTxx_PORT &= ~(1 << sensor_id);
	
	_delay_ms(20);
	
	DHTxx_DIR &= ~(1 << sensor_id);
	DHTxx_PORT |= (1<< sensor_id);
	_delay_us(5);
	
}

void dhtxx_check(uint8_t sensor_id)
{
	while (DHTxx_PIN & (1<<sensor_id))
	{
	}
	while (!(DHTxx_PIN & (1<<sensor_id)))
	{
	}
	while (DHTxx_PIN & (1<<sensor_id))
	{
	}
	
}

int dhtxx_byte_read(uint8_t sensor_id){
	
	int byte_data = 0;
		
	for (uint8_t i = 0; i < 16; i++)
	{
		while (!(DHTxx_PIN & (1<<sensor_id)))
		{
			_delay_us(1);
		}
		_delay_us(35);
		
		byte_data = byte_data << 1;
		
		if (DHTxx_PIN & (1<<sensor_id))
		{
			byte_data |= 1;
			while(DHTxx_PIN & (1<<sensor_id)){
				_delay_us(1);
			}
		}
		
	}
	
	return byte_data;
	
}

void dhtxx_message_read(uint8_t *table, uint8_t sensor_id){
	
	table += 4;
	for (int byte = 4; byte > 0; byte--)
	{
		*table-- = dhtxx_byte_read(sensor_id);
	}
	/*
	*table = table;
	for (int byte = 0; byte < 4 ; byte++)
	{
		*table++ = dhtxxV2_byte_read(sensor_id); 
	}
	*/
	
}

void dhtxx_convert2int16(uint16_t *table){
	if (*table & 0x8000)
	{
		*table &= ~0x8000;
		*table = ~(*table);
		*table = *table + 1;
	}
}
int8_t dhtxx_trunc(uint16_t *table){
	
	*table = *table / 10;
	*table++;
	*table = *table / 10;
}