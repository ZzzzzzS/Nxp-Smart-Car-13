#include "include.h"




void iic_init(void)
{

  SCL_dir_out;
  SCL_dir_out;

  SCL_set(HIGH);
  SDA_set(HIGH);
}


void I2Cstart(void)
{
  SCL_dir_out;
  SDA_dir_out;

  SDA_set(HIGH);
  somenop();
  SCL_set(HIGH);
  somenop();
  somenop();
  SDA_set(LOW);
  somenop();
  somenop();
  SCL_set(LOW);
}


void I2Cstop(void)
{
  SCL_dir_out;
  SDA_dir_out;

  SCL_set(HIGH);
  SDA_set(LOW);
  somenop();
  somenop();
  SDA_set(HIGH);
  somenop();
  somenop();
}


void I2Crecack()
{
  
   SCL_dir_out;
   SDA_dir_in;

   SCL_set(HIGH);
   somenop();
   somenop();
   while(SDA_read==1);
   SCL_set(LOW);
   somenop();
   somenop();
}


void I2Csendack(char ack)
{
    SCL_dir_out;
    SDA_dir_out;

    if(ack==1)
    {
       SDA_set(HIGH);
       SCL_set(HIGH);
       somenop();
       somenop();
       SCL_set(LOW);
       somenop();
       somenop();
    }
    else
    {
       SDA_set(LOW);
       SCL_set(HIGH);
       somenop();
       somenop();
       SCL_set(LOW);
       somenop();
       somenop();
    }
}


void I2Csend(byte data)
{
 unsigned char i=8;

 SCL_dir_out;
 SDA_dir_out;

 for (i=0; i<8; i++)
 {
        if((data&0x80)>>7)
          SDA_set(HIGH);
        else
          SDA_set(LOW);
        data=data<<1;
        SCL_set(HIGH);
        somenop();
        somenop();
        SCL_set(LOW);
        somenop();
        somenop();
 }
 SDA_set(LOW);

 I2Crecack();
}


signed char I2Creceive(void)
{
    byte i;
    byte dat = 0;

    SCL_dir_out;
    SDA_dir_in;

    for (i=0; i<8; i++)
    {
        dat <<= 1;
        SCL_set(HIGH);
        somenop();
        somenop();
        dat |= SDA_read; 
        SCL_set(LOW);
        somenop();
        somenop();
    }
    return dat;
}

void I2C_WriteByte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
    I2Cstart();
    I2Csend(SlaveAddress);
    I2Csend(REG_Address);
    I2Csend(REG_data);
    I2Cstop();
}
unsigned char I2C_ReadByte(unsigned char SlaveAddress,unsigned char REG_Address)
{
    unsigned char REG_data;
    I2Cstart();
    I2Csend(SlaveAddress);
    I2Csend(REG_Address);
    I2Cstart();
    I2Csend(SlaveAddress+1);
    REG_data=I2Creceive();
    I2Csendack(1);
    I2Cstop(); 
    return REG_data;
}

void somenop()
{
  volatile uint16_t  num = 50;
  while(num)
  {
    num--;
  }
}