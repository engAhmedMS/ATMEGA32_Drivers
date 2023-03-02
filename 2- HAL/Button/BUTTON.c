/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  BUTTON.c
 *        \brief  
 *				header file to interface with push buttons
 *      \details  
 *				This file provide function t initialize and read push buttons value
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"
#include "BUTTON.h"
#include "BUTTON_CFG.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 arr_button_channel[NUMBER_BUTTONS] = {BUTTON1_CHANNEL, BUTTON2_CHANNEL, BUTTON3_CHANNEL, BUTTON4_CHANNEL};
static u8 arr_BUTTON_CONNECTION[NUMBER_BUTTONS] = {BUTTON1_CONNECTION, BUTTON2_CONNECTION, BUTTON3_CONNECTION, BUTTON4_CONNECTION};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                                                                         
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                 
*******************************************************************************/
void BUTTON_init(void)
{
	for(u8 button_id=0; button_id<NUMBER_BUTTONS; button_id++)
	{
		dio_vidConfigChannel(BUTTON_PORT, arr_button_channel[button_id], INPUT);
		if(arr_BUTTON_CONNECTION[button_id] == INTERNAL_PULL_UP)
		{
			dio_vidEnablePullUp(BUTTON_PORT, arr_button_channel[button_id]);
		}
	}	
}
BUTTON_STATE BUTTON_get_status(BUTTON_ID button_id)
{
	volatile dio_level_t dio_read = 5;
	volatile dio_level_t button_read = 5;
	dio_read = dio_dioLevelReadChannel(BUTTON_PORT, arr_button_channel[button_id]);
	
	if(arr_BUTTON_CONNECTION[button_id] == PULL_DOWN)
	{
		if(dio_read == STD_HIGH)
		{
			button_read = PRESSED;
		}
		else
		{
			button_read = NOT_PRESSED;
		}
	}
	else if(arr_BUTTON_CONNECTION[button_id] == PULL_UP || arr_BUTTON_CONNECTION[button_id] == INTERNAL_PULL_UP)
	{
		if(dio_read == STD_LOW)
		{
			button_read = PRESSED;
		}
		else
		{
			button_read = NOT_PRESSED;
		}
	}
	return button_read;
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
