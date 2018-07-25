#include "include.h"


void FinnalPointHandler()
{
  static uint32_t Time;
  //TODO 添加GPIO检测
  //if()
  //{
   // Time=g_Time;
  //}
  if(FinnalPointFlag)
  {
      MeetingStatus=meeting;
  }
}


void ImageControlor(uint8_t* img)  //列188，行120
{

    getSmallImage(img,small_image);
  //correctSmallImage(small_image, converted_image);
  if(DISPLAY_FLAG)
  {
    LCD_DrawPicture_Small(small_image);
    //LCD_DrawPicture(img);
  }
  if(g_Time-500>MeetingTime)
    //FindMeetingArea(small_image);
     ;   
}

void ActiveDiffSpeed(speed_control_config_t *speed,int16_t *steerValue)
{
  GV_speedControlT.Pid[RightWheel].AimSpeed=GV_speedControlT.Pid[RightWheel].SetSpeed;
  GV_speedControlT.Pid[LeftWheel].AimSpeed=GV_speedControlT.Pid[LeftWheel].SetSpeed;
  

  GV_speedControlT.Pid[RightWheel].AimSpeed=((float)(STEER_MIDDLE-GV_steerPwmOutValueI)*(-0.2258)+100)*GV_speedControlT.Pid[RightWheel].SetSpeed/100;
  GV_speedControlT.Pid[LeftWheel].AimSpeed=((float)(STEER_MIDDLE-GV_steerPwmOutValueI)*0.2258+100)*GV_speedControlT.Pid[LeftWheel].SetSpeed/100;

  if(MeetingStatus==meeting)
  {
    GV_speedControlT.Pid[RightWheel].AimSpeed=GV_speedControlT.Pid[RightWheel].SetSpeed;
    GV_speedControlT.Pid[LeftWheel].AimSpeed=GV_speedControlT.Pid[LeftWheel].SetSpeed;
  }

}

void stop_car()
{
  if(0)
    STOP_FLAG=1;
  else
    STOP_FLAG=0;
}

void meetingControl()
{

  static int16_t speed_origin;
  
  led_down();
  
  

  if(Message.distance_between<74&&old[0]<74&&old[1]<74&&old[2]<74)
  {
    GV_speedControlT.Pid[0].AimSpeed = GV_speedControlT.Pid[0].SetSpeed*0.2;
    GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[1].SetSpeed*0.2;
  }

  if(Message.distance_between<=60&&old[0]<60&&old[1]<60&&old[2]<60)
  {
    MeetingStatus=meeting;
    MeetingTime=g_Time;
    MeetingArea=0;
    DistanceAddFlag3=1;
  }

  if(Message.distance_between>74)
  {
    MeetingStatus=normal;
  }

  if(DistanceAddFlag3>7000)
  {
    DistanceAddFlag3=0;
  }

  if(MeetingStatus==meeting||DistanceAddFlag3!=0)
  {
    GV_speedControlT.Pid[0].AimSpeed = GV_speedControlT.Pid[0].SetSpeed*0.4;
    GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[1].SetSpeed*0.4;
  }

  
}

void SystemCtrl_PIT0CallBack()
{
    

  //系统时间加一
  //MeetingStatus=normal;
  if(MeetingArea==0)
  {
    GV_speedControlT.Pid[0].SetSpeed=g_Speed;
	  GV_speedControlT.Pid[1].SetSpeed=g_Speed;
  }
  
  if(AllDistance/100>FullDistance-300)
  {
   // GV_speedControlT.Pid[0].SetSpeed*=0.5;
   // GV_speedControlT.Pid[1].SetSpeed*=0.5;
   ;
  }

	++g_Time;
	++g_Time_NRF;
  GetADCVal(InductanceVal);  //获取adc采集的值
  
  circleAnalysis(InductanceVal); //分析入圆
  //InductanceVal[MIDDLE] = InductanceVal[MIDDLE]>2000? 1000:InductanceVal[MIDDLE];
  GV_steerControlT.ErrorDistance=getDirectionError3(InductanceVal); //差比和计算误差
  SteerPWMCalculator(); //计算舵机PID
 
  ActiveDiffSpeed(&GV_speedControlT,&GV_steerPwmOutValueI);

  if(Circle_Flag==1||Circle_Flag==2)
  {
    GV_speedControlT.Pid[0].AimSpeed=120;
    GV_speedControlT.Pid[1].AimSpeed=120;
  }

  SteerOut(); //计算舵机最终输出
  
  if(g_Time%4==0)
  {
  GV_speedControlT.Pid[LeftWheel].NowSpeed = getLeftSpeed(); //获取当前速度
  GV_speedControlT.Pid[RightWheel].NowSpeed = -getRightSpeed(); //获取当前速度
  }
  if(g_Time%4==0)
  {
    if(READ_KEY2)
    {
    NRF24L01_CE_L;
    //Message.distance_between=12;
    NRF24L01_WriteTxPayload_NOACK((uint8_t*)(&Message), sizeof(Message));
    NRF24L01_CE_H;  
    }
  }
  
  AllDistance+=(GV_speedControlT.Pid[LeftWheel].NowSpeed+
                       GV_speedControlT.Pid[RightWheel].NowSpeed)/2;

  if(Circle_Flag==3)
  {
      DistanceAddFlag+=(GV_speedControlT.Pid[LeftWheel].NowSpeed+
                       GV_speedControlT.Pid[RightWheel].NowSpeed)/2;
  }
  if(MeetingArea!=0)
  {
      DistanceAddFlag2+=(GV_speedControlT.Pid[LeftWheel].NowSpeed+
                       GV_speedControlT.Pid[RightWheel].NowSpeed)/2;
  }
  if(DistanceAddFlag3!=0)
  {
    DistanceAddFlag3+=(GV_speedControlT.Pid[LeftWheel].NowSpeed+
                       GV_speedControlT.Pid[RightWheel].NowSpeed)/2;
  }

  if((AllDistance/100>(HalfDistance-500)&&AllDistance/100<(HalfDistance+500))||AllDistance/100<500||AllDistance/100>(FullDistance-500))
  {
    ;
  }
  else
  {
    Message.distance_between=251;
  }

  meetingControl();
    
  PIDControl(&GV_speedControlT.Pid[LeftWheel]); //计算PID
  PIDControl(&GV_speedControlT.Pid[RightWheel]);
  if((InductanceVal[LEFT]+InductanceVal[MIDDLE]+InductanceVal[RIGHT])<100)
  {
    STOP_FLAG = 1;
  }
  else if((InductanceVal[LEFT]+InductanceVal[MIDDLE]+InductanceVal[RIGHT])>=100)
  {
    STOP_FLAG = 0;
  }

  
  SpeedComput(&GV_speedControlT); //检查速度合法性
  MotorOut(&GV_speedControlT); //输出动力
}
