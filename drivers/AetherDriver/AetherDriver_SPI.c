
#include "include.h"



void  SPI_WriteData(uint8_t Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
		{SDA(HIGH);} //输出数据
		else 
                { SDA(LOW)};
		SCL(LOW);
		SCL(HIGH);
		Data<<=1;
	}
}

