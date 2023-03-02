#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_


#define MAX_SSD_DIGIT 	10

// value = ABCD EFG_
#define SSD_DIG0	0xFC
#define SSD_DIG1	0x60
#define SSD_DIG2	0xDA
#define SSD_DIG3	0xF2
#define SSD_DIG4	0x66
#define SSD_DIG5	0xB6
#define SSD_DIG6	0xBE
#define SSD_DIG7	0xE0
#define SSD_DIG8	0xFF
#define SSD_DIG9	0xF6

typedef struct
{
		u8 ComType;
		u8 PortName;
		u8 ComPin;
		u8 ComPort;

}SSD;

typedef enum
{
	SSD_COM_CATHOD,
	SSD_COM_ANODE
	}SSD_COMTYPE;

u8 SSD_u8Init(SSD* Copy_pssd, dio_portId_t Copy_u8Port, SSD_COMTYPE Copy_u8ComType
							, dio_portId_t Copy_ComPort, dio_channelId_t Copy_ComChannel);

u8 SSD_u8DisplayDigit(SSD* copy_pssd, u8 Copy_u8Digit);

void SSD_vidEnable(SSD* Copy_pssd);

void SSD_vidDisable(SSD* Copy_pssd);


#endif
