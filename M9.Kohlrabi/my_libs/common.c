/*
 * common.c
 *
 * Created: 02/03/2015 00:04:09
 *  Author: cezet/MLYNY9
 */ 

#include "common.h"

void bcd_to_ascii(char inp_byte, char *text){
	*text++ = (inp_byte >> 4) + '0';
	*text++ = (inp_byte & 0x0F) + '0';
	*text++ = '\0';
}

void itoa8bit(int8_t input_int, char *char_table,uint8_t digits){
	
	
	
	if (input_int & 0x80)
	{
		*char_table = '-';
	}
	
}