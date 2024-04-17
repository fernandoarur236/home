/*
 * DCmotor_prg.c
 *
 *  Created on: 25 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIM1/TIM1_int.h"
#include "DCM_cfg.h"
#include "DCM_int.h"

void DCM_vInit(){
	//DIO_vSetPinDir(IN1_PORT, IN1_PIN, DIR_OUTPUT);
	//DIO_vSetPinDir(IN2_PORT, IN2_PIN, DIR_OUTPUT);
	TIM1_vInit();
	TIM1_vSetIcr1Val((u16)65530);
	TIM1_vSetDutyCycleOC1B(TIMER_DUTY_CYCLE_25);
}
void DCM_vTurnOn(){
	//DIO_vSetPinVal(IN1_PORT, IN1_PIN, VAL_HIGH);
	//DIO_vSetPinVal(IN2_PORT, IN2_PIN, VAL_LOW);
	TIM1_vOcr1bOn();
	TIM1_vTurnOn();
}
void DCM_vTurnOff(){
	//DIO_vSetPinVal(IN1_PORT, IN1_PIN, VAL_LOW);
	//DIO_vSetPinVal(IN2_PORT, IN2_PIN, VAL_LOW);
	TIM1_vTurnOff();
	TIM1_vOcr1bOff();
	DIO_vSetPinVal(PORTD_ID, PIN4_ID, VAL_LOW);
}
void DCM_vSetDirection(u8 A_u8Dir){
	switch(A_u8Dir) {
		case DCM_CLK_WISE:
			DIO_vSetPinVal(IN1_PORT, IN1_PIN, VAL_HIGH);
			DIO_vSetPinVal(IN2_PORT, IN2_PIN, VAL_LOW);
			break;
		case DCM_ANTI_CLK_WISE:
			DIO_vSetPinVal(IN1_PORT, IN1_PIN, VAL_LOW);
			DIO_vSetPinVal(IN2_PORT, IN2_PIN, VAL_HIGH);
			break;
	}
}
void DCM_vSetPWM(s8 A_u8PWM){
	if(A_u8PWM <= 100)
		TIM1_vSetDutyCycleOC1B(A_u8PWM);
}
