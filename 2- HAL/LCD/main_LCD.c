#include "bit_math.h"
#include "Std_Types.h"
#include "util/delay.h"
#include "lcd.h"



/********* application to test  LCD ****************
 * writing my name with 4-bit Mode
 * NOTE: this driver is not compatible with fares kit
 * 		 as it requires Consecutive LCD data pins
 */

#define TOGGLE_DELAY_MS	500

int main(void)
{
	lcd_init();
	char my_name[] = "AHMED";

	lcd_displyStr(my_name);





	return 0;
}
