#ifndef SPI_H_
#define SPI_H_


#define SPI_MASTER	1
#define SPI_SLAVE	0

#define SPI_IDLE_HIGH	1
#define SPI_IDLE_LOW	0

#define SPI_SAMPLE_RISING		0
#define SPI_SETUP_RISING		1
#define SPI_SAMPLE_FALLING		2
#define SPI_SETUP_FALLING		3

#define SPI_PRESCAL_MASK	0b11111100
#define SPI_PRESCALE_2		0b00000100
#define SPI_PRESCALE_4		0b00000000
#define SPI_PRESCALE_8		0b00000101
#define SPI_PRESCALE_16		0b00000001
#define SPI_PRESCALE_32		0b00000110
#define SPI_PRESCALE_64		0b00000010
#define SPI_PRESCALE_128	0b00000011

#define SPI_DATAORDER_LSB		1
#define SPI_DATAORDER_MSB		0

typedef struct SPI
{
	u8 role;
	u8 CLKPolPhase;
	u8 Prescaler;
	u8 DataOrder;
}SPI;

extern u8 SPI_Data;

void SPI_VoidInit(SPI* Copy_spi);
u8 SPI_u8Enable();
u8 SPI_u8Disable();
u8 SPI_u8MasterSlaveSelect(u8 Copy_u8Select);
u8 SPI_u8CLKPolPhase(u8 Copy_u8PolPhase);
u8 SPI_u8PreScaler(u8 Copy_u8Scale);
u8 SPI_u8DataOrder(u8 Copy_u8Dataorder);
u8 SPI_u8SelectSlave(u8 Coy_u8Port, u8 Copy_u8Pin);
u8 SPI_u8ReleaseSlave(u8 Coy_u8Port, u8 Copy_u8Pin);
u8 SPI_u8SendRecData(u8 Copy_u8Data);
u8 SPI_u8RecDataSlave();
void SPI_voidInterruptEnable();
void SPI_u8SendRecDataInterrupt(u8 Copy_u8Data);
void __vector_12(void) __attribute__(( signal , used ));
#endif
