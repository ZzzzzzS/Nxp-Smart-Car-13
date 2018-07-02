#include "include.h"

void ImageControlor(uint8_t* img)  //列188，行120
{
  uint8_t use_flag = 1;
	int16_t Left_One=0;
	int16_t Right_One=0;
	static uint16_t g_Speed_Cp = 0;  
  if(READ_LEFT)
  {
    GV_speedControlT.Pid[0].AimSpeed +=10;
    GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
    Display_Number(0,6,GV_speedControlT.Pid[0].AimSpeed,YELLOW,RED);
  }
        
  led_down();
  if(READ_KEY2)
  {
    NRF24L01_SetMode(MODE_TX);
    NRF24L01_CE_L;
    NRF24L01_WriteTxPayload_NOACK((uint8_t*)(&Message), sizeof(Message));
  }

  NRF24L01_CE_H;   
		//缩放加二值化
  getSmallImage(img,small_image);
        
  if(Using_Flag==Using_A)
    Using_Flag=Using_B;
  else if(Using_Flag==Using_B)
    Using_Flag=Using_A;

  if(use_flag)
  {

  }   
        
}

void stop_car()
{
	
}

void meetingControl()
{
  if(READ_KEY2&&Message.distance_between<1500)
  {
    Message.stop = 22;
    Meet = 1;
  }

  if(!READ_KEY2&&NRF_RxBuf[1]==22)
  {
    Meet = 1;
  }

  if(Meet)
  {
    GV_speedControlT.Pid[0].AimSpeed = 40;
    GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
    InductanceMiddle = MEETING_MIDDLE;
  }
    
  if(Meet_distance>1000)
  {
    Message.stop = 10;
  }

  if(Meet_distance>2500)
  {
    Meet = 0;
    Message.stop = 10;
    GV_speedControlT.Pid[0].AimSpeed = 80;
    GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
    InductanceMiddle = INDUCTANCE_MIDDLE;
    Meet_distance=0;
  }
}

void SystemCtrl_PIT0CallBack()
{
  //系统时间加一
	++g_Time;
	++g_Time_NRF;

  GetADCVal(InductanceVal);  //获取adc采集的值
  GV_steerControlT.ErrorDistance=getDirectionError3(InductanceVal); //差比和计算误差
  circleAnalysis(InductanceVal); //分析入圆
  SteerPWMCalculator(); //计算舵机PID
  SteerOut(); //计算舵机最终输出

  /*static int16_t temp[5][2];
  static uint8_t loop_flag=0;
  temp[loop_flag][LeftWheel] = getLeftSpeed();
  temp[loop_flag][RightWheel] = -getRightSpeed();
    
  loop_flag=(loop_flag+1)%5;
    
  GV_speedControlT.Pid[LeftWheel].NowSpeed=0;
  GV_speedControlT.Pid[RightWheel].NowSpeed=0;
    
  for(int i=0;i<5;i++)
  {
    GV_speedControlT.Pid[LeftWheel].NowSpeed+=temp[i][LeftWheel];
    GV_speedControlT.Pid[RightWheel].NowSpeed+=temp[i][RightWheel];
  }
  GV_speedControlT.Pid[LeftWheel].NowSpeed = -GV_speedControlT.Pid[LeftWheel].NowSpeed/5;
  GV_speedControlT.Pid[RightWheel].NowSpeed = -GV_speedControlT.Pid[RightWheel].NowSpeed/5;*/

  GV_speedControlT.Pid[LeftWheel].NowSpeed = getLeftSpeed(); //获取当前速度
  GV_speedControlT.Pid[RightWheel].NowSpeed = -getRightSpeed(); //获取当前速度
    
  PIDControl(&GV_speedControlT.Pid[LeftWheel]); //计算PID
  PIDControl(&GV_speedControlT.Pid[RightWheel]);
   
  SpeedComput(&GV_speedControlT); //检查速度合法性
  MotorOut(&GV_speedControlT); //输出动力
}