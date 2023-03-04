#include "Std_Types.h"
#include "Bit_Math.h"
#include "SPI.h"
#include "SPI_REGISTERS.h"
#include "dio.h"




void SPI_VoidInit(SPI* Copy_spi)
{
	// Select Master or slave
	SPI_u8MasterSlaveSelect(Copy_spi->role);
	if(Copy_spi->role == SPI_MASTER)
	{
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN5, OUTPUT);	//MOSI
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN6, INPUT);	//MISO
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN7, OUTPUT);	//SCLK
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN4, INPUT);	//SS'

		dio_vidEnablePullUp(DIO_PORTB, DIO_PIN4);
		//select CLK rate
		SPI_u8PreScaler(Copy_spi -> Prescaler);
	}
	else if(Copy_spi->role == SPI_SLAVE)
	{

		dio_vidConfigChannel(DIO_PORTB, DIO_PIN5, INPUT);	//MOSI

		dio_vidConfigChannel(DIO_PORTB, DIO_PIN6, OUTPUT);	//MISO
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN7, INPUT);	//SCLK
		dio_vidConfigChannel(DIO_PORTB, DIO_PIN4, INPUT);	//SS'
		//DIO_u8ActivatePinPullup(DIO_u8PORTB, DIO_u8PIN4);
	}

	//select CLK polarity and phase
	SPI_u8CLKPolPhase(Copy_spi -> CLKPolPhase);

	//select Data order
	SPI_u8DataOrder(Copy_spi -> DataOrder);

	SPI_u8Enable();

}


u8 SPI_u8Enable()
{
	SET_BIT(SPCR, SPCR_SPE);

	return 0;
}

u8 SPI_u8Disable()
{
	CLEAR_BIT(SPCR, SPCR_SPE);
	return 0;
}

u8 SPI_u8MasterSlaveSelect(u8 Copy_u8Select)
{
	if(Copy_u8Select == SPI_MASTER)
	{
		SET_BIT(SPCR, SPCR_MSTR);
	}
	else if(Copy_u8Select == SPI_SLAVE)
	{
		CLEAR_BIT(SPCR, SPCR_MSTR);
	}

	return 0;
}

u8 SPI_u8CLKPolPhase(u8 Copy_u8PolPhase)
{
	switch(Copy_u8PolPhase)
	{
		case SPI_SAMPLE_RISING:		CLEAR_BIT(SPCR, SPCR_CPOL);	CLEAR_BIT(SPCR, SPCR_CPHA);	break;
		case SPI_SETUP_RISING:		CLEAR_BIT(SPCR, SPCR_CPOL);	SET_BIT(SPCR, SPCR_CPHA);	break;
		case SPI_SAMPLE_FALLING:	SET_BIT(SPCR, SPCR_CPOL);	CLEAR_BIT(SPCR, SPCR_CPHA);	break;
		case SPI_SETUP_FALLING:		SET_BIT(SPCR, SPCR_CPOL);	SET_BIT(SPCR, SPCR_CPHA);	break;
	}
	return 0;
}

u8 SPI_u8PreScaler(u8 Copy_u8Scale)
{
	//initialize clock rate bits with 0
	SPCR &= SPI_PRESCAL_MASK;
	//check for clock rate bits only (bit 1:0)
	SPCR|= (Copy_u8Scale<<6)>>6;

	//enable double speed mode if needed
	if(CHECK_BIT(Copy_u8Scale, 2) == 0)	//(for 4, 16, 64, 128)
	{
		CLEAR_BIT(SPSR, SPSR_SPI2X);
	}
	else if(CHECK_BIT(Copy_u8Scale, 2) == 1)	//(for 2, 8, 32)
	{
		SET_BIT(SPSR, SPSR_SPI2X);
	}
	return 0;
}


u8 SPI_u8DataOrder(u8 Copy_u8Dataorder)
{
	if(Copy_u8Dataorder == SPI_DATAORDER_LSB)
	{
		SET_BIT(SPCR, SPCR_DORD);
	}
	else if(Copy_u8Dataorder == SPI_DATAORDER_MSB)
	{
		CLEAR_BIT(SPCR, SPCR_DORD);
	}
	return 0;
}

u8 SPI_u8SelectSlave(u8 Coy_u8Port, u8 Copy_u8Pin)
{
	dio_vidConfigChannel(Coy_u8Port, Copy_u8Pin, OUTPUT);
	dio_vidWriteChannel(Coy_u8Port, Copy_u8Pin, STD_LOW);
	return 0;
}

u8 SPI_u8ReleaseSlave(u8 Coy_u8Port, u8 Copy_u8Pin)
{
	dio_vidConfigChannel(Coy_u8Port, Copy_u8Pin, OUTPUT);
	dio_vidWriteChannel(Coy_u8Port, Copy_u8Pin, STD_HIGH);

	return 0;
}

u8 SPI_u8SendRecData(u8 Copy_u8Data)
{
	/* Write Data Byte */
	u8 Local_temp = SPDR;
	SPDR = Copy_u8Data;
	/* wait until transmission is completed */
	while( (CHECK_BIT(SPSR,SPSR_SPIF) == 0) && (CHECK_BIT(SPSR,SPSR_WCOL) == 0) );
	Copy_u8Data = SPDR;
	return Copy_u8Data;

}

u8 SPI_u8RecDataSlave()
{

	/* wait until transmission is completed */
	while( (CHECK_BIT(SPSR,SPSR_SPIF) == 0) && (CHECK_BIT(SPSR,SPSR_WCOL) == 0) );
	return SPDR;

}

void SPI_voidInterruptEnable()
{
	SET_BIT(SPCR, SPCR_SPIE);
}

u8 SPI_Data = 0;
u8 SPI_DATA_RECIVED_FLAG = 0;

void SPI_u8SendRecDataInterrupt(u8 Copy_u8Data)
{
	if(SPI_DATA_RECIVED_FLAG == 0)
	{
		SPDR = Copy_u8Data;
		SPI_DATA_RECIVED_FLAG=1;
	}


}


#include "LED.h"
void __vector_12(void)
{
	LED_ON(GREEN);
	SPI_Data = SPDR;
	SPI_DATA_RECIVED_FLAG = 0;
}




