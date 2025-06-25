#include <xc.h>
#include "interrupt.h"
void GIE_setup(void){    
    INTCONbits.PEIE = 1; //periferiche
    INTCONbits.GIE = 1; //general enable
}
void INT_pin_setup(void){
    INTCONbits.INTE = 1;
    OPTION_REGbits.INTEDG = 0;//fronti di discesa
    TRISBbits.TRISB0 = 1;
    INTCONbits.INTF = 0;
}
void IOC_pin_setup(void){
    //interrupt in change
    INTCONbits.RBIE = 1; //enable
    INTCONbits.RBIF = 0; //flag
    TRISBbits.TRISB4 = 1; 
    TRISBbits.TRISB5 = 1;
}