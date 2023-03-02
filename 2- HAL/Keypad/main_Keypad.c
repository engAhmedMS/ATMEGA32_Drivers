#include "bit_math.h"
#include "Std_Types.h"

#define F_CPU 8000000UL
#include "util/delay.h"
#include "dio.h"
#include "lcd.h"
#include "keypad.h"





/********* application to test  Keypad with LCD ****************
 * the application prints the row and colomn of each key
 *
 *
 */



int main(void)
{
	keypad_vidInit();
	lcd_init();

	u8 read = 0;
	while(1)
	{
		read = keypad_u8GetKey();


	}
}

