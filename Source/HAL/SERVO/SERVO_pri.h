/*
 * SERVO_pri.h
 *
 * Created: 28/12/2022 10:55:08 PM
 *  Author: 20109
 */ 


#ifndef SERVO_PRI_H_
#define SERVO_PRI_H_

#define MAX_OVF 78

static u8 G_u8OvfCounts = 0;
static u8 G_u8State = STATE_0;
static u8 G_u8CurrentOVf = 0;

static void stateHandler();



#endif /* SERVO_PRI_H_ */
