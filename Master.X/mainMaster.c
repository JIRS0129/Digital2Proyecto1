/*
 * File:   mainMaster.c
 * Author: JIRS0129
 *
 * Created on February 28, 2020, 1:25 PM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#define _XTAL_FREQ 500000

//*****************************************************************************
//Variables

//*****************************************************************************
//Prototipos
void setup(void);
void configPWM(void);
void setWidth(uint8_t time);

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    while(1){
        if(PORTAbits.RA0){
            setWidth(63);
        }else{
            setWidth(32);
        }
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    // Port configs
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    
    OSCCONbits.IRCF = 3;    // Fosc = 500kHz
    configPWM();
    TRISAbits.TRISA0 = 1;
}

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