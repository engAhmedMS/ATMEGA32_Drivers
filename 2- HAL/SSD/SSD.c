#include "STD_TYPES.h"
#include "dio.h"
#include "SSD.h"



u8 SSD_DigitalValues[MAX_SSD_DIGIT] = {SSD_DIG0, SSD_DIG1, SSD_DIG2, SSD_DIG3, SSD_DIG4, SSD_DIG5, SSD_DIG6, SSD_DIG7, SSD_DIG8, SSD_DIG9};

u8 SSD_u8Init(SSD* Copy_pssd, dio_portId_t Copy_u8Port, SSD_COMTYPE Copy_u8ComType
							, dio_portId_t Copy_ComPort, dio_channelId_t Copy_ComChannel)
{

	Copy_pssd -> ComType = Copy_u8ComType;
	Copy_pssd -> PortName = Copy_u8Port;
	Copy_pssd -> ComPort = Copy_ComPort;
	Copy_pssd -> ComPin = Copy_ComChannel;

	dio_vidConfigPort(Copy_pssd -> PortName, PORT_ALL_OUTPUT);
	dio_vidConfigChannel(Copy_pssd->ComPort, Copy_pssd -> ComPin, OUTPUT);

	SSD_vidEnable(Copy_pssd);

	return 0;

}


u8 SSD_u8DisplayDigit(SSD* copy_pssd, u8 Copy_u8Digit)
{
	u8 Local_u8ErrorState = 0;
	if(Copy_u8Digit < MAX_SSD_DIGIT)
	{
		if(copy_pssd->ComType == SSD_COM_CATHOD)
		{
			dio_vidSetPortValue(copy_pssd -> PortName, SSD_DigitalValues[Copy_u8Digit]);
		}
		else if (copy_pssd->ComType == SSD_COM_ANODE)
		{
			dio_vidSetPortValue(copy_pssd -> PortName, ~SSD_DigitalValues[Copy_u8Digit]);
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;


}


void SSD_vidDisable(SSD* Copy_pssd)
{
	if(Copy_pssd->ComType == SSD_COM_ANODE)
	{
		dio_vidWriteChannel(Copy_pssd->ComPort, Copy_pssd->ComPin, STD_LOW);

	}
	else if(Copy_pssd->ComType == SSD_COM_CATHOD)
	{
		dio_vidWriteChannel(Copy_pssd->ComPort, Copy_pssd->ComPin, STD_HIGH);
	}
}



void SSD_vidEnable(SSD* Copy_pssd)
{
	if(Copy_pssd->ComType == SSD_COM_ANODE)
	{
		dio_vidWriteChannel(Copy_pssd->ComPort, Copy_pssd->ComPin, STD_HIGH);

	}
	else if(Copy_pssd->ComType == SSD_COM_CATHOD)
	{
		dio_vidWriteChannel(Copy_pssd->ComPort, Copy_pssd->ComPin, STD_LOW);
	}
}
