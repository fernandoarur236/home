/*
 * ADC_pri.h
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_ADC_ADC_PRI_H_
#define MCAL_ADC_ADC_PRI_H_

/*Available pre-scale*/
#define PRE_SCALE_2   1
#define PRE_SCALE_4   2
#define PRE_SCALE_8   3
#define PRE_SCALE_16  4
#define PRE_SCALE_32  5
#define PRE_SCALE_64  6
#define PRE_SCALE_128 7

#define		 ADC_PRESCALE_BIT_MASK	0b11111000
#define     _ADC_CHANNEL_MASK		0b11100000

/*Vref select. 2 is reserved by the MCU*/
#define ADC_AVCC     1
#define ADC_Internal 3

#define LEFT_ADJUST  1
#define RIGHT_ADJUST 0

/*ISR for ADC. the vector number is 2*/
/*signal attribute means nesting is disabled. */
void __vector_16 (void) __attribute__((signal));

/*ISR variable*/
static ptr_func_t G_ISR_ADC = ADDRESS_NULL;
static ptr_func_t ISR_ADCCHAINPTR;

/* ISR Conversion Mode */
#define     _ADC_ISR_SINGLECONVERSION       200
#define     _ADC_ISR_MULTICONVERSION        201

#endif /* MCAL_ADC_ADC_PRI_H_ */
