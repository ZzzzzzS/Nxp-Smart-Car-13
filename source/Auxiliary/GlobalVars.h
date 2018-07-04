/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */


#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#include "GlobalStructure.h"

//电感
extern int16_t InductanceVal[MAX_POSITION];
extern uint8_t InductanceMiddle; 

//图像
extern IMGS IMG_STATUS;
extern Using_Status Using_Flag;

//系统与会车
extern uint32_t g_Time;
extern uint32_t g_Time_NRF;
extern uint8_t NRF_TxBuf[32];
extern uint8_t NRF_RxBuf[32];
extern Message_t Message;
extern uint8_t Meet;
extern uint32_t Meet_distance;

//动力输出
extern speed_control_config_t GV_speedControlT;
extern pid_control_config_t PID_Motor;
extern int16_t GV_steerPwmOutValueI;
extern steer_config_t GV_steerControlT;
extern uint16_t STEER_PWM_MAX;
extern uint16_t STEER_PWM_MIN;

//判断标志位
extern uint32_t Circle_Flag;
extern uint8_t Motor_Stop;
extern uint8_t DISPLAY_FLAG;
extern uint8_t STOP_FLAG;

extern 	uint8_t CAMERA_COUNT;
extern 	const uint8_t CAMERA_LIMIT;
#endif
