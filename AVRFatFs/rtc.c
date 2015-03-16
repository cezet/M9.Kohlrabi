/*--------------------------------------------------------------------------*/
/*  DS1338 RTC controls                                                     */

#include <avr/io.h>
#include <string.h>
#include "rtc.h"





/*-------------------------------------------------*/
/* I2C bus protocol                                */


static
void iic_delay (void)
{
	
}


/* Generate start condition on the IIC bus */
static
void iic_start (void)
{
	
}


/* Generate stop condition on the IIC bus */
static
void iic_stop (void)
{
	/*SDA_LOW();
	iic_delay();
	SCL_HIGH();
	iic_delay();
	SDA_HIGH();
	iic_delay(); */
}


/* Send a byte to the IIC bus */
static
int iic_send (BYTE dat)
{
	/*BYTE b = 0x80;
	int ack;


	do {
		if (dat & b)	 {	
			SDA_HIGH();
		} else {
			SDA_LOW();
		}
		iic_delay();
		SCL_HIGH();
		iic_delay();
		SCL_LOW();
		iic_delay();
	} while (b >>= 1);
	SDA_HIGH();
	iic_delay();
	SCL_HIGH();
	ack = SDA_VAL ? 0 : 1;	
	iic_delay();
	SCL_LOW();
	iic_delay();
	return ack; */
}


/* Receive a byte from the IIC bus */
static
BYTE iic_rcvr (int ack)
{
	UINT d = 1;


	return (BYTE)d;
}



/*-------------------------------------------------*/
/* I2C block read/write controls                   */


int iic_read (
	BYTE dev,		/* Device address */
	UINT adr,		/* Read start address */
	UINT cnt,		/* Read byte count */
	void* buff		/* Read data buffer */
)
{
	
	return cnt ? 0 : 1;
}



int iic_write (
	BYTE dev,			/* Device address */
	UINT adr,			/* Write start address */
	UINT cnt,			/* Write byte count */
	const void* buff	/* Data to be written */
)
{
}



/*-------------------------------------------------*/
/* RTC functions                                   */


int rtc_gettime (RTC *rtc)
{
	

	rtc->sec = 00; //(buf[0] & 0x0F) + ((buf[0] >> 4) & 7) * 10;
	rtc->min = 01; //(buf[1] & 0x0F) + (buf[1] >> 4) * 10;
	rtc->hour = 02;//(buf[2] & 0x0F) + ((buf[2] >> 4) & 3) * 10;
	rtc->wday = 01;//(buf[2] & 0x07);
	rtc->mday = 01; //(buf[4] & 0x0F) + ((buf[4] >> 4) & 3) * 10;
	rtc->month = 02; //(buf[5] & 0x0F) + ((buf[5] >> 4) & 1) * 10;
	rtc->year = 2015; //2000 + (buf[6] & 0x0F) + (buf[6] >> 4) * 10;

	return 1;
}




int rtc_settime (const RTC *rtc)
{

	/*BYTE buf[8];


	buf[0] = rtc->sec / 10 * 16 + rtc->sec % 10;
	buf[1] = rtc->min / 10 * 16 + rtc->min % 10;
	buf[2] = rtc->hour / 10 * 16 + rtc->hour % 10;
	buf[3] = rtc->wday & 7;
	buf[4] = rtc->mday / 10 * 16 + rtc->mday % 10;
	buf[5] = rtc->month / 10 * 16 + rtc->month % 10;
	buf[6] = (rtc->year - 2000) / 10 * 16 + (rtc->year - 2000) % 10;
	return iic_write(0xD0, 0, 7, buf);
	*/
}




int rtc_init (void)
{
	return 1;
}

