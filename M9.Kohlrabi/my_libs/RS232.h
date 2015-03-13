/*
 * RS232.h
 *
 * Created: 29/01/2015 21:10:30
 *  Author: czop.m
 */ 


#ifndef RS232_H_
#define RS232_H_



void USART_Transmit(unsigned char char_data);
unsigned char USART_Receive(void);

#endif /* RS232_H_ */