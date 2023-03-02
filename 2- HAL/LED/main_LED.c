#include "bit_math.h"
#include "Std_Types.h"
#include "dio.h"
#include "LED.h"
#include "util/delay.h"

/********* application to test  LED ****************
 * attach the GREEN LED
 * toggle Green LED every 500 ms
 */

#define TOGGLE_DELAY_MS	500

int main(void)
{

	LED_INIT();


	while(1)
	{
		LED_TOG(GREEN);
		_delay_ms(TOGGLE_DELAY_MS);
	}






	return 0;
}
