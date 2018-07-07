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
		if(value[LEFT]>value[RIGHT])
			Circle_Direction = LEFT;
		else
			Circle_Direction = RIGHT;
	}
	
	if(DistanceAddFlag>1500)
	{
		Circle_Flag=0;
		DistanceAddFlag = 0;
	}

	if(Circle_Flag!=0) //控制声音
	{
		Beep_Up();
	}
	else
	{
		Beep_Down();
	}

//圆环控制
	if(Circle_Flag!=0)
	{
		if(Circle_Direction == LEFT)//刚入环的时候让它疯狂转一下
		{
			GV_steerControlT.ErrorDistance-=50;
		}
		else
		{
			GV_steerControlT.ErrorDistance+=50;
		}
	}
	else
	{

	}





	/*if(value[LEFT]>3500&&DISTANCE_RECORD_FLAG==0&&C_OUT==0)
	{
		DISTANCE_RECORD_FLAG = 1;
	}

		  if(DISTANCE_RECORD_FLAG)
		  {
                         Beep_Up();
          
                         if(DistanceRecord>2000&&DistanceRecord<4000){
                           if(circle_angle==0)
                             circle_angle = GV_steerPwmOutValueI;
                           else 
                             circle_angle = (GV_steerPwmOutValueI+circle_angle)/2;
                         }
			 if(READ_KEY4)
			 {
                                 if(DistanceRecord<2000){
                                   SpaceMiddles.points[SpaceMiddles.count-1].x = (SpaceMiddles.points[SpaceMiddles.count-1].x+80)/2;
                                  SpaceMiddles.points[SpaceMiddles.count-2].x = (SpaceMiddles.points[SpaceMiddles.count-1].x+75)/2;
                                 }
			 }
			 if(READ_KEY3)
			 {
                                SpaceMiddles.points[SpaceMiddles.count-1].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+10)/2;	
                                if(DistanceRecord<2000){
                                  SpaceMiddles.points[SpaceMiddles.count-1].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+15)/2;
                                  SpaceMiddles.points[SpaceMiddles.count-2].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+30)/2;
                                }
			 }
                
		  }
		  
		  if(Left_One>1500&&DistanceRecord>5000)
		  {
                          GV_speedControlT.Pid[0].PidCore.Kp = 0.8;
                           GV_speedControlT.Pid[1].PidCore.Kp =0.8;
                          GV_speedControlT.Pid[0].AimSpeed = 80;
                          GV_speedControlT.Pid[1].AimSpeed = 80;
                          Circle_Flag++;
                          Beep_Down();
                          circle_angle=0;
			  C_OUT = 1;
			  DISTANCE_RECORD_FLAG = 0;
			  DistanceRecord = 0;
		  }

		  if(C_OUT&&Left_One<1000)
		  {
			  C_OUT = 0;
		  }*/
}