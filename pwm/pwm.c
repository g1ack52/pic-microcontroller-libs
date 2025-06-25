#include<xc.h>
#include "pwm.h"
#define _XTAL_FREQ 750000

void pwm_setup(int x){
    //motore dx
    CCP1CONbits.CCP1M = 0b1100; //11xx pwm mode
    TRISCbits.TRISC2 = 0; //output pwm dx
    //motore sx
    CCP2CONbits.CCP2M = 0b1100; //pwm mode
    TRISCbits.TRISC1 = 0; //output pwm sx
    //periodo
    PR2 = x;
}
void timer2_setup(int x){
    //prescaler
    switch(x){
        case 1:
            T2CONbits.T2CKPS = 0b00; 
            break;
        case 4:
            T2CONbits.T2CKPS = 0b01; 
            break;
        case 16:
            T2CONbits.T2CKPS = 0b11; 
            break;
        default:
            T2CONbits.T2CKPS = 0b00;
    }
    T2CONbits.TMR2ON = 1;
}
void dc_dx(int dc){
    CCPR1L = (dc)>>2;
    CCP1CON  = CCP1CON & 0b11001111;
    CCP1CON = CCP1CON |(((dc)<<4)&0b00110000);
}
void dc_sx(int dc){
    CCPR2L = (dc)>>2;
    CCP2CON  = CCP2CON & 0b11001111;
    CCP2CON = CCP2CON |(((dc)<<4)&0b00110000);
}
int chopping (int dc){
    //estremo inferiore
    if(dc < 150) dc = 150;
    
    //esremo superiore
    if(dc > 640) dc = 640;
 
    return dc;
}