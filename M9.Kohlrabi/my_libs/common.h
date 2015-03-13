/*
 * common.h
 *
 * Created: 02/03/2015 00:04:25
 *  Author: czop.m
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#include <avr/io.h>

void bcd_to_ascii(char inp_byte, char *text);

#endif /* COMMON_H_ */