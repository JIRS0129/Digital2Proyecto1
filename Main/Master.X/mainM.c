/*
 * File:   mainM.c
 * Author: JIRS0129
 *
 * Created on February 21, 2020, 9:46 AM
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
#include "I2C.h"
#include "LCD.h"
#include "ADC.h"
#include "USART.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

uint8_t adcT, adc, entero1, dec1, alarm, hall;
uint8_t entero2, dec2;
float sensorF1, float1;
float sensorF2, float2;
uint8_t toggle, s3, count = 0;
uint8_t toggle2, count2, adcP, signal, mov = 0;
uint8_t toggle3, count3, ir, garage = 0;
uint8_t antibounce, antibounce2, screenCounter, screenState = 0;
uint8_t receiveUSART;

//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
    if(ADCON0bits.GO_DONE == 0){   //If ADC interrupt
        adc = readADC();                    //Activate flag
        PIR1bits.ADIF = 0;          //Clear ADC flag
    }
    
    if(PIR1bits.RCIF == 1){         //If data received by USART
        PORTAbits.RA0 = 1;
        receiveUSART = RCREG;      //Read
    }
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    while(1){
        if(ADCON0bits.GO_DONE == 0){
           ADCON0bits.GO_DONE = 1; 
        }
        
        count = toggle%3;
        I2C_Master_Start();
        I2C_Master_Write(0x69);
        if(count == 0){
            adcT = I2C_Master_Read(0);
        }else if(count == 1){
            alarm = I2C_Master_Read(0);
        }else if(count == 2){
            hall = I2C_Master_Read(0);
        }
        toggle++;
        I2C_Master_Stop();
        __delay_ms(10); 
        
        
        count2 = toggle2%3;
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        if(count2 == 0){
            signal = I2C_Master_Read(0);
        }else if(count2 == 1){
            adcP = I2C_Master_Read(0);
        }else if(count2 == 2){
            mov = I2C_Master_Read(0);
        }
        toggle2++;
        I2C_Master_Stop();
        __delay_ms(10); 
        
        
        count3 = toggle3%2;
        I2C_Master_Start();
        I2C_Master_Write(0x71);
        if(count3 == 0){
            ir = I2C_Master_Read(0);
        }else if(count3 == 1){
            garage = I2C_Master_Read(0);
        }
        toggle3++;
        I2C_Master_Stop();
        __delay_ms(10); 
        
        
        //Potentiometer's processing
        sensorF1 = (float) adcT * 5/255; //Conversion from 0 to 5V
        sensorF2 = (float) sensorF1/0.01;
        entero1 = (int) sensorF2;           //Takes only the integer from convertion
        float1 = (sensorF2 - entero1)*100;  //Subtraction and multiplication to leave the 2 decimals as integers
        dec1 = (int) float1;                //Takes the integer (which is the 2 decimals from convertion)
        
        
        if(PORTAbits.RA1){
            antibounce = 1;
        }
        if(PORTAbits.RA1 == 0 && antibounce){
            screenCounter++;
            screenCounter = screenCounter%3;
            antibounce = 0;
        }
        
        
        if(PORTAbits.RA2){
            antibounce2 = 1;
        }
        if(PORTAbits.RA2 == 0 && antibounce2){
            screenState++;
            screenState = screenState%2;
            antibounce2 = 0;
        }
        
        if(signal){
            PORTAbits.RA0 = 1;
        }else{
            PORTAbits.RA0 = 0;
        }
        
        if(entero1 >= 60){
            PORTAbits.RA4 = 1;
        }else{
            PORTAbits.RA4 = 0;
        }
        
        
        if(receiveUSART==0){
            sendUSART(signal);
        }else if(receiveUSART==1){
            sendUSART(PORTAbits.RA4);
        }else if(receiveUSART==2){
            sendUSART(garage);
        }else if(receiveUSART==3){
            sendUSART(hall);
        }else if(receiveUSART==4){
            sendUSART(entero1);
        }else if(receiveUSART==5){
            sendUSART((uint8_t) adcP*100/255);
        }else if(receiveUSART==6){
            sendUSART(mov);
        }else if(receiveUSART==7){
            sendUSART(alarm);
        }
        
        
        
        
        if(screenState == 0){
            setCursorLCD(1, 1);
            if(screenCounter == 0){
                writeStrLCD("TEMP ");
                writeIntLCD(entero1);
                writeCharLCD('°');
                writeCharLCD('C');
            }else if(screenCounter == 1){
                writeStrLCD("LUZ ");
                writeIntLCD((uint8_t) adcP*100/255);
                writeCharLCD(' ');
                writeCharLCD('%');
            }
            writeStrLCD("           ");
            
            
            setCursorLCD(2, 1);
            if(screenCounter == 0){
                writeStrLCD("PUERTA ");
                if(hall){
                    writeStrLCD("ABIERTA");
                }else{
                    writeStrLCD("CERRADA");
                }
                writeCharLCD(' ');
            }else if(screenCounter == 1){
                if(mov){
                    writeStrLCD("MOVIMIENTO");
                }else{
                    writeStrLCD("SIN MOVIMIENTO");
                }
            }else if(screenCounter == 2){
                if(garage){
                    writeStrLCD("GARAGE ABIERTO");
                }else{
                    writeStrLCD("GARAGE CERRADO");
                }
            }
            writeStrLCD("           ");
        }else{
            setCursorLCD(1, 1);
            if(screenCounter == 0){
                writeStrLCD("PUERTA ");
                if(hall){
                    writeStrLCD("ABIERTA");
                }else{
                    writeStrLCD("CERRADA");
                }
                writeCharLCD(' ');
            }else if(screenCounter == 1){
                if(mov){
                    writeStrLCD("MOVIMIENTO");
                }else{
                    writeStrLCD("SIN MOVIMIENTO");
                }
            }
            setCursorLCD(2, 1);
            if(screenCounter == 0){
                writeStrLCD("ALARMA ");
                if(alarm){
                    writeStrLCD("ACTIVA");
                }else{
                    writeStrLCD("DESCATIVADA");
                }
                writeCharLCD(' ');
            }else if(screenCounter == 1){
                if(signal){
                    writeStrLCD("PUERTA ABIERTA");
                }else{
                    writeStrLCD("PUERTA CERRADA");
                }
            }else if(screenCounter == 2){
                if(garage){
                    writeStrLCD("GARAGE ABIERTO");
                }else{
                    writeStrLCD("GARAGE CERRADO");
                }
            }
        }
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    //Configs
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    
    initUSART(9600, 1, 1, 0);
    
    initLCD();
    clcLCD();
    
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
}