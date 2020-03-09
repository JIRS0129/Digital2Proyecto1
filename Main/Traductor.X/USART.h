/* 
 * File:   USART.h
 * Author: JIRS0129
 *
 * Created on February 12, 2020, 12:36 PM
 */

#include <stdint.h>
#include <xc.h>

#ifndef USART_H
#define	USART_H

#define _XTAL_FREQ 4000000

//Prototypes
void initUSART(uint16_t baudrate, uint8_t txint, uint8_t rcint, uint8_t syncrono);
void sendUSART (uint8_t data);

#endif	/* USART_H */

