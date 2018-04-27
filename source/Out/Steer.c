/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */

#include "include.h"

void SteerInit() {
  PORT_SetPinMux(PORTE, 12, kPORT_MuxAlt6);  //引脚复用
  GV_steerControlT.ErrorDistance = 0;
  GV_steerControlT.LastErrorDistance = 0;
  GV_steerControlT.PD.Steer_P = 4;
  GV_steerControlT.PD.Steer_D = 1;
  GV_steerControlT.PD.Steer_P_Small = 2;
  GV_steerControlT.PD.Steer_D_Small = 1;
  // ftm_pwm_init(STEER_FTM, STEER_FTM_CHANAL,100, 0);

  ftm_config_t FTM3Info;
  ftm_chnl_pwm_signal_param_t ftmParam[1];

  /* Configures the FTM parameters with frequency 50 HZ */
  ftmParam[0].chnlNumber = kFTM_Chnl_7;
  ftmParam[0].level = kFTM_HighTrue;
  ftmParam[0].dutyCyclePrecision = 10 * 1000U;
  ftmParam[0].dutyCyclePercent = STEER_MIDDLE;  
  ftmParam[0].firstEdgeDelayPercent = 0U;

  FTM_GetDefaultConfig(&FTM3Info);

  FTM3Info.reloadPoints = kFTM_CntMax;
  FTM3Info.chnlPolarity = 0;

  /* Initializes the FTM module. */
  FTM_Init(FTM3, &FTM3Info);
  FTM_SetupPwm(FTM3, ftmParam,
               sizeof(ftmParam) / sizeof(ftm_chnl_pwm_signal_param_t),
               kFTM_EdgeAlignedPwm, 50, CLOCK_GetFixedFreqClkFreq());  // Ƶ��50
  FTM_StartTimer(FTM3, kFTM_FixedClock);
}

void SteerPWMCalculator() {
  int16_t errorNow=0;
  int16_t addPwm = 0;
  if(SpaceMiddles.count!=0){
    
    for(int loop=SpaceMiddles.count-1;loop>0;--loop)
    {
      if(SpaceMiddles.points[loop].y>33){
        SpaceMiddles.count=loop+1;
        break;
      }
    }
    
    if(SpaceMiddles.count>3)
      errorNow = (SpaceMiddles.points[SpaceMiddles.count-1].x+SpaceMiddles.points[SpaceMiddles.count-2].x+SpaceMiddles.points[SpaceMiddles.count-3].x)/3-46;
    else
      errorNow = SpaceMiddles.points[SpaceMiddles.count-1].x-46;
    if(SpaceMiddles.count<20&&I_abs(errorNow)>20)
    {
      errorNow += errorNow>0? 10:-10;
    }
    
    
    if(I_abs(errorNow)<20)
    {
      addPwm = (int16_t)(GV_steerControlT.PD.Steer_P_Small * errorNow +
                               GV_steerControlT.PD.Steer_D_Small *(errorNow-GV_steerControlT.ErrorDistance));
    }else{
        addPwm = (int16_t)(GV_steerControlT.PD.Steer_P * errorNow +
                           GV_steerControlT.PD.Steer_D *(errorNow-GV_steerControlT.ErrorDistance));
    }
    
    GV_steerControlT.ErrorDistance = errorNow;
    
    GV_steerPwmOutValueI = STEER_MIDDLE-addPwm;
  }
  // SteerOut();
}

void SteerOut(void) {  //对输入上界进行保护
  if(GV_steerPwmOutValueI>STEER_PWM_MAX)
    GV_steerPwmOutValueI=STEER_PWM_MAX;
  else if(GV_steerPwmOutValueI<STEER_PWM_MIN)
    GV_steerPwmOutValueI=STEER_PWM_MIN;
  FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_7, kFTM_EdgeAlignedPwm, 10*1000U,GV_steerPwmOutValueI);
}

void SteerSet(uint16_t pwm)
{
  FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_7, kFTM_EdgeAlignedPwm, 10*1000U,pwm);
}
void Steer_ajust()
{
  static uint16_t duty=730;
  
  if(READ_LEFT)
  {  
    delay_ms(30);
    if(READ_LEFT)
        duty+=1;
    
    if(duty>1000)
      duty=1000;
  }
  if(READ_RIGHT)
  {
    delay_ms(30);
    if(READ_RIGHT)
        duty-=1;
    if(duty<500)
      duty=500;
  }  
  FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_7, kFTM_EdgeAlignedPwm, 10*1000U, duty);
  Display_Number(0,5,duty,YELLOW,RED);
  
}
