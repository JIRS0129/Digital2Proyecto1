/*
 * File:   HeaderSensorMovFoto.c
 * Author: Grupo Nachito
 * _Jesús_
 * Created on 01 de marzo de 2020, 00:01 AM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

//------------------------------------------------------------------------------
//DEFINICION DE VARIABLES
unsigned char VarMOV = 0;
unsigned char debounce = 0;

float adc1 = 0;
float adc2 = 0;
float adc3 = 0;
float adc4 = 0;
unsigned int adc5 = 0;
unsigned int adc6 = 0;
float ValorADC = 0;

unsigned char ADCcomp1 = 0b11110000;
unsigned char ADCcomp2 = 0b00001111;
unsigned char mostrar = 0;
unsigned char multi1 = 0;
unsigned char multi2 = 0;
unsigned char timer = 0;
unsigned char contador = 0;

unsigned char voltajeunidad = 0;
unsigned char decimal1 = 0;
unsigned char decimal2 = 0;

unsigned char Signal2 = 0;

//----------------------------------------------------------------------------
//IDENTIFICACION DE FUNCIONES
void ADC(void);
void ADC_ChannelSelect(uint8_t);
void LeerADC(void);

void lcd_cmd(unsigned char varLCD);      //----Function to Send Command to LCD
void lcd_dwr(unsigned char varLCD);      //----Function to Send Data to LCD
void lcd_msg(unsigned char *c);     //----Function to Send String of Data to LCD
void lcd_lat(void);                     //----Function to Latch data into LCD
void lcd_ready(void);                   //----Function to Check LCD is Bus
void lcd_init(void);                    //----Initialization of LCD
void cmd(char a);
void cursor(char a, char b);
void lcdinit(void);
void WriteChar(char a);
void WriteString(char *a);
void string(uint8_t entero);

void USART (void);
void transmitirUSART(unsigned char a);

//*****************************************************************************
// Función para inicializar I2C Maestro
//*****************************************************************************
void I2C_Master_Init(const unsigned long c);
//*****************************************************************************
// Función de espera: mientras se esté iniciada una comunicación,
// esté habilitado una recepción, esté habilitado una parada
// esté habilitado un reinicio de la comunicación, esté iniciada
// una comunicación o se este transmitiendo, el IC2 PIC se esperará
// antes de realizar algún trabajo
//*****************************************************************************
void I2C_Master_Wait(void);
//*****************************************************************************
// Función de inicio de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_Start(void);
//*****************************************************************************
// Función de reinicio de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_RepeatedStart(void);
//*****************************************************************************
// Función de parada de la comunicación I2C PIC
//*****************************************************************************
void I2C_Master_Stop(void);
//*****************************************************************************
//Función de transmisión de datos del maestro al esclavo
//esta función devolverá un 0 si el esclavo a recibido
//el dato
//*****************************************************************************
void I2C_Master_Write(unsigned d);
//*****************************************************************************
//Función de recepción de datos enviados por el esclavo al maestro
//esta función es para leer los datos que están en el esclavo
//*****************************************************************************
unsigned short I2C_Master_Read(unsigned short a);
//*****************************************************************************
// Función para inicializar I2C Esclavo
//*****************************************************************************
void I2C_Slave_Init(uint8_t address);


#endif	/* XC_HEADER_TEMPLATE_H */

