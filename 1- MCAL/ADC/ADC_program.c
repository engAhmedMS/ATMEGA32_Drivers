/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 2 May 2019	                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : prog.c for ADC		                    */
/************************************************************/


/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "STD_Types.h"
#include "Bit_Math.h"

/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_private.h"
volatile u8* Global_ADC_Reading = 0;
/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/


/****************************************************************/
/* Description    :  This function used to initialize ADC 	    */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/

static u8 ADC_u8SelAdj(u8 Copy_u8Adj);
static u8 ADC_u8Prescale(u8 Copy_u8Scale);
static u8 ADC_u8SelChannel(u8 Copy_u8Channel, u8 Copy_u8Mode);
static u8 ADC_u8RefVolt(u8 Copy_u8Ref);


void ADC_voidInit (void)
{
	
	
	/* End ( if ) condition for Macros */	
	// 1- select reference voltage
	ADC_u8RefVolt(AVCC);
	// 2- select pre-scaler
	ADC_u8Prescale(ADC_PRESCALLER);
	// 3- select adjustment
	ADC_u8SelAdj(ADJUSTMENT);
	// 4- set autotriggering
	ADC_voidAutoTrigger();
	// 4- disable ADC

	
	
}


/****************************************************************/
/* Description    : This function used to Enable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidEnable()
{
	
	SET_BIT( ADCSRA , ADCSRA_ADEN );
	void ADC_voidDisable();
	
}

/****************************************************************/
/* Description    : This function used to Enable ADC Interrput	*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidInterrputEnable(u8* var)
{

	Global_ADC_Reading = var;
	SET_BIT( ADCSRA , ADCSRA_ADIE );
	
}


/****************************************************************/
/* Description    : This function used to Disable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidDisable()
{
	
	CLEAR_BIT( ADCSRA , ADCSRA_ADEN );
	
}


/****************************************************************/
/* Description    : This function used to Start converting		*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidStartConversion()
{
	
	SET_BIT( ADCSRA , ADCSRA_ADSC );
	
}


/****************************************************************/
/* Description    : This function used to Set lach Interrupt	*/
/*									 happens.					*/ 
/*																*/
/*					Inputs : Sense Mode				  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidAutoTrigger()
{
	

	
/****************************************************************/	
/** !comment : From Data Sheet : Starting conversion on positive*/
/*			   edge when ADATE = 1						    	*/
/****************************************************************/

	
	/** Enable ADC Auto Trigger	 							   **/
	/** ADATE = 1 =====> 	SET_BIT( ADATE , 5 ); 			   **/

    SET_BIT( ADCSRA , ADCSRA_ADATE );
	

		/*  ( if / else if ) condition for Macros */
	#if ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING_MODE 
	CLEAR_BIT( SFIOR , SFIOR_ADTS0 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS1 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS2 );
	
	#elif ADC_AUTO_TRIGGER_SOURCE == ANALOG_COMPARATOR
	SET_BIT( SFIOR , SFIOR_ADTS0);
	CLEAR_BIT( SFIOR , SFIOR_ADTS1 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS2 );
	
	#elif ADC_AUTO_TRIGGER_SOURCE == EXTERNAL_INTERRPUT_REQUEST_0
	CLEAR_BIT( SFIOR , SFIOR_ADTS0 );
	SET_BIT( SFIOR , SFIOR_ADTS1 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS2 );

	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COUNTER_0_COMPARE_MATCH
	SET_BIT( SFIOR , SFIOR_ADTS0 );
	SET_BIT( SFIOR , SFIOR_ADTS1 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS2 );

	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COUNTER_0_OVERFLOW
	CLEAR_BIT( SFIOR , SFIOR_ADTS0 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS1 );
	SET_BIT( SFIOR , SFIOR_ADTS2 );
	
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COUNTER_COMPARE_MATCH_B
	SET_BIT( SFIOR , SFIOR_ADTS0 );
	CLEAR_BIT( SFIOR , SFIOR_ADTS1 );
	SET_BIT( SFIOR , SFIOR_ADTS2 );

	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COUNTER_1_OVERFLOW
	CLEAR_BIT( SFIOR , SFIOR_ADTS0 );
	SET_BIT( SFIOR , SFIOR_ADTS1 );
	SET_BIT( SFIOR , SFIOR_ADTS2 );

	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COUNTER_1_CAPTURE_EVENT
	SET_BIT( SFIOR , SFIOR_ADTS0 );
	SET_BIT( SFIOR , SFIOR_ADTS1 );
	SET_BIT( SFIOR , SFIOR_ADTS2 );
	
	#endif
	/* End ( if ) condition for Macros */
	
}


