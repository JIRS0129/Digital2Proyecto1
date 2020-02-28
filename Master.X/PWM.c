#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "PWM.h"

void configPWM(void){
    // Set PWM period to 20ms
    TRISCbits.TRISC1 = 1;
    PR2 = 156;
    CCP2CONbits.CCP2M = 12;
    setWidth(63);
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 3;
    T2CONbits.TMR2ON = 1;
    while(!PIR1bits.TMR2IF){}
    TRISCbits.TRISC1 = 0;
}

void setWidth(uint8_t time){
    if(time & 0b00000001){
        CCP2CONbits.DC2B0 = 1;
    }else{
        CCP2CONbits.DC2B0 = 0;
    }
    if(time & 0b00000010){
        CCP2CONbits.DC2B1 = 1;
    }else{
        CCP2CONbits.DC2B1 = 0;
    }
    time = time & 0b11111100;
    time = time/4;
    CCPR2L = time;
}
