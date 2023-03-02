#include "bit_math.h"
#include "Std_Types.h"
#include "dio.h"

/********* application test DIO ****************
 * config pin A4 as output	(Connected to green led on fares kit)
 * config pin D7 as input pull up	(connected to BUTTON1 in fares kit)
 * while pin D7 pressed pin A4 output high else output low
 */

#define LED_PORT	DIO_PORTA
#define LED_PIN		DIO_PIN4

#define BUTTON_PORT	DIO_PORTD
#define BUTTON_PIN	DIO_PIN7


int main(void)
{

	dio_vidConfigChannel(LED_PORT, LED_PIN, OUTPUT);
	dio_vidConfigChannel(BUTTON_PORT, BUTTON_PIN, INPUT);
	dio_vidEnablePullUp(BUTTON_PORT, BUTTON_PIN);
	volatile dio_level_t read = STD_HIGH;

	while(1)
	{
		read = dio_dioLevelReadChannel(BUTTON_PORT, BUTTON_PIN);
		if(read == STD_LOW)
		{
			dio_vidWriteChannel(LED_PORT, LED_PIN, STD_HIGH);
		}
		else
		{
			dio_vidWriteChannel(LED_PORT, LED_PIN, STD_LOW);
		}
	}






	return 0;
}
