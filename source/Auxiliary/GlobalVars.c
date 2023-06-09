/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */


#include "include.h"

//电感
uint16_t InductanceVal[MAX_POSITION];
uint8_t InductanceMiddle=INDUCTANCE_MIDDLE; 

//图像
 IMGS IMG_STATUS;
 Using_Status Using_Flag=Using_A;

//系统与会车
 uint32_t g_Time;
 uint32_t g_Time_NRF;
 uint8_t NRF_TxBuf[32];
 uint8_t NRF_RxBuf[32];
 uint8_t Meet;
 uint32_t Meet_distance;
 Message_t Message={
							.distance_between=0xff,
						};

//动力输出
 speed_control_config_t GV_speedControlT;
 pid_control_config_t PID_Motor;
 int16_t GV_steerPwmOutValueI;
 steer_config_t GV_steerControlT;
 uint16_t STEER_PWM_MAX=824;
 uint16_t STEER_PWM_MIN=674;
 uint16_t STEER_MIDDLE=746;
 uint16_t g_Speed = 220;


//判断标志位
 int32_t Circle_Flag=0;
 int32_t Circle_Flag2=0;
 uint8_t Motor_Stop=0;
 uint8_t DISPLAY_FLAG=0;
 uint8_t STOP_FLAG=0;
 int32_t DistanceAddFlag=0;
 int32_t DistanceAddFlag2=0;
 int32_t DistanceAddFlag3=0;
 int32_t DistanceAddFlag4=0;
 uint8_t Circle_Direction = LEFT;
 uint8_t MeetingArea=0;
 uint8_t MeetingStatus;
 uint32_t MeetingTime;
 uint8_t old[3];
 uint16_t FinnalPointFlag=0;
 int32_t AllDistance;
 int32_t HalfDistance;
 int32_t FullDistance;
 uint8_t GaveValue;
 CircleQueue_t CircleQueue;
