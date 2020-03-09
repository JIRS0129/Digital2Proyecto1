/*
 * File:   mainStepper.c
 * Author: Jorge Lorenzana
 *
 * Created on 29 de febrero de 2020, 11:44 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

#include <xc.h>
#define _XTAL_FREQ 4000000
#include "Stepper.h"
#include "PORTB_INT.h"
#include "I2C.h"

uint8_t action, z = 0;
uint8_t counter, module = 0;

void setup (void);

void __interrupt() ISR (void){
    INTCONbits.GIE = 0; //deshabilitación de interrupciones
    INTCONbits.RBIE = 0;

    if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = action;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
    
    if(INTCONbits.RBIF == 1 && PORTBbits.RB0 == 0){
        if(action == 0){
            wave_drive (clockwise, 2048);
            action = 1;
        }else if(action == 1){
            wave_drive (anti_clockwise, 2048);
            action = 0;
        }
    }
    
    INTCONbits.GIE = 1; //Reinicio de banderas y habilitación de interrupciones
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
}

void main(void) {
    setup();
    Interrupcion_PORTB (0);
    while(1){

    }
    return;
}

void setup(void){
    // Fosc = 500kHz--
    //OSCCONbits.IRCF = 3;    
    
    // Port configs
    ANSEL = 0; //Pines digitales
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    TRISB = 255;
    PORTB = 0;
    //TRISBbits.TRISB0 = 1;
    I2C_Slave_Init(0x70);
}