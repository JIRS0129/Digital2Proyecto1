/* 
 * File:   LCD.h
 * Author: JIRS0129
 *
 * Created on February 8, 2020, 7:39 AM
 */
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

#ifndef LCD_H
#define	LCD_H

//Definition of pins for the LCD
#define RS RD0
#define RW RC2
#define E RD1
#define dataPort PORTB

uint8_t cursor = 0; //Var for cursor

//Prototypes
void initLCD(void);
void setCursorLCD(uint8_t y, uint8_t x);
void clcLCD(void);
void writeStrLCD(uint8_t *a);
void writeCharLCD(uint8_t character);
void cmdLCD(uint8_t cmd);
void writeIntLCD(uint8_t numero);
void writeFloat(uint8_t integer, uint8_t decimals, uint8_t initPos);

#endif	/* LCD_H */

