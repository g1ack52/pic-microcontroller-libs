
#include <xc.h>
#include "I2C.h"
#include "MPU6050.h"
#include <stdio.h>
#include <math.h>
#include "pid.h"
#include "pwm.h"


bit i = 0;
//-------------[ MPU6050 Routines ]------------------
//---------------------------------------------------

void MPU6050_Init()
{
  // Power-Up Delay & I2C_Init
  __delay_ms(100);
  I2C_Master_Init();
 
  // Setting The Sample (Data) Rate
  I2C_Start(0xD0);
  I2C_Master_Write(SMPLRT_DIV);
  I2C_Master_Write(0x07);
  I2C_Master_Stop();
 
  // Setting The Clock Source
  I2C_Start(0xD0);
  I2C_Master_Write(PWR_MGMT_1);
  I2C_Master_Write(0x01);
  I2C_Master_Stop();
 
  // Configure The DLPF
  I2C_Start(0xD0);
  I2C_Master_Write(CONFIG);
  I2C_Master_Write(0x00);
  I2C_Master_Stop();
 
  // Configure The ACCEL (FSR= +-2g)
  I2C_Start(0xD0);
  I2C_Master_Write(ACCEL_CONFIG);
  I2C_Master_Write(0x00);
  I2C_Master_Stop();
 
  // Configure The GYRO (FSR= +-1000d/s)
  I2C_Start(0xD0);
  I2C_Master_Write(GYRO_CONFIG);
  I2C_Master_Write(0x10);
  I2C_Master_Stop();
 
  // Enable Data Ready Interrupts
  I2C_Start(0xD0);
  I2C_Master_Write(INT_ENABLE);
  I2C_Master_Write(0x01);
  I2C_Master_Stop();
}

void MPU6050_Read()
{
  char buffer[40];
  I2C_Start(0xD0);
  I2C_Master_Write(ACCEL_XOUT_H);
  I2C_Master_Stop();
  I2C_Start(0xD1);
  //dati accelerometro----------------------------------------------------------
  Ax = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
  Ay = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
  Az = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
  //dati temperatura------------------------------------------------------------
  T  = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
//  //dati giroscopio-------------------------------------------------------------
  Gx = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
  Gy = ((int)I2C_Read(0)<<8) | (int)I2C_Read(0);
  Gz = ((int)I2C_Read(0)<<8) | (int)I2C_Read(1);
  I2C_Master_Stop();

  
  //angle_acc= atan((Ay/2048.0)/sqrt((Ax/2048.0)*(Ax/2048.0)+ (Az/2048.0)*(Az/2048.0)))*57.3; //acc
  angle_acc= atan((Ay/16384.0)/sqrt((Ax/16384.0)*(Ax/16384.0)+ (Az/16384.0)*(Az/16384.0)))*57.3; //acc
  if(!i){
      angle = angle_acc;
      i =! i;
  }
  angle_gyro = Gx/32.8;
  angle = 0.98 *(angle + angle_gyro*t) + 0.02*angle_acc;
}