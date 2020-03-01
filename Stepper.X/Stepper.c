#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#include "Stepper.h"

void wave_drive (char direction, int steps){
    for (int i = 0; i <= steps; i++){
        if (direction == anti_clockwise){
            in2 = 0;
            in3 = 0;
            in4 = 0;
            in1 = 1;
            __delay_ms(2);
            in1 = 0;
            in3 = 0;
            in4 = 0;
            in2 = 1;
            __delay_ms(2);
            in1 = 0;
            in2 = 0;
            in4 = 0;
            in3 = 1;
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
            in4 = 0;
            in3 = 1;
            __delay_ms(2);
            in1 = 0;
            in3 = 0;
            in4 = 0;
            in2 = 1;
            __delay_ms(2);
            in2 = 0;
            in3 = 0;
            in4 = 0;
            in1 = 1;
            __delay_ms(2);
        }
    }
}
