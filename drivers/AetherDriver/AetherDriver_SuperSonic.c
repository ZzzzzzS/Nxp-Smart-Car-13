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
    static uint16_t result[3];
	uint16_t temp;


    dat[num]=Input;
	if(dat[0] != 0xa5) num = 0;	//检查头帧是否正确，不正确就重新接收
	else ++num;
	
	

	if(num==3)					//接收完成，开始处理数据
	{
		result[2]=result[1];
		result[1]=result[0];
		num = 0;
		result[0] = dat[1]<<8 | dat[2];
                if(result[0]>=6800)
                  result[0]=6800;

		
		temp=(result[0]+result[1]+result[2])/3;
		Message.distance_between=result[0]/27;
		old[2]=old[1];
  		old[1]=old[0];
  		old[0]=Message.distance_between;
	}
}
