/* 
 * File:   PWM.h
 * Author: JIRS0129
 *
 * Created on February 28, 2020, 4:12 PM
 */

#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>

#define _XTAL_FREQ 500000

#ifndef PWM_H
#define	PWM_H

void configPWM(void);
void setWidth(uint8_t time);

#endif	/* PWM_H */