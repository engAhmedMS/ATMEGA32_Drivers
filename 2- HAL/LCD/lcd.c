/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"
#include "lcd.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define DELAY_POWER_UP 40
#define DELAY_PULSE 2
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
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                                                                         
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/

void lcd_init(void)
{
	#if LCD_CHANNELS==UPPER 
		dio_vidConfigChannel(LCD_PORT,DIO_PIN4,OUTPUT);
		dio_vidConfigChannel(LCD_PORT,DIO_PIN5,OUTPUT);
		dio_vidConfigChannel(LCD_PORT,DIO_PIN6,OUTPUT);
		dio_vidConfigChannel(LCD_PORT,DIO_PIN7,OUTPUT);
	#elif LCD_CHANNELS==LOWER 
		 dio_vidConfigChannel(LCD_PORT,DIO_PIN0,OUTPUT);
		 dio_vidConfigChannel(LCD_PORT,DIO_PIN1,OUTPUT);
		 dio_vidConfigChannel(LCD_PORT,DIO_PIN2,OUTPUT);
		 dio_vidConfigChannel(LCD_PORT,DIO_PIN3,OUTPUT);
	#endif
	
	dio_vidConfigChannel(RS_PORT,RS_PIN,OUTPUT);
	dio_vidConfigChannel(EN_PORT,EN_PIN,OUTPUT);
	_delay_ms(40);
	lcd_sendCmd(CMD_retrun_home) ;
	lcd_sendCmd(CMD_4bit_mode) ;
	lcd_sendCmd(CMD_Display_on) ;
	lcd_sendCmd(CMD_Clear_display) ;
}


void lcd_sendCmd(lcd_Cmd_Type cmd)
{
	dio_vidWriteChannel(RS_PORT,RS_PIN,STD_LOW);
	#if LCD_CHANNELS== UPPER 
		u8 mask = 0xF0;
		dio_vidWriteChannelGroup(LCD_PORT, cmd>>4, mask, 4);
		lcd_Enable_pulse();
		dio_vidWriteChannelGroup(LCD_PORT, cmd, mask, 4);
		lcd_Enable_pulse();
		
	#elif LCD_CHANNELS== LOWER
		u8 mask = 0x0F;
		dio_vidWriteChannelGroup(LCD_PORT, cmd>>4, mask, 0);
		lcd_Enable_pulse();
		dio_vidWriteChannelGroup(LCD_PORT, cmd, mask, 0);
		lcd_Enable_pulse();
	#endif
}
void lcd_sendData(u8 data)
{
	dio_vidWriteChannel(RS_PORT,RS_PIN,STD_HIGH);
	#if LCD_CHANNELS== UPPER
	u8 mask = 0xF0;
	dio_vidWriteChannelGroup(LCD_PORT, data>>4, mask, 4);
	lcd_Enable_pulse();
	dio_vidWriteChannelGroup(LCD_PORT, data, mask, 4);
	lcd_Enable_pulse();
	
	#elif LCD_CHANNELS== LOWER
	u8 mask = 0x0F;
	dio_vidWriteChannelGroup(LCD_PORT, data>>4, mask, 0);
	lcd_Enable_pulse();
	dio_vidWriteChannelGroup(LCD_PORT, data, mask, 0);
	lcd_Enable_pulse();
	#endif
}

void lcd_Enable_pulse(void) 
{
	dio_vidWriteChannel(EN_PORT,EN_PIN,STD_HIGH);
	_delay_ms(2);
	dio_vidWriteChannel(EN_PORT,EN_PIN,STD_LOW);
	
}

void lcd_displyChar(char chr)
{
	lcd_sendData(chr);
}
void lcd_displyStr(char* str)
{
	u8 idx = 0;
	while(str[idx] != 0)
	{
		lcd_displyChar(str[idx]);
		idx++;
	}
}

void lcd_DisplayNumber3(u16 number)
{

	lcd_sendData(number/100 + '0');
	lcd_sendData( (number/10)%10  + '0');
	lcd_sendData(number%10 + '0');

}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
