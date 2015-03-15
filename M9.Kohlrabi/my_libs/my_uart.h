/*
 * my_uart.h
 *
 * Created: 29/01/2015 22:03:11
 *  Author: cezet/MLYNY9
 */ 


#ifndef MY_UART_H_
#define MY_UART_H_

#define UART_BAUD 9600
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL * UART_BAUD) -1)

void USART_Init( uint16_t _UBRR );
void uart_putc(char char_data);
void uart_puts(char *s);
void uart_puts_P(const char * s);
void uart_put_long( uint32_t value, uint8_t radix);

#endif /* MY_UART_H_ */