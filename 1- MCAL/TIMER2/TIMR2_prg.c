
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMR2_int.h"
#include "TIMR02_priv.h"
#include "TIMR2_config.h"

void (*TIMER2_OV_CallBack) (void) ;
void (*TIMER2_CTC_CallBack) (void) ;

void TIMER2_void_Init(void)
{
	#if(TIMER2_MODE == TIMER2_NORMAL)
		CLEAR_BIT(TCCR2 , 6);
		CLEAR_BIT(TCCR2 , 3);
	
	#elif(TIMER2_MODE == TIMER2_PHASE_PWM)
		CLEAR_BIT(TCCR2 , 6);
		SET_BIT(TCCR2 , 3);
		
	#elif(TIMER2_MODE == TIMER2_CTC  )
		SET_BIT(TCCR2 , 6);
		CLEAR_BIT(TCCR2 , 3);
	#elif(TIMER2_MODE == TIMER2_FAST_PWM )
		SET_BIT(TCCR2 , 6);
		SET_BIT(TCCR2 , 3);
	#endif
	
	#if(TIMER2_PRESCALER == TIMER2_DIV_BY_1)
		SET_BIT(TCCR2 , 0);
		CLEAR_BIT(TCCR2 , 1);
		CLEAR_BIT(TCCR2 , 2);
	
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_8)
		CLEAR_BIT(TCCR2 , 0);
		SET_BIT(TCCR2 , 1);
		CLEAR_BIT(TCCR2 , 2);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_32 )
			SET_BIT(TCCR2 , 0);
			SET_BIT(TCCR2 , 1);
			CLEAR_BIT(TCCR2 , 2);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_64 )
		CLEAR_BIT(TCCR2 , 0);
		CLEAR_BIT(TCCR2 , 1);
		SET_BIT(TCCR2 , 2);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_128 )
		SET_BIT(TCCR2 , 0);
		CLEAR_BIT(TCCR2 , 1);
		SET_BIT(TCCR2 , 2);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_256 )
		CLEAR_BIT(TCCR2 , 0);
		SET_BIT(TCCR2 , 1);
		SET_BIT(TCCR2 , 2);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_1024 )
		SET_BIT(TCCR2 , 0);
		SET_BIT(TCCR2 , 1);
		SET_BIT(TCCR2 , 2);
		
	#endif
	
	#if(TIMER2_COM_EVENT == TIMER2_NO_ACTION)
		CLEAR_BIT(TCCR2 , 4);
		CLEAR_BIT(TCCR2 , 5);
		
	
	#elif(TIMER2_COM_EVENT == TIMER2_TOGGLE)
		SET_BIT(TCCR2 , 4)
		CLEAR_BIT(TCCR2 , 5);
	#elif(TIMER2_COM_EVENT == TIMER2_CLEAR )
		CLEAR_BIT(TCCR2 , 4);
		SET_BIT(TCCR2 , 5);
	#elif(TIMER2_COM_EVENT == TIMER2_SET )
		SET_BIT(TCCR2 , 4);
		SET_BIT(TCCR2 , 5);

		
	#endif
	/*Disable Interrupts*/
	CLEAR_BIT(TIMSK , 0);	
	CLEAR_BIT(TIMSK , 1);
	/*CLEAR FLAGS*/
	SET_BIT(TIFR , 0);	
	SET_BIT(TIFR , 1);
	/*Clear register*/
	TCNT2 = 0 ;
	OCR2 = 0 ;
	
	
}

void TIMER2_void_SetTimerReg(u8 Copy_uint8Val)
{
	TCNT2 = Copy_uint8Val ;
}

void TIMER2_void_SetCompareVal(u8 Copy_uint8Val)
{
	OCR2 = Copy_uint8Val ;
}

void TIMER2_void_EnableOVInt(void)
{
	SET_BIT(TIMSK , 6);
}

void TIMER2_void_DisableOVInt(void)
{
	CLEAR_BIT(TIMSK , 6);
}

void TIMER2_void_EnableCTCInt(void)
{
	SET_BIT(TIMSK , 7);
}

void TIMER2_void_DisableCTCInt(void)
{
	CLEAR_BIT(TIMSK , 7);
}

void TIMER2_void_SetOVCallBack(void (*Copy_ptr) (void) )
{
	TIMER2_OV_CallBack = Copy_ptr ;
}

void TIMER2_void_SetCTCCallBack(void (*Copy_ptr) (void) )
{
	TIMER2_CTC_CallBack = Copy_ptr ;
	
}

void __vector_5(void) __attribute__((signal , used));
void __vector_5(void)
{
	
	TIMER2_OV_CallBack();
}

void __vector_4(void) __attribute__((signal , used));
void __vector_4(void)
{
	
	TIMER2_CTC_CallBack();
}
