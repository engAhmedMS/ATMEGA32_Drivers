#include "bit_math.h"
#include "Std_Types.h"

#define F_CPU 8000000UL
#include "util/delay.h"
#include "dio.h"
#include "LED.h"
#include "GIE.h"
#include "Motor_stepper.h"


/********* application to test  ADC with interrupt ****************
 * the 8 bit value read from pin A0 is displayed on port B
 *
 *
 */

#define STEP_DELAY	250


int main(void)
{

	Stepper_Init();

	while(1)
	{
		Stepper_TurnLeftFull();
		_delay_ms(STEP_DELAY);

	}
}

