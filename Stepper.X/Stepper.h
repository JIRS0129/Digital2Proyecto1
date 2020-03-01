/* 
 * File:   Stepper.h
 * Author: jorge
 *
 * Created on 1 de marzo de 2020, 10:28 AM
 */

#ifndef STEPPER_H
#define	STEPPER_H

#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#define clockwise 1
#define anti_clockwise 0
#define _XTAL_FREQ 500000

#ifndef in1
#define in1 RB0
#endif

#ifndef in2
#define in2 RB1
#endif

#ifndef in3
#define in3 RB2
#endif

#ifndef in4
#define in4 RB3
#endif

void wave_drive (char direction, int steps);

#endif	/* STEPPER_H */

