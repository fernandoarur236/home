/*
 * ADC_cfg.h
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_ADC_ADC_CFG_H_
#define MCAL_ADC_ADC_CFG_H_

/*ADC port in ATmega 32*/
#define ADC_PORT PORTA_ID
/*ADC channels pins*/
#define ADC0_PIN PIN0_ID
#define ADC1_PIN PIN1_ID
#define ADC2_PIN PIN2_ID
#define ADC3_PIN PIN3_ID
#define ADC4_PIN PIN4_ID
#define ADC5_PIN PIN5_ID
#define ADC6_PIN PIN6_ID
#define ADC7_PIN PIN7_ID

/* mode of PreScale
 * Options:
 * 1- PRE_SCALE_2
 * 2- PRE_SCALE_4
 * 3- PRE_SCALE_8
 * 4- PRE_SCALE_16
 * 5- PRE_SCALE_32
 * 6- PRE_SCALE_64
 * 7- PRE_SCALE_128
 * */
#define ADC_PRE_SCALE   PRE_SCALE_128 /*Must get to 50-200kHZ*/

/* Vref selection
 * Options:
 * 1-ADC_AVCC
 * 2-ADC_Internal
 * */
#define ADC_VREF_SELECT ADC_AVCC

/* Adjust ADC
 * options:
 * 1- LEFT_ADJUST
 * 2- RIGH_ADJUST
 *
 * */
#define ADC_ADJUST RIGHT_ADJUST

/*some limitations of IMTschool kit*/
/*we always use right adjust for the ADCL & ADCH, ADLAR=0*/
/*Vref is always connected AVCC: */


#endif /* MCAL_ADC_ADC_CFG_H_ */
