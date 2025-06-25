#include<xc.h>
#include "lcd.h"
#include <stdio.h>
#define _ENABLE {PORTDbits.RD4 = 1; __delay_ms(2); PORTDbits.RD4 = 0;}
#define RS PORTDbits.RD5
#define _XTAL_FREQ 1000000
void lcd_initialize(void){
    TRISD= 0;
    PORTD = 0;
    __delay_ms(20);
    PORTD = 0b00000011;
    _ENABLE;
    __delay_ms(7);
    PORTD = 0b00000011;
    _ENABLE;
    __delay_ms(1);
    PORTD = 0b00000011;
    _ENABLE;
}

void lcd_on(void){
    //4 bit
    PORTD = 0b00000010;
    _ENABLE;
    // attivo display, cursore, lampeggio
    PORTD = 0b00000000; 
    _ENABLE;
    PORTD = 0b00001111; 
    _ENABLE;
    // attivo modalità due righe
    PORTD = 0b00000010; 
    _ENABLE;
    PORTD = 0b00001000;
    _ENABLE;
    __delay_ms(1);
}

void cursor_pos(int x){
    PORTD = x;
    PORTD = PORTD >> 4;
    PORTDbits.RD3 = 1;
    RS = 0;
    _ENABLE;
    PORTD = x;
    RS = 0;
    _ENABLE;
    __delay_ms(5);
}

void cursor_home(void){
    PORTD = 0b00000000;
    _ENABLE;
    PORTD = 0b00000010;
    _ENABLE;
}

void clear(void){
    PORTD = 0b00000000;
    _ENABLE;
    PORTD = 0b00000001;
    _ENABLE;
    __delay_ms(5);
}

void output_char(char c){
    unsigned char high, low;
    high = c>>4;
    low = c;
    PORTD = high;
    RS = 1;
    _ENABLE;
    
    PORTD = low;
    RS = 1;
    _ENABLE;
    __delay_ms(5);
}

void output_frase(char*frase){
    while(*frase){
        output_char(frase[0]);
        *frase++;
    }
    __delay_ms(5);
}

void stringa_float_stringa_output(char*txt, float a, char*txt_){
    char frase[16];
    sprintf(frase,"%s%.2f%s",txt, a, txt_);
    output_frase(frase);
}
void output_float(float a){
    char frase[16];
    sprintf(frase,"%.2f",a);
    output_frase(frase);
}
void output_int(int a){
    char frase[16];
    sprintf(frase,"%d",a);
    output_frase(frase);
}


