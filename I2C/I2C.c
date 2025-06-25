
#include <xc.h>
#include "I2C.h"


//---------------[ I2C Routines ]-------------------
//--------------------------------------------------

void I2C_Master_Init()
{
  SSPSTATbits.SMP = 1; //slew rate disabilitato
  SSPSTATbits.CKE = 0; //SMBus disabilitati
  SSPCONbits.SSPEN = 1; //SDA e SCL come pin della porta serial
  SSPCONbits.SSPM = 0b1000; //i2c master mode,
                              //clock=Fosc/(4*(SSPADD+1))
  //SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate)-1; //baud rate generato
  SSPADD = 0x0A; //1MHz
  TRISCbits.TRISC3 = 1; //serial clock
  TRISCbits.TRISC4 = 1; //serial data
}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Start(char add)
{
    I2C_Master_Wait();
    SEN = 1;
    I2C_Master_Write(add);
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_ACK(void)
{
	ACKDT = 0;			// 0 -> ACK
    ACKEN = 1;			// Send ACK
    while(ACKEN);
}

void I2C_NACK(void)
{
	ACKDT = 1;			// 1 -> NACK
	ACKEN = 1;			// Send NACK
    while(ACKEN);
}

unsigned char I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}

unsigned char I2C_Read_Byte(void)
{
    //---[ Receive & Return A Byte ]---
    I2C_Master_Wait();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSPIF);	  // Wait Until Completion
	SSPIF = 0;		  // Clear The Interrupt Flag Bit
    I2C_Master_Wait();
    return SSPBUF;	  // Return The Received Byte
}

unsigned char I2C_Read(unsigned char ACK_NACK)
{  
    //---[ Receive & Return A Byte & Send ACK or NACK ]---
    unsigned char Data;
    RCEN = 1;              
    while(!BF);      
    Data = SSPBUF;           
    if(ACK_NACK==0)
        I2C_ACK();            
    else
        I2C_NACK();     
    while(!SSPIF);                 
    SSPIF=0;   
    return Data;
}



