/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  uart.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "uart.h"
#include "uart_reg.h"
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
* \Syntax          : void UART_Init(u16 baudRate)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : baudRate   UART baudrate                                                                     
* \Return value:   : None                                   
*******************************************************************************/
void UART_Init(u16 baudRate)
{
	/* Set baud rate */
	UART_UBRRL_REG = (u8)baudRate;
	UART_UBRRH_REG = (u8)(baudRate>>8);

	/* Enable receiver and transmitter */
	SET_BIT(UART_UCSRB_REG,RXEN_BIT_NO);  /* Enable Receiver*/
	SET_BIT(UART_UCSRB_REG,TXEN_BIT_NO);  /* Enable Transmitter */
	/* Set frame format: 8data, 1stop bit, Even Parity */
	UART_UCSRC_REG |= (1 << URSEL_BIT_NO) | UART_8_BIT_DATA | UART_EVEN_PARITY;

	SET_BIT(UART_UCSRB_REG,7); /*	Enable Rx Complete Interrupt	*/
	SET_BIT(UART_UCSRB_REG,6); /*	Enable Tx Complete Interrupt	*/
}

/******************************************************************************
* \Syntax          : void UART_TransmitChr(u8 data)      
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : data   data byte                                                                    
* \Return value:   : None                                   
*******************************************************************************/
void UART_TransmitChr(u8 data)
{
	while(CHECK_BIT(UART_UCSRA_REG, UDRE_BIT_NO) == 0);
	/* Put data into buffer*/
	UART_UDR_REG = data;
}

/******************************************************************************
* \Syntax          : u8 UART_ReceiveChr(void)       
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                    
* \Return value:   : u8     received data byte                                   
*******************************************************************************/
u8 UART_ReceiveChr(void)
{

	while(CHECK_BIT(UART_UCSRA_REG, RXC_BIT_NO) == 0);

	return UART_UDR_REG;
}


#define UART_BUFFER_MAX_SIZE	1000
u8 TX_byte_idx;
u8 TX_buffer[UART_BUFFER_MAX_SIZE];

void UART_TransmitStr(u8 *str)
{
	u8 idx=0;
	if(TX_byte_idx == 0)
	{
		while(str[idx] != 0)
		{
			TX_buffer[idx] = str[idx];
			idx++;
		}
		TX_buffer[idx] = 0;
		UART_UDR_REG = TX_buffer[0];
	}

}
void __vector_15(void) __attribute__(( signal , used ));	//Tx


void __vector_15(void)
{
	TX_byte_idx++;
	if(TX_buffer[TX_byte_idx] != 0)
	{
		UART_UDR_REG = TX_buffer[TX_byte_idx];
	}
	else
	{
		TX_byte_idx = 0;
	}

}

u8 RX_byte_idx;
u8* rec_buffer;
u8 REC_COMPLETE_FLAG;
void UART_RecStr(u8 *str)
{
	if(RX_byte_idx == 0)
	{
		REC_COMPLETE_FLAG = 0;
		rec_buffer[0] = UART_UDR_REG;
		rec_buffer = str;
	}
}

void __vector_13(void) __attribute__(( signal , used ));		//Rx
void __vector_13(void)
{
	RX_byte_idx++;
	rec_buffer[RX_byte_idx] = UART_UDR_REG;
	if(rec_buffer[RX_byte_idx] == 0)
	{
		RX_byte_idx = 0;
		REC_COMPLETE_FLAG = 1;
	}


}



/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
