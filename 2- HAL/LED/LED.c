/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  LED.c
 *        \brief  
 *				Source file for interfacing with LEDs
 *      \details  
 *				this file provides function to turning LEDs ON - OFF and Toggle its state of fares kit
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"
#include "LED.h"
#include "LED_CFG.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
* \Syntax          : void LED_INIT(void)        
* \Description     : initialize all 4 leds in the fares kit as output                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : void                                                                         
* \Return value:   : void                                  
*******************************************************************************/
void LED_INIT(void)
{
	dio_vidConfigChannel(YELLOW_PORT, YELLOW_CHANNEL, OUTPUT);
	dio_vidConfigChannel(BLUE_PORT, BLUE_CHANNEL, OUTPUT);
	dio_vidConfigChannel(RED_PORT, RED_CHANNEL, OUTPUT);
	dio_vidConfigChannel(GREEN_PORT, GREEN_CHANNEL, OUTPUT);
}

/******************************************************************************
* \Syntax          : void LED_ON(LED_ID led_id)
* \Description     : turn specific led on by its id
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : led_id
* \Return value:   : void
*******************************************************************************/
void LED_ON(LED_ID led_id)
{
	if(led_id == YELLOW)
	{
		dio_vidWriteChannel(YELLOW_PORT, YELLOW_CHANNEL, YELLOW_LED_STATE);
	}
	else if(led_id == GREEN)
	{
		dio_vidWriteChannel(GREEN_PORT, GREEN_CHANNEL, GREEN_LED_STATE);
	}
	else if(led_id == RED)
	{
		dio_vidWriteChannel(RED_PORT, RED_CHANNEL, RED_LED_STATE);
	}
	else if(led_id == BLUE)
	{
		dio_vidWriteChannel(BLUE_PORT, BLUE_CHANNEL, BLUE_LED_STATE);
	}

}

/******************************************************************************
* \Syntax          : void LED_OFF(LED_ID led_id)
* \Description     : turn specific led off by its id
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : led_id
* \Return value:   : void
*******************************************************************************/
void LED_OFF(LED_ID led_id)
{
		if(led_id == YELLOW)
		{
			dio_vidWriteChannel(YELLOW_PORT, YELLOW_CHANNEL, !YELLOW_LED_STATE);
		}
		else if(led_id == GREEN)
		{
			dio_vidWriteChannel(GREEN_PORT, GREEN_CHANNEL, !GREEN_LED_STATE);
		}
		else if(led_id == RED)
		{
			dio_vidWriteChannel(RED_PORT, RED_CHANNEL, !RED_LED_STATE);
		}
		else if(led_id == BLUE)
		{
			dio_vidWriteChannel(BLUE_PORT, BLUE_CHANNEL, !BLUE_LED_STATE);
		}
	
}

/******************************************************************************
* \Syntax          : void LED_ON(LED_ID led_id)
* \Description     : Toggle specific led by its id
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : led_id
* \Return value:   : void
*******************************************************************************/
void LED_TOG(LED_ID led_id)
{
		if(led_id == YELLOW)
		{
			dio_vidFlipChannel(YELLOW_PORT, YELLOW_CHANNEL);
		}
		else if(led_id == GREEN)
		{
			dio_vidFlipChannel(GREEN_PORT, GREEN_CHANNEL);
		}
		else if(led_id == RED)
		{
			dio_vidFlipChannel(RED_PORT, RED_CHANNEL);
		}
		else if(led_id == BLUE)
		{
			dio_vidFlipChannel(BLUE_PORT, BLUE_CHANNEL);
		}
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
