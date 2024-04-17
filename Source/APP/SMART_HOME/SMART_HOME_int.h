/*********************************************************/
/***********		Author: Smart Home	 	**************/
/***********		Layer: APP			 	**************/
/***********		Component: APPSYS  		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 28 Dec 2022	 	**************/
/***********		Updated: 28 Sep 2022	**************/
/*********************************************************/

#ifndef APP_SMART_HOME_SMART_HOME_INT_H_
#define APP_SMART_HOME_SMART_HOME_INT_H_



/******************************************************************************
* \Syntax          : void System_Start(void)
* \Description     : Initializing and preparing the system for the first time
*******************************************************************************/
void SMART_HOME_vInit();


/******************************************************************************
* \Syntax          : void System_WakeUp(void)        
* \Description     : Waking the system-up and doing its functions
*******************************************************************************/
void SMART_HOME_vUpdate();



#endif /* APP_SMART_HOME_SMART_HOME_INT_H_ */
