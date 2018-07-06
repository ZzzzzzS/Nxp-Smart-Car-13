/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */
#ifndef __AETHER_STEER__
#define __AETHER_STEER__


//extern void SteerOut();
extern void SteerInit();
extern void SteerPWMCalculator();
extern void SteerPWMCalculator2();
extern void SteerOut(void);
extern void Steer_ajust();
extern void SteerSet(uint16_t pwm);
#endif
