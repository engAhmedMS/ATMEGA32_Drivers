#include "bit_math.h"
#include "Std_Types.h"

#define F_CPU 8000000UL
#include "util/delay.h"
#include "dio.h"
#include "LED.h"
#include "GIE.h"
#include "ADC_int.h"







/********* application to test  ADC with interrupt ****************
 * the 8 bit value read from pin A0 is displayed on port B
 *
 *
 */

#define DEBOUNCING_DELAY_MS	150


int main(void)
{
	dio_vidConfigPort(DIO_PORTB, PORT_ALL_OUTPUT);
	ADC_voidInit();
	ADC_voidEnable();

	u8 read = 0;
	ADC_voidInterrputEnable(&read);
	ADC_voidReadADCInterrupt(DIO_U8_PIN_0);

	GIE_voidGlobalInterruptEnable();


	while(1)
	{
		dio_vidSetPortValue(DIO_PORTB, read);


	}
}

