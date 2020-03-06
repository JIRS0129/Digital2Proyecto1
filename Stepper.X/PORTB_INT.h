/* 
 * File:   PORTB_INT.h
 * Author: jorge
 *
 * Created on 6 de marzo de 2020, 02:48 PM
 */

#ifndef PORTB_INT_H
#define	PORTB_INT_H
#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#define _XTAL_FREQ 4000000

void Interrupcion_PORTB (int pin);

#endif	/* PORTB_INT_H */

