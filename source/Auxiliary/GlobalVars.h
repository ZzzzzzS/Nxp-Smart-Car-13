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

extern speed_control_config_t GV_speedControlT;
extern pid_control_config_t PID_Motor;
extern int16_t GV_steerPwmOutValueI;
extern steer_config_t GV_steerControlT;
extern IMGS IMG_STATUS;
extern uint8_t Circle_Flag;
extern uint8_t Motor_Stop;
extern Using_Status Using_Flag;
extern uint8_t DISPLAY_FLAG;
extern int16_t InductanceVal[2];
extern uint32_t DistanceRecord;
extern uint8_t DISTANCE_RECORD_FLAG;
extern uint8_t LeftOrRight;

extern uint16_t STEER_PWM_MAX;
extern uint16_t STEER_PWM_MIN;

extern uint8_t img_middle; 
extern uint32_t g_Time;
extern uint8_t STOP_FLAG;
extern uint8_t C_OUT;
extern uint32_t g_Time_NRF;
extern int16_t NRF_TxBuf[32];                              // NRF24L01发送缓冲区
extern int16_t NRF_RxBuf[32];
#endif
