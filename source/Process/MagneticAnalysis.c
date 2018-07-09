#include "MagneticAnalysis.h"

int getDirectionError3(int16_t* Road_Data)//用3电感获取误差
{
    int16_t sum[3];
    if (Road_Data[RIGHT] + Road_Data[LEFT] != 0)
	{
		sum[0] = 100 * (float)(Road_Data[RIGHT] - Road_Data[LEFT]) /(Road_Data[LEFT] + Road_Data[RIGHT]);				//差比和计算
	}
	else
	{
		sum[0] = 0;
	}
	if (Road_Data[LEFT]+ Road_Data[MIDDLE] != 0)
	{
		sum[1] = 100 * (float)(Road_Data[LEFT] - Road_Data[MIDDLE]) / (Road_Data[LEFT] + Road_Data[MIDDLE]);			//差比和计算
	}
	else
	{
		sum[1] = 0;
	}
	if (Road_Data[RIGHT] + Road_Data[MIDDLE] != 0)
	{
		sum[2] = 100 * (Road_Data[RIGHT] - Road_Data[MIDDLE]) / (Road_Data[MIDDLE] + Road_Data[RIGHT]);		//差比和计算
	}
	else
	{
		sum[2] = 0;
	}
	
	sum[2] = Rk*(float)sum[2] + Rb;
	sum[1] = Lk*(float)sum[1] + Lb;

	return (sum[0]*5 + sum[1] + sum[2])/7;						//计算出最终误差


}

int getDirectionError5(int16_t* value)//用5电感获取误差
{
   
}

void circleAnalysis(int16_t* value)
{

//圆环检测
	if(value[MIDDLE]>2000&&Circle_Flag==0)//检测入环
	{
		Circle_Flag=1; //检测到圆环将标志位 置1,并当作超时计数器使用
		
	}
        
        if(value[MIDDLE]<1800&&Circle_Flag==1)
        {
          Circle_Flag=3;
          if(value[FRONT_LEFT]>value[FRONT_RIGHT])
			Circle_Direction=LEFT;
		else
			Circle_Direction=RIGHT;
		Beep_Up();
        }
	
	if(value[MIDDLE]>1300&&Circle_Flag==3 && DistanceAddFlag>3500)
	{
		DistanceAddFlag = 0;
		Beep_Down();
                Circle_Flag=-100;
	}

        if(Circle_Flag<0)
        {
          Circle_Flag++;
        }

//圆环控制
	if(Circle_Flag==3 && DistanceAddFlag<2000)
	{
		if(Circle_Direction == LEFT)//刚入环的时候让它疯狂转一下
			value[RIGHT] = 0;
		
		else
			value[LEFT] =  0;
                        
                       
                          
                     for(int i=0;i<MAX_POSITION;i++)
                       if(value[i]<0)
                          value[i]=0;
	}
	

	if(DistanceAddFlag>15000)
	{
		Circle_Flag=0;
		DistanceAddFlag = 0;
		Beep_Down();
	}
}