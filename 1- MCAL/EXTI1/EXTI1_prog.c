/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 20 April 2019                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : prog.c for EXT1		                    */
/************************************************************/


/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "STD_Types.h"
#include "Bit_Math.h"


/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "EXTI1_int.h"
#include "EXTI1_config.h"
#include "EXTI1_private.h"

#define NULL ((void*) 0)
/***********************************************************/
/**!comment   :  pointer to function for callback	       */
/***********************************************************/

static volatile void (*x) (void);

/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/


/****************************************************************/
/* Description    :  This function used to initialize EXT1      */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/



void EXT1_voidInit (void)
{
	
	/*  ( if / else if ) condition for Macros */
	#if EXT1_SENSE_MODE == IOC
	SET_BIT(MCUCR , 2);
	CLEAR_BIT(MCUCR , 3);
	
	#elif EXT1_SENSE_MODE == RISING
	SET_BIT(MCUCR , 2);
	SET_BIT(MCUCR , 3);
	
	#elif EXT1_SENSE_MODE == FALLING
	CLEAR_BIT(MCUCR , 2);
	SET_BIT(MCUCR , 3);
	
	#elif EXT1_SENSE_MODE == LOW_LEVEL
	CLEAR_BIT(MCUCR , 2);
	CLEAR_BIT(MCUCR , 3);
	
	#endif
	/* End ( if ) condition for Macros */

	
/** disable EXT1 in initialization function  **/
/** like : void EXT1_voidDisable(); 		  */
	CLEAR_BIT( GICR , 7 );
	SET_BIT(GIFR , 7 ) ;
	
	
}


/****************************************************************/
/* Description    : This function used to Enable EXT1			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT1_voidEnable()
{
	
	SET_BIT( GICR , 7 );
	
}


/****************************************************************/
/* Description    : This function used to Disable EXT1			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT1_voidDisable()
{
	
	CLEAR_BIT( GICR , 7 );
	
}


/****************************************************************/
/* Description    : This function used to communicate with the	*/
/*					function in App Layer(The Callback function)*/ 
/*						[ Layer Architecture Problem Solved ]	*/
/*																*/
/*					Inputs : Pointer to function that points to	*/
/*							 the first line of the function(ISR)*/
/*					Return : void								*/
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT1_voidCallBack( volatile void (*addresscpy) (void) )
{
	if(addresscpy != NULL)
	{
		x = addresscpy;
	}
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
void EXT1_voidSetSignalch(u8 SenseCpy)
{
	if( SenseCpy == IOC)
	{
		SET_BIT(MCUCR , 2);
		CLEAR_BIT(MCUCR , 3);
	}

	else if( SenseCpy == RISING)
	{
		SET_BIT(MCUCR , 2);
			SET_BIT(MCUCR , 3);

	}


	else if( SenseCpy == FALLING)
	{
		CLEAR_BIT(MCUCR , 2);
		SET_BIT(MCUCR , 3);

	}


	else if( SenseCpy == LOW_LEVEL)
	{
		CLEAR_BIT(MCUCR , 2);
		CLEAR_BIT(MCUCR , 3);
	}


}

/****************************************************************/
/* Description    : This function used to Check if interrupt is */
/*					Executed or Not.							*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : flag Status [ LBTY_OK , LBTY_NOK ]	*/
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
/*
flagStatus EXT1_enuIsExecuted( void )
{
	flagStatus ErrorStatus ;
	
	if( (GET_BIT(GIFR, 6)) == 1 )
	{
		
		ErrorStatus = LBTY_NOK ;
	}
	else if ( (GET_BIT(GIFR, 6)) == 0 )
	{
		
		ErrorStatus = LBTY_OK ;
	}
	
	return ErrorStatus ;
}
*/
/** Linker Problem solved */
void __vector_2(void) __attribute__(( signal , used ));


void __vector_2(void)
{
	x();
	
}

/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/
