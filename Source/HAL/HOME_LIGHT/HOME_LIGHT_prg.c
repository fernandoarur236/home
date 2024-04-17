/*
 * HOME_LIGHT_prg.c
 *
 *  Created on: 12 Jan 2023
 *      Author: 20109
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "HOME_LIGHT_int.h"
#include "HOME_LIGHT_cfg.h"

/**********************************************************************************************************
 * Description : Interface Function to initialize the Home lights
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void HOME_LIGHT_vInit(){
	DIO_vSetPinDir(HOME_LEDS_PORT, HOME_LED1_PIN, DIR_OUTPUT);
	DIO_vSetPinDir(HOME_LEDS_PORT, HOME_LED2_PIN, DIR_OUTPUT);
	DIO_vSetPinDir(HOME_LEDS_PORT, HOME_LED3_PIN, DIR_OUTPUT);
}
/**********************************************************************************************************
 * Description : Interface Function to set the status of the lights
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Use the interface MACROS
 ***********************************************************************************************************/
void HOME_LIGHT_vSetStatus(u8 A_u8Status){
	switch(A_u8Status){
		case HOME_LIGHTS_LVL1:
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED1_PIN, VAL_LOW);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED2_PIN, VAL_LOW);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED3_PIN, VAL_LOW);
			break;
		case HOME_LIGHTS_LVL2:
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED1_PIN, VAL_HIGH);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED2_PIN, VAL_LOW);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED3_PIN, VAL_LOW);
			break;
		case HOME_LIGHTS_LVL3:
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED1_PIN, VAL_HIGH);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED2_PIN, VAL_HIGH);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED3_PIN, VAL_LOW);
			break;
		case HOME_LIGHTS_LVL4:
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED1_PIN, VAL_HIGH);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED2_PIN, VAL_HIGH);
			DIO_vSetPinVal(HOME_LEDS_PORT, HOME_LED3_PIN, VAL_HIGH);
			break;
	}
}
