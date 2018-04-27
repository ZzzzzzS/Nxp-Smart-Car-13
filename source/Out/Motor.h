/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */


#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "GlobalStructure.h"
#include "GlobalVars.h"

extern void PIDInit(pid_control_config_t *base,float P,float I,float D);
extern void PIDControl(pid_control_config_t *base);
extern void SpeedComput(speed_control_config_t *base);

extern void GetMotorSpeed(speed_control_config_t *base);
extern void MotorOut(speed_control_config_t *base);
extern void MotorInit();
extern void MotorOut_PWM(uint16_t num);
#endif