
#ifndef lcd
#define lcd
#include "dio.h"
#include <util/delay.h>


#define		UPPER			1
#define		LOWER			0
#define		LCD_PORT		DIO_PORTB
#define		LCD_CHANNELS	LOWER
#define		RS_PORT			DIO_PORTA
#define		RS_PIN			DIO_PIN3
#define		EN_PORT			DIO_PORTA
#define		EN_PIN			DIO_PIN2


typedef enum {
		CMD_4bit_mode	=	0x28,
		CMD_retrun_home	 =	0x02,
		CMD_Display_on	=	0x0E,
		CMD_Clear_display =	0x01
	}lcd_Cmd_Type;


void lcd_init(void);
void lcd_sendData(u8 data);
void lcd_sendCmd(lcd_Cmd_Type cmd);
void lcd_gotoRowColumn(u8 row, u8 column);
void lcd_displyChar(char chr);
void lcd_displyStr(char* str);
void lcd_customWrite(u8* custCfg);
void lcd_Enable_pulse(void) ;
void lcd_DisplayNumber3(u16 number);


#endif
