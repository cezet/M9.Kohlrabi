/*
 * RS232.c
 *
 * Created: 29/01/2015 21:10:11
 *  Author:cezet/MLYNY9
 */ 
#include <avr/io.h>

void USART_Transmit(unsigned char char_data){
	while (!(UCSRA & (1<<UDRE)));
	
	UDR = char_data;
}

unsigned char USART_Receive(void){
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}