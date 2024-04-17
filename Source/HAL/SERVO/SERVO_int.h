/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: SERVO		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 19 Sep 2022	 	**************/
/*********************************************************/

#ifndef HAL_SERVO_SERVO_INT_H_
#define HAL_SERVO_SERVO_INT_H_


typedef enum {
	SERVO_ANGLE_45,
	SERVO_ANGLE_90,
	SERVO_ANGLE_135,
	SERVO_ANGLE_180
};

#define STATE_0		0
#define STATE_180	1

/**********************************************************************************************************
 * Description : Interface Function to setup the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : must configure timer_1 in fast PWM mode with ICR1 TOP (mode 14) of value 19999
 ***********************************************************************************************************/
void SERVO_vInit();

/**********************************************************************************************************
 * Description : Interface Function to turn ON the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void SERVO_vTurnOn();

/**********************************************************************************************************
 * Description : Interface Function to turn OFF the Servo_Motor
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void SERVO_vTurnOff();

/**********************************************************************************************************
 * Description : Interface Function to set the angle of Servo_Motor
 * Outputs     : void
 * Inputs      : the required angle
 * NOTES	   : any given angle within 0 - 180 will work just fine. this will work only in TIMER_1 fast PWM
 * 				 with TOP ICR1 of 19999
 ***********************************************************************************************************/
void SERVO_vSetAngle(u8 A_u8Angle);



void SERVO_vSetState(u8 A_u8State);

#endif /* HAL_SERVO_SERVO_INT_H_ */