/****************************************************************/
/* Description    : This function used to Read ADC and 			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : u16 Digital Converting melli Volt	*/
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

u16 ADC_u16ReadADCInMV(u8 channel)
{
	u16 mv_result;

	// select channel
	ADC_u8SelChannel(channel, ADC_MODE_SINGLE);
	//ADC_VoidStartConversion();
	ADC_voidStartConversion();
	// wait untill conversion is complete
	while(CHECK_BIT(ADCSRA, ADCSRA_ADIF) == 0);
	// clear conversion completed flag
	SET_BIT(ADCSRA, ADCSRA_ADIF);
	mv_result = ADCH;

	return mv_result;
}



u16 ADC_read()
{

	return ADCH;
}

void ADC_voidReadADCInterrupt(u8* an_read)
{
	Global_ADC_Reading = an_read;
	// select channel
	ADC_u8SelChannel(ADC_CHANNEL_NUMBER, ADC_MODE_SINGLE);
	//ADC_VoidStartConversion();
	ADC_voidStartConversion();

	//enable ADC Interrupt
//	ADC_voidInterrputEnable();

}


void __vector_16(void)	__attribute__(( signal , used ));
void __vector_16(void)
{
	*Global_ADC_Reading = ADCH;
}



static u8 ADC_u8SelChannel(u8 Copy_u8Channel, u8 Copy_u8Mode)
{
	u8 Local_Error = 0;

	if(Copy_u8Mode == ADC_MODE_SINGLE)
	{
		ADMUX &= ADC_CH_MASK;
		ADMUX |= Copy_u8Channel;

	}
	else if(Copy_u8Mode == ADC_MODE_DIFF)
	{
		//NOT IMPLEMENTED YET
	}
	return Local_Error;
}


static u8 ADC_u8RefVolt(u8 Copy_u8Ref)
{

	ADMUX &= 0b00111111;

	if(Copy_u8Ref == AVCC)
	{
		ADMUX |= ADC_REF_AVCC_MASK;
	}
	else if(Copy_u8Ref == AREF)
	{
		ADMUX |= ADC_REF_AREF_MASK;
	}
	else if(Copy_u8Ref == INTERNAL)
	{
		ADMUX |= ADC_REF_INTERNAL_MASK;
	}




	return 0;
}


static u8 ADC_u8SelAdj(u8 Copy_u8Adj)
{
	if(Copy_u8Adj == LEFT_ADJUSTMENT)
	{
		SET_BIT(ADMUX, ADMUX_ADLAR);
	}
	else if(Copy_u8Adj == RIGHT_ADJUSTMENT)
	{
		CLEAR_BIT(ADMUX, ADMUX_ADLAR);
	}

	return 0;
}

static u8 ADC_u8Prescale(u8 Copy_u8Scale)
{
	switch(Copy_u8Scale)
	{
		ADCSRA &= 0b11111000;
		case DIVID_BY_2: 							break;
		case DIVID_BY_4: 	ADCSRA|= 0b00000010;	break;
		case DIVID_BY_8: 	ADCSRA|= 0b00000011;	break;
		case DIVID_BY_16: 	ADCSRA|= 0b00000100;	break;
		case DIVID_BY_32: 	ADCSRA|= 0b00000101;	break;
		case DIVID_BY_64: 	ADCSRA|= 0b00000110;	break;
		case DIVID_BY_128: 	ADCSRA|= 0b00000111;	break;
	}


	return 0;
}


/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/
