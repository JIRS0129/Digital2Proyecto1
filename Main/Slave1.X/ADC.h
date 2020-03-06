/*
 * File:   ADC.h
 * Author: JIRS0129
 *
 * Created on February 4, 2020, 8:05 AM
 */

#ifndef ADC_H
#define	ADC_H
#include <stdint.h>

unsigned char adc, adcValue = 0;    //Variables

//Prototypes
void configADC(uint8_t FOSC);
uint8_t readADC(void);
void selCanal(uint8_t channel);
void configCanal(uint8_t channel);

#endif	/* ADC_H */
