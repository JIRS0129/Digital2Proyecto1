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
#include <xc.h>
#include "LCD.h"
#include <math.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

uint8_t adc, entero1, dec1, counter;
uint8_t entero2, dec2;
float sensorF1, float1;
float sensorF2, float2;
uint8_t toggle, s3 = 0;
float lux;

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    while(1){
        
        
        
        I2C_Master_Start();
        I2C_Master_Write(0x69);
        if(toggle%2){
            adc = I2C_Master_Read(0);
        }else{
            counter = I2C_Master_Read(0);
        }
        toggle++;
        I2C_Master_Stop();
        __delay_ms(10); 
        
        
        setCursorLCD(2, 15);
        writeIntLCD(adc);
        writeStrLCD("  ");
        //Potentiometer's processing
        sensorF1 = (float) (adc-20) * 3.04; //Conversion from 0 to 5V
        entero1 = (int) sensorF1;           //Takes only the integer from convertion
        float1 = (sensorF1 - entero1)*100;  //Subtraction and multiplication to leave the 2 decimals as integers
        dec1 = (int) float1;                //Takes the integer (which is the 2 decimals from convertion)
        
        writeFloat(entero1, dec1, 1);       //Writes first number starting from position 1
        setCursorLCD(2, 9);
        writeIntLCD(counter);
        writeCharLCD(' ');
        //writeFloat(entero2, dec2, 13);       //Writes first number starting from position 1
        writeStrLCD("  ");
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
    
    initLCD();
    clcLCD();
    
    //Write first row that won't be modified
    setCursorLCD(1, 1);
    writeStrLCD("S1");
    setCursorLCD(1, 7);
    writeStrLCD("S2");
    setCursorLCD(1, 13);
    writeStrLCD("S3");
}