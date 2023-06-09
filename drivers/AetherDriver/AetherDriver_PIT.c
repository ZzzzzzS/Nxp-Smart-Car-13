#include "include.h"

void PIT0_Init(uint16_t mm)
{
    pit_config_t PIT_config;
    // PIT_GetDefaultConfig(&PIT_config);
    PIT_config.enableRunInDebug = true;
    
    /* Init pit module */
    PIT_Init(PIT, &PIT_config);
    /* Set Timer Chain Mode */
    PIT_SetTimerChainMode(PIT, kPIT_Chnl_0, false);
    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(mm, CLOCK_GetBusClkFreq()));         // 定时周期 T0 = 20ms
    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    /* Enable at the NVIC */
    EnableIRQ(PIT0_IRQn);
    /* Start channel 0 */
     //PIT_StartTimer(PIT, kPIT_Chnl_0);
}

void PIT1_Init(uint16_t mm)
{
    pit_config_t PIT_config;
    // PIT_GetDefaultConfig(&PIT_config);
    PIT_config.enableRunInDebug = true;
    
    /* Init pit module */
    PIT_Init(PIT, &PIT_config);
    /* Set Timer Chain Mode */
    PIT_SetTimerChainMode(PIT, kPIT_Chnl_1, false);
    /* Set timer period for channel 1 */
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_1, MSEC_TO_COUNT(mm, CLOCK_GetBusClkFreq()));         // 定时周期 T0 = 20ms
    /* Enable timer interrupts for channel 1 */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_1, kPIT_TimerInterruptEnable);
    /* Enable at the NVIC */
    EnableIRQ(PIT1_IRQn);
    
    
    /* Start channel 1 */
     //PIT_StartTimer(PIT, kPIT_Chnl_1);
}

void PIT2_Init(uint16_t mm)
{
    pit_config_t PIT_config;
    // PIT_GetDefaultConfig(&PIT_config);
    PIT_config.enableRunInDebug = true;
    
    /* Init pit module */
    PIT_Init(PIT, &PIT_config);
    /* Set Timer Chain Mode */
    PIT_SetTimerChainMode(PIT, kPIT_Chnl_2, false);
    /* Set timer period for channel 2 */
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_2, MSEC_TO_COUNT(mm, CLOCK_GetBusClkFreq()));         // 定时周期 T0 = 20ms
    /* Enable timer interrupts for channel 2 */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_2, kPIT_TimerInterruptEnable);
    /* Enable at the NVIC */
    EnableIRQ(PIT2_IRQn);
    /* Start channel 2 */
     //PIT_StartTimer(PIT, kPIT_Chnl_2);
}

void PIT3_Init(uint16_t mm)
{
    pit_config_t PIT_config;
    // PIT_GetDefaultConfig(&PIT_config);
    PIT_config.enableRunInDebug = true;
    
    /* Init pit module */
    PIT_Init(PIT, &PIT_config);
    /* Set Timer Chain Mode */
    PIT_SetTimerChainMode(PIT, kPIT_Chnl_3, false);
    /* Set timer period for channel 3 */
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_3, MSEC_TO_COUNT(mm, CLOCK_GetBusClkFreq()));         // 定时周期 T0 = 20ms
    /* Enable timer interrupts for channel 3 */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_3, kPIT_TimerInterruptEnable);
    /* Enable at the NVIC */
    EnableIRQ(PIT3_IRQn);
    /* Start channel 3 */
     //PIT_StartTimer(PIT, kPIT_Chnl_3);
}


void PIT0_IRQHandler(void)
{
    // 清中断标志位
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    SystemCtrl_PIT0CallBack();
}

void PIT1_IRQHandler(void)
{// 清中断标志位
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);	
}

void PIT2_IRQHandler(void)
{
    // 清中断标志位
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);
}

void PIT3_IRQHandler(void)
{
    // 清中断标志位
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);
    
}
