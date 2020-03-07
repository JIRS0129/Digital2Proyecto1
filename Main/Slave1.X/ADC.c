#include <xc.h>
#include "ADC.h"
#include <stdint.h>


uint8_t readADC(void){  //Returns ADC's convertion
    return ADRESL;
}

void selCanal(uint8_t channel){     //Changes channel to desired one
    ADCON0bits.CHS = channel;
    return;
}

void configCanal(uint8_t channel){      //Configures everything needed for channel (config as input, analog and channel select)
    switch (channel){
        case 0:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS0 = 1;
            TRISAbits.TRISA0 = 1;
            break;
        case 1:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS1 = 1;
            TRISAbits.TRISA1 = 1;
            break;
        case 2:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS2 = 1;
            TRISAbits.TRISA2 = 1;
            break;
        case 3:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS3 = 1;
            TRISAbits.TRISA3 = 1;
            break;
        case 4:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS4 = 1;
            TRISAbits.TRISA5 = 1;
            break;
        case 5:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS5 = 1;
            TRISEbits.TRISE0 = 1;
            break;
        case 6:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS6 = 1;
            TRISEbits.TRISE1 = 1;
            break;
        case 7:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 0;
            ANSELbits.ANS7 = 1;
            TRISEbits.TRISE2 = 1;
            break;
        case 8:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS8 = 1;
            TRISBbits.TRISB2 = 1;
            break;
        case 9:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS9 = 1;
            TRISBbits.TRISB3 = 1;
            break;
        case 10:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS10 = 1;
            TRISBbits.TRISB1 = 1;
            break;
        case 11:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS11 = 1;
            TRISBbits.TRISB4 = 1;
            break;
        case 12:
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS12 = 1;
            TRISBbits.TRISB0 = 1;
            break;
        case 13:
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS3 = 1;
            ANSELHbits.ANS13 = 1;
            TRISBbits.TRISB5 = 1;
            break;
    }
    return;
}

void configADC(uint8_t FOSC){       //Configures everything needed for ADC interrupts
    //ADC
    INTCONbits.PEIE=1;  //Enable peripherial interrupts
    PIE1bits.ADIE = 1;  //Enables ADC interrupts
    PIR1bits.ADIF=0; // Clear ADC flag
    ADCON1bits.ADFM=1; // Left Justification
    ADCON1bits.VCFG1=0; // Ref
    ADCON1bits.VCFG0=0; // Ref
    ADCON0bits.ADON=1;  //Activate ADC

    switch (FOSC){  //Selects ADC convertion's frequency
        case 0:
            ADCON0bits.ADCS1=0;//
            ADCON0bits.ADCS0=0;// Fosc/2
            break;
        case 1:
            ADCON0bits.ADCS1=0;//
            ADCON0bits.ADCS0=1;// Fosc/8
            break;
        case 2:
            ADCON0bits.ADCS1=1;//
            ADCON0bits.ADCS0=0;// Fosc/32
            break;
        case 3:
            ADCON0bits.ADCS1=1;//
            ADCON0bits.ADCS0=1;// Frc
            break;
    }
    
    ADCON0bits.GO_DONE=1;   //Starts convertion
    INTCONbits.GIE = 1;     //Enables global interrupts
    return;
}

