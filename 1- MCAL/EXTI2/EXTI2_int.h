/****************************************************************/
/*   Author             :    Ahmed Atia Atia 				    */
/*	 Date 				:    20 April 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:   public Accessing mechanism prototype*/ 
/*							and Sense Mode Definition [int.h] 	*/
/****************************************************************/



/****************************************************************/
/* Description   : Guard to protect this File from include more */
/*                 than one time .                              */
/****************************************************************/

#ifndef _EXT2_INT_H
#define _EXT2_INT_H


/****************************************************************/	
/** !comment : Sense Mode Definition					   		*/
/****************************************************************/

#define FALLING		4
#define RISING		7



/****************************************************************/
/* Description    :  This function used to initialize EXT2      */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/
void EXT2_voidInit ( void );


/****************************************************************/
/* Description    : This function used to Enable EXT2			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
void EXT2_voidEnable( void );


/****************************************************************/
/* Description    : This function used to Disable EXT2			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
void EXT2_voidDisable( void );


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
void EXT2_voidCallBack(volatile void (*addresscpy) (void) );


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
void EXT2_voidSetSignalch(u8 SenseCpy);


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
flagStatus EXT2_enuIsExecuted( void );
*/

#endif	/** !comment  :  End of guard                          **/
