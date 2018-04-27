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
#endif