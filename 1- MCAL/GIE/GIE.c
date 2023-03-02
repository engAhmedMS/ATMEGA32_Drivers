#include "STD_Types.h"
#include "Bit_Math.h"

#include "GIE.h"

#define SREG    *((volatile u8*)0x5F)

void GIE_voidGlobalInterruptEnable(void)
{
	SET_BIT(SREG,7);
}

void GIE_voidGlobalInterruptDisable(void)
{
	CLEAR_BIT(SREG,7);
}
