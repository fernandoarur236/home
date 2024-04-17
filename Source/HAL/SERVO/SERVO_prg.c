/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: SERVO		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 19 Sep 2022	 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/TIM2/TIM2_int.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "SERVO_cfg.h"
#include "SERVO_int.h"
#include "SERVO_pri.h"



/**********************************************************************************************************
 * Description : Interface Function to setup the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : must configure timer_1 in fast PWM mode with ICR1 TOP (mode 14) of value 19999
 ***********************************************************************************************************/

void SERVO_vInit(){
	TIM2_vInit();
	DIO_vSetPinDir(SERVO_PORT, SERVO_PIN, DIR_OUTPUT);
	TIM2_vCallBack_OVF2(&stateHandler);
}

/**********************************************************************************************************
 * Description : Interface Function to turn ON the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/

void SERVO_vTurnOn(){
	TIM2_vTurnOn();
}

/**********************************************************************************************************
 * Description : Interface Function to turn OFF the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void SERVO_vTurnOff(){
	TIM2_vTurnOff();
}

/**********************************************************************************************************
 * Description : Interface Function to set the angle of Servo_Motor
 * Outputs     : void
 * Inputs      : the required angle
 * NOTES	   : any given angle within 0 - 180 will work just fine. this will work only in TIMER_1 fast PWM
 * 				 with TOP ICR1 of 19999
 ***********************************************************************************************************/
void SERVO_vSetAngle(u8 A_u8Angle){
	u16 L_u8CompareVal = 750; /*Default is zer0*/
	if(A_u8Angle < 180)
		L_u8CompareVal = SERVO_ANGLE_EQN ;

	//TIM1_vSetIcr1Val(L_u8CompareVal);
}

static void stateHandler(){
	static u8 G_u8ISRcounter = 0;
	G_u8ISRcounter ++;
	if(G_u8ISRcounter == G_u8OvfCounts){	/*End of High Pulse*/
		DIO_vSetPinVal(SERVO_PORT, SERVO_PIN, VAL_LOW);
		TIM2_vSetPreload(224 - G_u8CurrentOVf);		/*Preload for the whole period (20ms)
													  subtracting the starting preload for each state*/
	}
	if(G_u8ISRcounter == MAX_OVF){							/*End of 20ms period*/
		DIO_vSetPinVal(SERVO_PORT, SERVO_PIN, VAL_HIGH);	/*Starting of high pulse*/
		TIM2_vSetPreload(G_u8CurrentOVf);					/*Starting with the needed preload for each state*/
		G_u8ISRcounter = 0;									/*Resetting the counter*/
	}
}


/**********************************************************************************************************
 * Description : Interface Function to set the state of the SERVO motor 0 or 180 degree
 * Outputs     : void
 * Inputs      : the required state
 * NOTES	   : Enable TIMER2 in OVF mode with interrupt enable and prescaler-8
 ***********************************************************************************************************/
void SERVO_vSetState(u8 A_u8State){
	switch(A_u8State){
		case STATE_0:	/*Case 0 degree*/
			G_u8CurrentOVf = 18;
			TIM2_vSetPreload(G_u8CurrentOVf);
			G_u8OvfCounts = 2;
			break;
		case STATE_180:	/*Case 180 degree*/
			G_u8CurrentOVf = 60;
			TIM2_vSetPreload(G_u8CurrentOVf);
			G_u8OvfCounts = 9;
			break;
		default:
			break;
	}
}
