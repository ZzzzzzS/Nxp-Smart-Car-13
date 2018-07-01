#include "MagneticAnalysis.h"

int getDirectionError3(int16_t* Road_Data)//用3电感获取误差
{
    int16_t sum[3];
    if (Road_Data[RIGHT] + Road_Data[LEFT] != 0)
	{
		sum[0] = 1000 * (float)(Road_Data[RIGHT] - Road_Data[LEFT]) /(Road_Data[LEFT] + Road_Data[RIGHT]);				//差比和计算
	}
	else
	{
		sum[0] = 0;
	}
	if (Road_Data[LEFT]+ Road_Data[MIDDLE] != 0)
	{
		sum[1] = 1000 * (float)(Road_Data[LEFT] - Road_Data[MIDDLE]) / (Road_Data[LEFT] + Road_Data[MIDDLE]);			//差比和计算
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
	
	sum[2] = Rk*sum[2] + Rb;
	sum[1] = Lk*sum[1] + Lb;

	return (sum[0]*5 + sum[1] + sum[2])/7;						//计算出最终误差


}

int getDirectionError5(int16_t* value)//用5电感获取误差
{
   
}