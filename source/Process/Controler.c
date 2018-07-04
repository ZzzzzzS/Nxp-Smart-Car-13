#include "include.h"

void ImageControlor(uint8_t* img)  //列188，行120
{
  //缩放加二值化
  getSmallImage(img,small_image);
  if(use_flag)
  {

  }   
        
}

void ActiveDiffSpeed(speed_control_config_t *speed,int16_t *steerValue)
{
  
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

  led_down();
  if(READ_KEY2)
  {
    NRF24L01_SetMode(MODE_TX);
    NRF24L01_CE_L;
    NRF24L01_WriteTxPayload_NOACK((uint8_t*)(&Message), sizeof(Message));
  }

  NRF24L01_CE_H;   

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
    GV_speedControlT.Pid[0].SetSpeed = 40;
    GV_speedControlT.Pid[1].SetSpeed= GV_speedControlT.Pid[0].SetSpeed;
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
    GV_speedControlT.Pid[0].SetSpeed= 80;
    GV_speedControlT.Pid[1].SetSpeed = GV_speedControlT.Pid[0].SetSpeed;
    InductanceMiddle = INDUCTANCE_MIDDLE;
    Meet_distance=0;
  }
}

void SystemCtrl_PIT0CallBack()
{
	CAMERA_COUNT = (CAMERA_COUNT+1)%CAMERA_LIMIT;
	if(CAMERA_COUNT==0&&MT9V034_CaptureAccomplished == true) 
	{
		EnableIRQ(MT9V034_DMA_CHANNEL);
    	EnableIRQ(PORTB_IRQn);
	}
  //系统时间加一
	++g_Time;
	++g_Time_NRF;

  GetADCVal(InductanceVal);  //获取adc采集的值
  GV_steerControlT.ErrorDistance=getDirectionError3(InductanceVal); //差比和计算误差
  circleAnalysis(InductanceVal); //分析入圆
  SteerPWMCalculator(); //计算舵机PID
  SteerOut(); //计算舵机最终输出

  ActiveDiffSpeed();//计算主动差速
  GV_speedControlT.Pid[LeftWheel].NowSpeed = getLeftSpeed(); //获取当前速度
  GV_speedControlT.Pid[RightWheel].NowSpeed = -getRightSpeed(); //获取当前速度
    
  PIDControl(&GV_speedControlT.Pid[LeftWheel]); //计算PID
  PIDControl(&GV_speedControlT.Pid[RightWheel]);
   
  SpeedComput(&GV_speedControlT); //检查速度合法性
  MotorOut(&GV_speedControlT); //输出动力
}
