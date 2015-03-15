/*
 * my_uart.c
 *
 * Created: 29/01/2015 22:02:56
 *  Author: cezet/MLYNY9
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "my_uart.h"

void USART_Init( uint16_t _UBRR )
{
	/* Set baud rate*/
	UBRRH = (uint8_t)(_UBRR>>8);
	UBRRL = (uint8_t) _UBRR;
	/* Enable receiver and transmitter*/
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit*/
}

void uart_putc( char char_data){
	while (!(UCSRA & (1<<UDRE)));
	
	UDR = char_data;
}

void uart_puts(char *s){
	
	while (*s) uart_putc(*s++);
}

void uart_puts_P(const char * s){
	register char c;
	while ((c=pgm_read_byte(s++))) uart_putc(c);
}

unsigned char UART_Receive(void){
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}

void uart_put_long( uint32_t value, uint8_t radix){
	char buffer[17];
	itoa(value, buffer, radix);
	uart_puts(buffer);
}