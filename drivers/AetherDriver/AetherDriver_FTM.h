/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */


#ifndef __DRIVER_FTM_H__
#define __DRIVER_FTM_H__
#include "fsl_clock.h"

#define FTM0_PRECISON 10000U  //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define FTM1_PRECISON 10000U  //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define FTM2_PRECISON 10000U  //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define FTM3_PRECISON 10000U  //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON

extern void ftm_pwm_init(FTM_Type* ftmn, uint8_t ch, uint32_t freq, uint32_t duty);
extern void ftm_pwm_duty(FTM_Type* ftmn, uint8_t ch, uint32_t duty);
extern void ftm_quad_init(FTM_Type* ftmn);

/*============================================
函数名：int16_t ftm_quad_get(FTM_Type* ftmn)
作用:获取正交解码值
作者:ZZS
说明:已清除正交解码计数寄存器值,无需再清除
==========================================*/

static inline int16_t ftm_quad_get(FTM_Type* ftmn)
{
  int16_t val;
  val = ftmn->CNT;
  ftmn->CNT=0;
  return val;
}

#endif