#include "bit_math.h"
#include "Std_Types.h"
#include "dio.h"
#include "LED.h"
#include "BUTTON.h"

/********* application to test BUTTON with LED ****************
 * attach the GREEN LED
 * attach BUTTON 1 with pull up configuration
 * while BUTTON1 is Pressed LED ON else LED off
 */



int main(void)
{

	LED_INIT();
	BUTTON_init();
	volatile BUTTON_STATE read = NOT_PRESSED;

	while(1)
	{
		read = BUTTON_get_status(BUTTON1);
		if(read == PRESSED)
		{
			LED_ON(GREEN);
		}
		else
		{
			LED_OFF(GREEN);
		}
	}






	return 0;
}
