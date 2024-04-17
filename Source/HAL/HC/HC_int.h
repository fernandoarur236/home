/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: HC-12		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 06/11/2022	 	**************/
/*********************************************************/


#ifndef HC_INT_H_
#define HC_INT_H_

/**********************************************************************************************************
 * Description : Interface Function to initialize the HC-12 based on the configuration
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : from UART data sheet do not set global interrupts before calling initialize
 ***********************************************************************************************************/
void HC_vInit();

/**********************************************************************************************************
 * Description : Interface Function to Configure the HC module
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Use it to configure the HC one time only before release 
 ***********************************************************************************************************/
void HC_vOneTimeConfig();

/**********************************************************************************************************
 * Description : Interface Function to put the HC-12 in sleep mode 
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Power consumption is 22uA
 ***********************************************************************************************************/
void HC_vSleep();

/**********************************************************************************************************
 * Description : Interface Function to wake up the module
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void HC_vWakeUp();

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void HC_vSendData(u8 A_u8Data);

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void HC_vSendString(u8 *A_u8Data);

/**********************************************************************************************************
 * Description : Interface Function to receive data async
 * Outputs     : void
 * Inputs      : the function of input u16
 * NOTES	   : Enable global interrupts before using this function
 ***********************************************************************************************************/
void HC_u8ReceiveDataAsync(ptr_func_Iu16_Ov ptr);

/**********************************************************************************************************
 * Description : Interface Function to Receive data sync
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : 
 ***********************************************************************************************************/
u8 HC_u8ReceiveDataSync();

/**********************************************************************************************************
 * Description : Interface Function to send data through HC-12 Async
 * Outputs     : void
 * Inputs      : The function to be executed after transmission is completed
				 maybe you want to check that data is transmitted correctly 
				 Enable global interrupts	
 ***********************************************************************************************************/
void HC_vSendDataAsync(ptr_func_t ptr);


/**********************************************************************************************************
 * Description : Interface Function to test the module
 * Outputs     : true/false
 * Inputs      : void
 ***********************************************************************************************************/
u8 HC_u8Test();

#endif /* HC_INT_H_ */
