/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: HC-12		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 06/11/2022	 	**************/
/*********************************************************/


#ifndef HC_CFG_H_
#define HC_CFG_H_

/***********		SET pin is used to set commands	 	**************/
#define HC_SET_PIN	PIN6_ID
#define HC_SET_PORT	PORTD_ID


/* HC-12 modes
 *
 * Options:
 * 1- FU1	-> Moderate power saving mode
 * 2- FU2	-> Extreme power saving mode,
 * 3- FU3	-> Default	
 * 4- FU4	-> maximum range (1200bps)
 * */
#define HC_MODE	FU3

/* HC-12 UART baud rate
 *
 * Options:		In air baud rate
 * 1- BAUD_1200		-> 5000bps
 * 2- BAUD_2400		-> 5000bps
 * 3- BAUD_4800		-> 15,000bps 
 * 4- BAUD_9600		-> 15,000bps 
 * 5- BAUD_19200	-> 58,000bps
 * 6- BAUD_38400	-> 58,000bps
 * 7- BAUD_57600	-> 236,000bps
 * 8- BAUD_115200	-> 236,000bps
 * */
#define HC_BAUD_RATE	BAUD_9600

/* HC-12 Channel select
 *
 * Options:
 *  select a channel from C001 to C100 in form of string i.e. for channel one: "1"
 * */
#define HC_CHANNEL_SELECT	"AT+C001"

/* HC-12 Transmitting power select
 *
 * Options:
 * 1- PW_NEG_1DB
 * 2- PW_2DB
 * 3- PW_5DB
 * 4- PW_8DB
 * 5- PW_11DB
 * 6- PW_14DB
 * 7- PW_17DB
 * 8- PW_20DB
 * */
#define HC_PW_SELECT	PW_14DB

#define HC_SLEEP	"AT+SLEEP"



#endif /* HC_CFG_H_ */
