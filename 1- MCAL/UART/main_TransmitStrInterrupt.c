/*
	ATmega16 external interrupt to toggle the PORTC
	(www.electronicwings.com)
*/


#define F_CPU	8000000UL
#include "bit_math.h"
#include "std_types.h"
#include "util/delay.h"
#include "dio.h"
#include "LED.h"
#include "BUTTON.h"
#include "EXTI0_int.h"
#include "EXTI1_int.h"
#include "ADC_int.h"
#include "lcd.h"
#include "GIE.h"

#include "uart.h"

#include "TIMR2_int.h"


#define DEBOUNCING_DELAY_MS	100


#define SREG   (*(volatile u8 * ) (0X5F))
#define SREG_IBIT	7


void call(void)
{
	static u8 counter = 0;

	if(counter%20 == 0)
	{
		LED_TOG(RED);
		_delay_ms(50);
	}
	counter++;

}


int main(void)
{
	LED_INIT();
	UART_Init(UART_BAUDRATE_9600);
	GIE_voidGlobalInterruptEnable();
	u8 read = 0;
	UART_TransmitStr("AHMED MOHAMMED SAYED MOHAMMED215616bjsnbjesngiueuigbwaigbiwan;ouwrbgouwbgiypwbubwribwuibuvbiwpyvouewevbipweyfbouewbfpiyBEFIYGLIUFEB5305615185408165198+4321+451894118946518945498adflmepofkpoqeijfoiqejojqepighwohguqhwpifjhq3iugh[qogpiyr3hgtuiyqvtyq3g1");

	while(1)
	{
		UART_TransmitStr("AHMED MOHAMMED SAYED MOHAMMED215616bjsnbjesngiueuigbwaigbiwan;ouwrbgouwbgiypwbubwribwuibuvbiwpyvouewevbipweyfbouewbfpiyBEFIYGLIUFEB5305615185408165198+4321+451894118946518945498adflmepofkpoqeijfoiqejojqepighwohguqhwpifjhq3iugh[qogpiyr3hgtuiyqvtyq3g1");


		LED_ON(GREEN);
		_delay_ms(100);
		LED_OFF(GREEN);
		_delay_ms(100);
	}
}

