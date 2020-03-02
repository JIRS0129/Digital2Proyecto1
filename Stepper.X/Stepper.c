#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#include "Stepper.h"

void wave_drive (char direction, int steps){
    int count = 0;
    for (int i = 0; i <= steps; i++){
        if (direction == clockwise){
            switch (count){
                case 0:
                    in2 = 0;
                    in3 = 0;
                    in4 = 0;
                    in1 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 1:
                    in1 = 0;
                    in3 = 0;
                    in4 = 0;
                    in2 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 2:
                    in1 = 0;
                    in2 = 0;
                    in4 = 0;
                    in3 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 3:
                    in1 = 0;
                    in2 = 0;
                    in3 = 0;
                    in4 = 1;
                    __delay_ms(2);
                    count = 0;
                    break;
            }
        }
        if (direction == anti_clockwise){
            switch (count){
                case 0:
                    in2 = 0;
                    in3 = 0;
                    in1 = 0;
                    in4 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 1:
                    in1 = 0;
                    in2 = 0;
                    in4 = 0;
                    in3 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 2:
                    in1 = 0;
                    in3 = 0;
                    in4 = 0;
                    in2 = 1;
                    __delay_ms(2);
                    count += 1;
                    break;
                case 3:
                    in4 = 0;
                    in2 = 0;
                    in3 = 0;
                    in1 = 1;
                    __delay_ms(2);
                    count = 1;
                    break;
            }
        }
    }
}