#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#include "PORTB_INT.h"

void Interrupcion_PORTB (int pin){
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    
    switch (pin){
        case 0:
            TRISBbits.TRISB0 = 1;
            IOCBbits.IOCB0 = 1;
        case 1:
            TRISBbits.TRISB1 = 1;
            IOCBbits.IOCB1 = 1;
        case 2:
            TRISBbits.TRISB2 = 1;
            IOCBbits.IOCB2 = 1;
        case 3:
            TRISBbits.TRISB3 = 1;
            IOCBbits.IOCB3 = 1;
        case 4:
            TRISBbits.TRISB4 = 1;
            IOCBbits.IOCB4 = 1;
        case 5:
            TRISBbits.TRISB5 = 1;
            IOCBbits.IOCB5 = 1;
        case 6:
            TRISBbits.TRISB6 = 1;
            IOCBbits.IOCB6 = 1;
        case 7:
            TRISBbits.TRISB7 = 1;
            IOCBbits.IOCB7 = 1;
    }
}
