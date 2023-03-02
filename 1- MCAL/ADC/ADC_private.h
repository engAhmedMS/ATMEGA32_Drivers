/****************************************************************/
/*   Author             :    Ahmed Atia Atia 				    */
/*	 Date 				:    2 May 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    contain the Memory mapped of		*/	
/*							 [MCUCR,MCUCSR,GICR,GIFR] Registers */
/****************************************************************/


/****************************************************************/
/* Description   : Guard to protect this File from include more */
/*                 than one time .                              */
/****************************************************************/

#ifndef _ADC_PRIV_H
#define _ADC_PRIV_H


/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of ADCSRA    	*/
/**			   Register	is  0X26						    	*/
/****************************************************************/
/**			   ADCSRA : MCU Control Register contains control	*/
/** 		   bits for interrupt sense control and general 	*/
/**            MCU functions.							    	*/
/****************************************************************/

#define ADCSRA		*((volatile u8 * ) (0X26))
#define	ADCSRA_ADEN		7
#define	ADCSRA_ADSC		6
#define	ADCSRA_ADATE	5
#define	ADCSRA_ADIF		4
#define	ADCSRA_ADIE		3
#define	ADCSRA_ADPS2	2
#define	ADCSRA_ADPS1	1
#define	ADCSRA_ADPS0	0
/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of MCUCSR   	*/
/**			   Register	is  0X54.								*/
/****************************************************************/
/**			   MCUCSR : MCU Control and Status Register			*/
/****************************************************************/

#define ADMUX       *((volatile u8 * ) (0X27))
#define ADMUX_REFS1		7
#define ADMUX_REFS0		6
#define ADMUX_ADLAR		5
#define ADMUX_MUX4		4
#define ADMUX_MUX3		3
#define ADMUX_MUX2		2
#define ADMUX_MUX1		1
#define ADMUX_MUX0		0
/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of GICR     	*/
/**			   Register	is  0X5B.								*/
/****************************************************************/
/**			   GICR : General Interrupt Control Register		*/
/****************************************************************/

#define ADCL        *((volatile u8 * ) (0X24))


/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of GIFR     	*/
/**			   Register	is  0X5A.						    	*/
/****************************************************************/
/**			   GIFR : General Interrupt Flag Register			*/
/****************************************************************/

#define ADCH        *((volatile u8 * ) (0X25))

#define SFIOR       *((volatile u8 * ) (0X50))
#define SFIOR_ADTS2			7
#define SFIOR_ADTS1			6
#define SFIOR_ADTS0			5
#define SFIOR_RESERVED		4
#define SFIOR_ACME			3
#define SFIOR_PUD			2
#define SFIOR_PSR2			1
#define SFIOR_PSR10			0












#endif	/**!comment : End of the guard [_ADC_PRIV_H]		   **/
