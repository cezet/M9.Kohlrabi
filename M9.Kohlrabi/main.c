/*
 * Kohlrabi by cezet/MLYNY9
 *
 * Created: 07/03/2015 18:41:11
 *  
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>


#include "my_libs/common.h"
#include "my_libs/RS232.h"
#include "my_libs/HD44780.h"
#include "my_libs/dhtxx.h"
#include "my_libs/I2C.h"
//#include "my_libs/RS232.h"
#include "my_libs/my_uart.h"

#include "fatfs/ff.h"

#define KEY1 (1<<PD5)
#define KEY2 (1<<PD7)
#define KEY_DIR DDRD
#define KEY_PORT PORTD
#define KEY_PIN PIND
#define RELAY_DIR DDRA
#define RELAY_PORT PORTA
#define RELAY_PIN (1<<PA4)

#define DELTA_TH 1
#define STATUS_FAN_ON (1<<0)
#define STATUS_KEY1_PRESSED (1<<1)
#define STATUS_KEY2_PRESSED (1<<2)

//EEPROM STORED VARIABLES:

int EEMEM ee_th1_offset;
int EEMEM ee_th2_offset;
int EEMEM ee_rh1_offset;
int EEMEM ee_rh2_offset;


int main(void)
{
	//DECLARATIONS
	
	uint8_t cycle_counter = 0;
	int rh1, th1, rh2, th2;
	int rh_avg = 0, th_avg =0;
	int th1_offset = 0, rh1_offset = 0, th2_offset = 0, rh2_offset = 0;
	char text_buffer[10];
	register uint8_t status_register = 0;
	int histeresis = 0;
			
	uint8_t bufor[4];
	uint8_t seconds, minutes, hours;

	RELAY_DIR |= RELAY_PIN;
	
	
	KEY_DIR &= ~( KEY1 | KEY2);
	KEY_PORT |= (KEY1 | KEY2);
		
	//USART_Init(__UBRR);
	TWI_init_baud();
	LCD_Initalize();
	LCD_Clear();
	LCD_WriteText("Czas: ");
	
	th1_offset = eeprom_read_word(&ee_th1_offset);
	th2_offset = eeprom_read_word(&ee_th2_offset);
	rh1_offset = eeprom_read_word(&ee_rh1_offset);
	rh2_offset = eeprom_read_word(&ee_rh2_offset);
	
	
	while(1)
    {
		
		if (KEY_PIN & KEY1)
		{
			status_register &= ~(STATUS_KEY1_PRESSED);
		}
		else if (!(KEY_PIN & KEY1) && !(status_register & STATUS_KEY1_PRESSED))
		{
			status_register |= STATUS_KEY1_PRESSED;
			//something to do when key pressed 
			
			
			rh_avg = (rh1 + rh2) / 2;
			th_avg = (th1 + th2) / 2;
			
			th1_offset = th1 - th_avg;
			th2_offset = th2 - th_avg;
			rh1_offset = rh1 - rh_avg;
			rh2_offset = rh2 - rh_avg;
			
			eeprom_write_word(&ee_th1_offset, th1_offset );
			eeprom_write_word(&ee_th2_offset, th2_offset );
			eeprom_write_word(&ee_rh1_offset, rh1_offset );
			eeprom_write_word(&ee_rh2_offset, rh2_offset );
		} 
		
		
		
		if (KEY_PIN & KEY2)
		{
		status_register &= ~(STATUS_KEY2_PRESSED);
		}
		else if (!(KEY_PIN & KEY2) && !(status_register & STATUS_KEY2_PRESSED))
		{
			status_register |= STATUS_KEY2_PRESSED;
			//something to do when key pressed
			
			//PORTA ^= RELAY_PIN;
		}
		
		
		
		//5 seconds trigger
		if(cycle_counter >= 4)
		{
				cycle_counter = 0;
				
				dhtxx_reset(2);
				dhtxx_check(2);
				rh1 = dhtxx_byte_read(2);
				th1 = dhtxx_byte_read(2);
			
				
				dhtxx_reset(3);
				dhtxx_check(3);
				rh2 = dhtxx_byte_read(3);
				th2 = dhtxx_byte_read(3);
				
			
						
			
			
			
				itoa(rh1 - rh1_offset, text_buffer, 10);
				LCD_GoTo(0,1);
				LCD_WriteText("R1: ");
				LCD_WriteText(text_buffer);
				LCD_WriteText(" ");
				
				itoa(th1 - th1_offset, text_buffer, 10);
				LCD_GoTo(8,1);
				LCD_WriteText("T1: ");
				LCD_WriteText(text_buffer);
				LCD_WriteText(" ");
				
				itoa(rh2 - rh2_offset, text_buffer, 10);
				LCD_GoTo(0,2);
				LCD_WriteText("R2: ");
				LCD_WriteText(text_buffer);
				LCD_WriteText(" ");
				
				itoa(th2 - th2_offset, text_buffer, 10);
				LCD_GoTo(8,2);
				LCD_WriteText("T2: ");
				LCD_WriteText(text_buffer);
				LCD_WriteText(" ");
				
				itoa(th1_offset, text_buffer, 10);
				LCD_GoTo(0,3);
				LCD_WriteText("TO: ");
				LCD_WriteText(text_buffer);
				
				itoa(rh1_offset, text_buffer, 10);
				LCD_GoTo(8,3);
				LCD_WriteText("RO: ");
				LCD_WriteText(text_buffer);
							
				
			
				
		}
		
		_delay_ms(1000);
		cycle_counter++;
	
		if ((th2 - th2_offset > th1 - th1_offset + DELTA_TH) && !(status_register & STATUS_FAN_ON))
		{
			PORTA &= ~RELAY_PIN;
			
		} 
		else
		{
			PORTA |= RELAY_PIN;
		}
		
		TWI_read_buffer(0xA2, 0x02, 4, bufor);
		
		TWI_read_buffer(0xA2, 0x02, 4, bufor);
		
		
		seconds = bufor[0];
		minutes = bufor[1];
		hours = bufor[2];
		
		LCD_GoTo(7, 0);
		bcd_to_ascii(hours, text_buffer);
		LCD_WriteText(text_buffer);
		LCD_WriteText(":");
		bcd_to_ascii(minutes, text_buffer);
		LCD_WriteText(text_buffer);
		LCD_WriteText(":");
		
		//itoa(seconds, text_buffer, 10);
		bcd_to_ascii(seconds, text_buffer);
		LCD_WriteText(text_buffer);
		
	}
		
		
		
}