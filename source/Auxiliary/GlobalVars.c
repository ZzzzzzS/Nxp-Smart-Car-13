/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */


#include "include.h"

speed_control_config_t GV_speedControlT;
steer_config_t GV_steerControlT;
int16_t GV_steerPwmOutValueI;
pid_control_config_t PID_Motor;
IMGS IMG_STATUS=IMG_N;
uint8_t Circle_Flag=0;
uint8_t Motor_Stop=0;

Using_Status Using_Flag=Using_A;
uint8_t DISPLAY_FLAG=0;
uint16_t STEER_MIDDLE=720;
int16_t InductanceVal[2];
uint32_t DistanceRecord=0;
uint8_t DISTANCE_RECORD_FLAG=0;
uint8_t LeftOrRight='l';

uint16_t STEER_PWM_MAX=835;
uint16_t STEER_PWM_MIN=680;


uint8_t img_middle = IMG_MIDDLE;
uint32_t g_Time = 0;
uint32_t g_Time_NRF = 0;
uint8_t STOP_FLAG=0;
uint8_t C_OUT = 0;
uint8_t NRF_TxBuf[32];                              // NRF24L01发送缓冲区
uint8_t NRF_RxBuf[32];
uint8_t Meet = 0;
uint16_t circle_angle = 0;
uint32_t Meet_distance=0;
Message_t Message={
	.stop = 10,
	.Empty = 47,
	.distance_between=0xffff,
};
