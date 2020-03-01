#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#include "Stepper.h"

void wave_drive (char direction){
    if (direction == anti_clockwise){
        in1 = 1;
        in2 = 0;
        in3 = 0;
        in4 = 0;
        __delay_ms(2);
        in1 = 0;
        in2 = 1;
        in3 = 0;
        in4 = 0;
        __delay_ms(2);
        in1 = 0;
        in2 = 0;
        in3 = 1;
        in4 = 0;
        __delay_ms(2);
        in1 = 0;
        in2 = 0;
        in3 = 0;
        in4 = 1;
        __delay_ms(2);
    }
    if (direction == clockwise){
        in1 = 0;
        in2 = 0;
        in3 = 0;
        in4 = 1;
        __delay_ms(2);
        in1 = 0;
        in2 = 0;
        in3 = 1;
        in4 = 0;
        __delay_ms(2);
        in1 = 0;
        in2 = 1;
        in3 = 0;
        in4 = 0;
        __delay_ms(2);
        in1 = 1;
        in2 = 0;
        in3 = 0;
        in4 = 0;
        __delay_ms(2);
    }
}
