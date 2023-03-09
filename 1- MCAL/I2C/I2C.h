#ifndef I2C_H_
#define I2C_H_


typedef enum
{
	NO_ERROR, START_CONDITION_ERROR,
	REPEATED_START_CONDITION_ERROR,
	SLAVE_ADDRESS_WITH_WRITE_ERROR,
	SLAVE_ADDRESS_WITH_READ_ERROR,
	MASTER_WRITE_BYTE_ERROR,
	MASTER_READ_BYTE_WITH_ACK_ERROR,
	MASTER_READ_BYTE_WITH_NACK_ERROR,
	STOP_CONDITION_ERROR
}I2C_ERROR;



void I2C_MasterInit(u8 Copy_u8Address);
void I2C_SlaveInit(u8 Copy_u8Address);
I2C_ERROR I2C_StartCondition();
void I2C_StopCondition();
I2C_ERROR I2C_RepeatedStartCondition();
I2C_ERROR I2C_Send_SlaveAddressWriteOperation(u8 Copy_u8Address);
I2C_ERROR I2C_Send_SlaveAddressReadOperation(u8 Copy_u8Address);
I2C_ERROR I2C_WriteByte(u8 Copy_u8DataByte);
I2C_ERROR I2C_ReadByte(u8* Copy_pu8DataByte);



#endif
