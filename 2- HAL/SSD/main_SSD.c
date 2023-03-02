#include "bit_math.h"
#include "Std_Types.h"

#define F_CPU 8000000UL
#include "util/delay.h"
#include "dio.h"
#include "SSD.h"
#include "BUTTON.h"



/********* application to test  Seven Segment Display ****************
 * up down counting on SSD
 * when pressing BUTTON1 2 seven segments start counting up from 0 t 99
 * when pressing BUTTON2 2 seven segments start counting down from 99 t 0
 *
 * NOTE: This code is not compatible with fares kit
 * 		 as it is not connected to a BCD Decoder
 * 		 so it uses 8 pins to connect a seven segment
 */



#define NUMBER_DIGITS			2
#define SSD_PORT				DIO_PORTA
#define SSD_COMMON_TYPE			SSD_COM_CATHOD
#define MOST_ENAPALE_PORT		DIO_PORTB
#define MOST_ENABLE_CHANNEL		DIO_PIN6
#define LEAST_ENAPLE_PORT		DIO_PORTB
#define LEAST_ENABLE_CHANNEL	DIO_PIN7
#define REFRESH_DELAY_MS		5
#define START_COUNT				0
#define END_COUNT				100
void Display_2DigitNumber(SSD* copy_pssdMost, SSD* copy_pssdLeast, u8 Copy_u8Number, u8 delay_ms);
void count(SSD* copy_pssdMost, SSD* copy_pssdLeast, u8 start, u8 end);



int main(void)
{
	SSD	ssd_most, ssd_least;

	SSD_u8Init(&ssd_most, SSD_PORT, SSD_COMMON_TYPE, MOST_ENAPALE_PORT, MOST_ENABLE_CHANNEL);
	SSD_u8Init(&ssd_least, SSD_PORT, SSD_COMMON_TYPE, LEAST_ENAPLE_PORT, LEAST_ENABLE_CHANNEL);

	BUTTON_init();

	volatile BUTTON_STATE read1 = NOT_PRESSED, read2 = NOT_PRESSED;

	while(1)
	{
		read1 = BUTTON_get_status(BUTTON1);
		read2 = BUTTON_get_status(BUTTON2);
		_delay_ms(150);
		if(read1 == PRESSED)
		{
			count(&ssd_most, &ssd_least, START_COUNT, END_COUNT);
		}
		if(read2 == PRESSED)
		{
			count(&ssd_most, &ssd_least, END_COUNT, START_COUNT);
		}




	}


}


void Display_2DigitNumber(SSD* copy_pssdMost, SSD* copy_pssdLeast, u8 Copy_u8Number, u8 delay_ms)
{
	SSD_vidEnable(copy_pssdMost);
	SSD_u8DisplayDigit(copy_pssdMost, (Copy_u8Number%100)/10);
	_delay_ms(delay_ms);
	SSD_vidDisable(copy_pssdMost);

	SSD_vidEnable(copy_pssdLeast);
	SSD_u8DisplayDigit(copy_pssdLeast, Copy_u8Number%10);
	_delay_ms(delay_ms);
	SSD_vidDisable(copy_pssdLeast);
}


void count(SSD* copy_pssdMost, SSD* copy_pssdLeast, u8 start, u8 end)
{
	if(start<end)
	{
		for(u8 counter = start; counter<end; counter++)
		{
			for(u8 delay_counter=0; delay_counter<20; delay_counter++)
			{

				Display_2DigitNumber(copy_pssdMost,copy_pssdLeast, counter, REFRESH_DELAY_MS);
			}

		}
	}

	else if(end<start)
	{
		for(u8 counter = start; counter>end; counter--)
		{
			for(u8 delay_counter=0; delay_counter<20; delay_counter++)
			{

				Display_2DigitNumber(copy_pssdMost,copy_pssdLeast, counter, REFRESH_DELAY_MS);
			}

		}

	}
}
