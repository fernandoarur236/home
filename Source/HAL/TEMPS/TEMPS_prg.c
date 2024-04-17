/*
 * TEMPS_prg.c
 *
 *  Created on: 1 Sep 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "TEMPS_pri.h"
#include "TEMPS_cfg.h"
#include "TEMPS_int.h"



void TEMPS_vInit(){
	ADC_vInit();
}

u8 TEMPS_u8GetTemp(){
	u16 L_u16DigitalVal = ADC_u16ReadDigitalSync(TEMPS_PIN);
	return (L_u16DigitalVal * 500UL)/1023 ;
}


u8 TEMPS_ConvertValue(u16 ADC_Data)
{
	return (ADC_Data * 500UL)/1023 ;
}