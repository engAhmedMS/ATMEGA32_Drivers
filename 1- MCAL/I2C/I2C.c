#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "I2C.h"
#include "I2C_REGISTERS.h"
#include "I2C_PRIVATE.h"

static u8 I2C_ReadStatus(void);

// pass 0 if master will not be addressed
void I2C_MasterInit(u8 Copy_u8Address)
{
	//Set CLK freq to 400KHz
	TWBR = 2;
	CLEAR_BIT(TWSR, TWSR_TWPS0);
	CLEAR_BIT(TWSR, TWSR_TWPS1);

	//Set Address
	if(Copy_u8Address!=0)
	{
		TWAR |= Copy_u8Address<<1;
	}

	//enable Acknowledge
	SET_BIT(TWCR, TWCR_TWEA);

	//enable I2C
	SET_BIT(TWCR, TWCR_TWEN);
}

void I2C_SlaveInit(u8 Copy_u8Address)
{
	//Set Address
	TWAR |= Copy_u8Address<<1;

	//enable Acknowledge
	SET_BIT(TWCR, TWCR_TWEA);

	//enable I2C
	SET_BIT(TWCR, TWCR_TWEN);

}

I2C_ERROR I2C_StartCondition()
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;
	//Send Start Condition
	SET_BIT(TWCR, TWCR_TWSTA);

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != START_ACK)
	{
		Local_Error = START_CONDITION_ERROR;
	}
	//Clear Start Condition
	CLEAR_BIT(TWCR, TWCR_TWSTA);

	return Local_Error;
}

I2C_ERROR I2C_RepeatedStartCondition()
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;
	//Send Start Condition
	SET_BIT(TWCR, TWCR_TWSTA);

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != REP_START_ACK)
	{
		Local_Error = REPEATED_START_CONDITION_ERROR;
	}
	//Clear Start Condition
	CLEAR_BIT(TWCR, TWCR_TWSTA);

	return Local_Error;
}

I2C_ERROR I2C_Send_SlaveAddressWriteOperation(u8 Copy_u8Address)
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;
	//write slave address in the 7 MSBs
	TWDR = Copy_u8Address<<1;
	//CLR TWD0 (R/W') to choose write operation
	CLEAR_BIT(TWDR, TWDR_TWD0);

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error = SLAVE_ADDRESS_WITH_WRITE_ERROR;
	}

	return Local_Error;
}

I2C_ERROR I2C_Send_SlaveAddressReadOperation(u8 Copy_u8Address)
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;
	//write slave address in the 7 MSBs
	TWDR = Copy_u8Address<<1;
	//SET TWD0 (R/W') to choose READ operation
	SET_BIT(TWDR, TWDR_TWD0);

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error = SLAVE_ADDRESS_WITH_READ_ERROR;
	}

	return Local_Error;
}

I2C_ERROR I2C_WriteByte(u8 Copy_u8DataByte)
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;
	// write data byte to TWDR
	TWDR = Copy_u8DataByte;

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != MSTR_WR_BYTE_ACK)
	{
		Local_Error = MASTER_WRITE_BYTE_ERROR;
	}

	return Local_Error;
}

I2C_ERROR I2C_ReadByte(u8* Copy_pu8DataByte)
{
	I2C_ERROR Local_Error = NO_ERROR;
	u8 status = 0;

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

	//wait the flag to be raised again to ensure that operation is done
	while(CHECK_BIT(TWCR, TWCR_I2CNT));

	//check status
	status = (TWSR>>3)<<3;
	if(status != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_Error = MASTER_READ_BYTE_WITH_ACK_ERROR;
	}
	else if(status != MSTR_RD_BYTE_WITH_NACK)
	{
		Local_Error = MASTER_READ_BYTE_WITH_NACK_ERROR;
	}
	else
	{
		// read data byte from TWDR
		*Copy_pu8DataByte = TWDR;
	}



	return Local_Error;
}

void I2C_StopCondition()
{
	//Send Stop Condition
	SET_BIT(TWCR, TWCR_TWSTO);

	//clear flag to start prev operation (it is cleared by writing logic 1 to it)
	SET_BIT(TWCR, TWCR_I2CNT);

}


static u8 I2C_ReadStatus(void)
{
	return (TWSR>>3)<<3;;
}
