/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: HC-12		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 06/11/2022	 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/UART/UART_int.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "HC_pri.h"
#include "HC_cfg.h"
#include "HC_int.h"
#include <string.h>
#include <avr/delay.h>

/**********************************************************************************************************
 * Description : Interface Function to initialize the HC-12 based on the configuration
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : 1-from UART data sheet do not set global interrupts before calling initialize
 * 				 2-If willing to use interrupt use HC_u8ReceiveDataAsync before this function
 ***********************************************************************************************************/
void HC_vInit(){
	DIO_vSetPinDir(HC_SET_PORT, HC_SET_PIN, DIR_OUTPUT);
	/*Energize the SET pin*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_HIGH);
	/*Initialize the UART*/
	UART_vInit(HC_BAUD_RATE);
}

/**********************************************************************************************************
 * Description : Interface Function to Configure the HC module
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Use it to configure the HC one time only before release 
 ***********************************************************************************************************/
void HC_vOneTimeConfig(){
	sendCommand(HC_MODE);
	sendCommand(HC_PW_SELECT);
	sendCommand(HC_CHANNEL_SELECT);
}

/**********************************************************************************************************
 * Description : Interface Function to put the HC-12 in sleep mode 
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Power consumption is 22uA
 ***********************************************************************************************************/
void HC_vSleep(){
	sendCommand(HC_SLEEP);
}


/**********************************************************************************************************
 * Description : Interface Function to wake up the module
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void HC_vWakeUp(){
	/*Pulling SET pin low*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_LOW);
	_delay_ms(40);

	/*Release SET pin*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_HIGH);
}

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12 Sync
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void HC_vSendData(u8 A_u8Data){
	UART_vSendCharSync(A_u8Data);
}

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12 Async
 * Outputs     : void
 * Inputs      : The function to be executed after transmission is completed
				 maybe you want to check that data is transmitted correctly 
				 Enable global interrupts	
 ***********************************************************************************************************/
void HC_vSendDataAsync(ptr_func_t ptr){
	UART_vSetCallBackTx(ptr);
}

/**********************************************************************************************************
 * Description : Interface Function to receive data async
 * Outputs     : void
 * Inputs      : the function of input u16
 * NOTES	   : Enable global interrupts before using this function
 ***********************************************************************************************************/
void HC_u8ReceiveDataAsync(ptr_func_Iu16_Ov ptr){
	UART_vSetCallBackRX(ptr);
}

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void HC_vSendString(u8 *A_u8Data){
	UART_vSendStringSync(A_u8Data);
}

/**********************************************************************************************************
 * Description : Interface Function to Receive data sync
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : 
 ***********************************************************************************************************/
u8 HC_u8ReceiveDataSync(){
	return (u8) UART_u16ReceiveDataSync();
}

/**********************************************************************************************************
 * Description : Interface Function to test the module
 * Outputs     : true/false
 * Inputs      : void
 * NOTES	   : This function after execution produces error in communication
 ***********************************************************************************************************/
u8 HC_u8Test(){
	u8 L_u8Buffer[3];		/*Used for receiving the OK from HC module*/
	u8 index = 0;
	DIO_vSetPinDir(HC_SET_PORT, HC_SET_PIN, DIR_OUTPUT);

	/*Pulling SET pin low*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_LOW);
	_delay_ms(40);

	UART_vSendStringSync(AT_COMMAND);

	do{	/*Due to HC not replying with an '\0'*/
		L_u8Buffer[index++] = UART_u16ReceiveDataSync();
	}while(index !=2);
	L_u8Buffer[2] = '\0';

	if(strcmp(L_u8Buffer, "OK"))
		return 1;
	else
		return 0;

	/*Release SET pin*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_HIGH);
}

static void sendCommand(u8 A_u8Command[]){
	/*Pulling SET pin low*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_LOW);
	_delay_ms(40);

	/*Sending the configuration ATcommands*/
	UART_vSendStringSync(A_u8Command);

	/*Release SET pin*/
	DIO_vSetPinVal(HC_SET_PORT, HC_SET_PIN, VAL_HIGH);
}
