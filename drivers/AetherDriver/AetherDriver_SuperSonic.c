#include "include.h"

void SuperSonicInit()
{
  UART4_Init();
}

void SuperSonicGetData(uint8_t Input)
{
    //环形队列缓冲区和数据分析队列的初始化
	static uint8_t dat[3]={0};
	static uint8_t num=0;
        uint16_t result;


    dat[num]=Input;
	if(dat[0] != 0xa5) num = 0;	//检查头帧是否正确，不正确就重新接收
	else ++num;
	
	if(num==3)					//接收完成，开始处理数据
	{
		num = 0;
		result = dat[1]<<8 | dat[2];
		Message.distance_between=result/7;
		if(Message.distance_between>255)
		Message.distance_between=255;
	}
}
