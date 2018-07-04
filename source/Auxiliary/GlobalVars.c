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
int16_t InductanceVal[MAX_POSITION];
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
							.stop = 10,
							.Empty = 47,
							.distance_between=0xffff,
						};

//动力输出
 speed_control_config_t GV_speedControlT;
 pid_control_config_t PID_Motor;
 int16_t GV_steerPwmOutValueI;
 steer_config_t GV_steerControlT;
 uint16_t STEER_PWM_MAX=824;
 uint16_t STEER_PWM_MIN=674;
 uint16_t STEER_MIDDLE=746


//判断标志位
 uint32_t Circle_Flag=0;
 uint8_t Motor_Stop=0;
 uint8_t DISPLAY_FLAG=0;
 uint8_t STOP_FLAG=0;
//摄像头采集延迟计数
uint8_t CAMERA_COUNT=0;
const uint8_t CAMERA_LIMIT=5;
