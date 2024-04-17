/*
 * BUZZ_prg.c
 *
 *  Created on: 12 Jan 2023
 *      Author: 20109
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "BUZZ_int.h"
#include "BUZZ_cfg.h"
#include <avr/delay.h>


/**********************************************************************************************************
 * Description : Interface Function to initialize the buzzer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void BUZZ_vInit(){
	DIO_vSetPinDir(BUZZ_PORT, BUZZ_PIN, DIR_OUTPUT);
}

/**********************************************************************************************************
 * Description : Interface Function to Turn on the Buzzer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void BUZZ_vTurnOn(){
	DIO_vSetPinVal(BUZZ_PORT, BUZZ_PIN, VAL_HIGH);
}

/**********************************************************************************************************
 * Description : Interface Function to Turn off the buzzer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void BUZZ_vTurnOff(){
	DIO_vSetPinVal(BUZZ_PORT, BUZZ_PIN, VAL_LOW);
}

/**********************************************************************************************************
 * Description : Interface Function to BEEP XD
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void BUZZ_vBeep(){
	BUZZ_vTurnOn();
	_delay_ms(50);
	BUZZ_vTurnOff();
	_delay_ms(50);
}
