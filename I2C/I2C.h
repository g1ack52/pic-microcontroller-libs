/* File: I2C.h */

#define _XTAL_FREQ             1000000

#define I2C_BaudRate           100000
#define SCL_D                  TRISC3
#define SDA_D                  TRISC4

//-----------[ Functions' Prototypes ]--------------

//---[ I2C Routines ]---

void I2C_Master_Init();
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Start(char add);
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char data);
unsigned char I2C_Read_Byte();
unsigned char I2C_Read(unsigned char);


