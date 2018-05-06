#ifndef __AETHER_SPEED__
#define __AETHER_SPEED__
//若要修改此处，Speed_Init函数中的管脚复用号也要修改
#include "include.h"

#define LEFT_BASE       FTM1
#define RIGHT_BASE      FTM2

#define LEFT_PORT_BASE  PORTA 
#define LEFT_A_PIN      12
#define LEFT_B_PIN      13

#define RIGHT_PORT_BASE  PORTA 
#define RIGHT_A_PIN      10
#define RIGHT_B_PIN      11

extern uint16_t g_Speed;
extern void Speed_Init();

static inline int16_t getLeftSpeed()
{
    int16_t temp_qL = FTM_GetQuadDecoderCounterValue(FTM1);
	if(DISTANCE_RECORD_FLAG)
		DistanceRecord+=temp_qL;
    FTM_ClearQuadDecoderCounterValue(FTM1);
    return temp_qL;
}

static inline int16_t getRightSpeed()
{
    int16_t temp_qR = FTM_GetQuadDecoderCounterValue(FTM2);
    FTM_ClearQuadDecoderCounterValue(FTM2);
    return temp_qR;
}

#endif
