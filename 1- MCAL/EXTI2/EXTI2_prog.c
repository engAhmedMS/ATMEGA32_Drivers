/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 20 April 2019                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : prog.c for EXT2		                    */
/************************************************************/


/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "STD_Types.h"
#include "Bit_Math.h"


/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "EXTI2_int.h"
#include "EXTI2_config.h"
#include "EXTI2_private.h"

#define NULL ((void*) 0)
/***********************************************************/
/**!comment   :  pointer to function for callback	       */
/***********************************************************/

static volatile void (*x) (void);

/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/

/****************************************************************/
/* Description    :  This function used to initialize EXT2      */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/


#define EXT2_SENSE_MODE FALLING
void EXT2_voidInit (void)
{
	
	/*  ( if / else if ) condition for Macros */
	
	#if EXT2_SENSE_MODE == RISING
	SET_BIT(MCUCSR , 6);
	
	#elif EXT2_SENSE_MODE == FALLING
	CLEAR_BIT(MCUCSR , 6);
	
	#endif
	/* End ( if ) condition for Macros */

	
/** disable EXT2 in initialization function  **/
/** like : void EXT2_voidDisable(); 		  */
	CLEAR_BIT( GICR , 5 );
	SET_BIT(GIFR , 5 ) ;
	
	
}


/****************************************************************/
/* Description    : This function used to Enable EXT2			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT2_voidEnable()
{
	
	SET_BIT( GICR , 5 );
	
}


/****************************************************************/
/* Description    : This function used to Disable EXT2			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT2_voidDisable()
{
	
	CLEAR_BIT( GICR , 5 );
	
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

void EXT2_voidCallBack( volatile void (*addresscpy) (void) )
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
void EXT2_voidSetSignalch(u8 SenseCpy)
{

	if( SenseCpy == RISING)
	{
		SET_BIT(MCUCSR , 6);

	}


	else if( SenseCpy == FALLING)
	{
		CLEAR_BIT(MCUCSR , 6);

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
flagStatus EXT2_enuIsExecuted( void )
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
void __vector_3(void) __attribute__(( signal , used ));


void __vector_3(void)
{
	x();
	
}

/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/
