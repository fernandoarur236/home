/*
 * LDR_prg.c
 *
 *  Created on: 12 Sep 2022
 *      Author: 20109
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LDR_cfg.h"
#include "LDR_int.h"

void LDR_vInit(){
	
	ADC_vInit();
}

/*LDR resistance decreases by increasing the light intensity*/
u16 LDR_u16GetValue(){
	u16 L_u8DigitalVal = ADC_u16ReadDigitalSync(LDR_CHANNEL);

	u32 L_u8AnalogVal = ( (L_u8DigitalVal * 5000UL) / 1023 ); /*in mV*/
	/* EQN: LDR = R * (VCC/AnalogVal - 1). R is connected to 5K*/
	return ( (1000UL * L_u8AnalogVal) / (5000UL - L_u8AnalogVal) ) ;
}


u16 LDR_ConvertValue(u16 ADC_Data)
{
	u32 L_u8AnalogVal = ( (ADC_Data * 5000UL) / 1023 ); /*in mV*/
	/* EQN: LDR = R * (VCC/AnalogVal - 1). R is connected to 5K*/
	return ( (1000UL * L_u8AnalogVal) / (5000UL - L_u8AnalogVal) ) ;
}
