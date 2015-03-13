/*
 * Kohlrabi by czoper/MLYNY9
 *
 * Created: 07/03/2015 18:41:11
 *  
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "my_libs/common.h"
#include "my_libs/RS232.h"
#include "my_libs/HD44780.h"
#include "my_libs/dhtxx.h"
#include "my_libs/I2C.h"
//#include "my_libs/RS232.h"
#include "my_libs/my_uart.h"



int main(void)
{
	//DECLARATIONS
	
	uint8_t cycle_counter = 0;
	int rh_int, rh_dec, th_int, th_dec, dh_checksum;
	char text_buffer[10];
	uint8_t a =0;
	
	
	// DO TESTOW
	
	DDRA |=  (1<<PA4);
	PORTA |= (1<<PA4);
	
	
	USART_Init(__UBRR);
	
	LCD_Initalize();
	LCD_Clear();
	LCD_WriteText("***START***");
	
	
	uart_puts("\rUART INIT......\n\r");
	itoa(a, text_buffer, 10);
	uart_puts(text_buffer);
	
	
	while(1)
    {
		//5 seconds trigger
		if(cycle_counter >= 4)
		{
				cycle_counter = 0;
				
				dhtxx_reset(2);
				
				dhtxx_check(2);
				
				rh_int = dhtxx_byte_read(2);
				
				rh_dec = dhtxx_byte_read(2);
				
				dhtxx_reset(3);
				
				dhtxx_check(3);
				
				th_int = dhtxx_byte_read(3);
				
				th_dec = dhtxx_byte_read(3);
			
			//	rh_int = rh_int >> 8; 
			//	th_int = dhtxx_byte_read(2);
			//	th_dec = dhtxx_byte_read(2);
			//	dh_checksum = dhtxx_byte_read(2);
				
		//	a = rh_dec + rh_int + th_dec + th_int;
			
				
			
			
				uart_puts("DHT 1: ");
				itoa(rh_int, text_buffer, 10);
				uart_puts(text_buffer);
				uart_puts(" ");
				
				itoa(rh_dec, text_buffer, 10);
				uart_puts(text_buffer);
			
				uart_puts("\tDHT 2: ");
				
				itoa(th_int, text_buffer, 10);
				uart_puts(text_buffer);
				uart_puts(" ");
				
				itoa(th_dec, text_buffer, 10);
				uart_puts(text_buffer);				
				
				uart_puts("\r\n");
				
		}
		_delay_ms(1000);
		cycle_counter++;
		itoa(cycle_counter, text_buffer, 10);
		uart_puts(text_buffer);
		uart_puts(" ");
		         
    }
}