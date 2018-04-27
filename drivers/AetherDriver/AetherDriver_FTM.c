#include "include.h"

/*============================================
函数名：ftm_pwm_init(FTM_Type* ftmn, uint8_t ch, uint32_t freq, uint32_t duty)
作用:PWM初始化
作者:ZZS
说明:和山外函数唯一区别就是不会设置port管脚,需要自己设置
==========================================*/
void ftm_pwm_init(FTM_Type* ftmn, uint8_t ch, uint32_t freq, uint32_t duty)
{
  uint32_t clk_hz ;
  uint16_t mod;
  uint8_t  ps;
  uint16_t cv;
  
  if(ftmn==FTM0)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
  }
  else if(ftmn==FTM1)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
  }
  else if(ftmn==FTM2)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM2_MASK;
  }
  else if(ftmn==FTM3)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM3_MASK;
  }
  
  clk_hz = CLOCK_GetBusClkFreq();     // bus频率
  mod = (clk_hz >> 16 ) / freq ;      // 临时用 mod 缓存一下
  ps = 0;
  while((mod >> ps) >= 1)             // 等 (mod >> ps) < 1 才退出 while 循环 ，即求 PS 的最小值
  {
      ps++;
  }
  assert(ps <= 0x07);                 // 断言， PS 最大为 0x07 ，超过此值，则 PWM频率设置过低，或 Bus 频率过高
  mod = (clk_hz >> ps) / freq;        // 求 MOD 的值
  
  if(ftmn==FTM0)
  {
    cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
  }
  else if(ftmn==FTM1)
  {
    cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
  }
  else if(ftmn==FTM2)
  {
    cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
  }
  else if(ftmn==FTM3)
  {
    cv = (duty * (mod - 0 + 1)) / FTM3_PRECISON;
  }
  
  ftmn->SC |= FTM_SC_CLKS(1);
  ftmn->SC |= FTM_SC_PS(ps);
  
  FTM0->MOD = mod;
  
  ftmn->CONTROLS[ch].CnSC &=~FTM_CnSC_ELSA_MASK;
  ftmn->CONTROLS[ch].CnSC |= ( FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK | FTM_CnSC_DMA_MASK);
  ftmn->CONTROLS[ch].CnV = cv;
  
  ftmn->CNTIN = 0;
  
  ftmn->CNT = 0;
}

/*============================================
函数名：ftm_pwm_duty(FTM_Type* ftmn, uint8_t ch, uint32_t duty)
作用:PWM设置占空比
作者:ZZS
说明:用法和山外一样
==========================================*/

void ftm_pwm_duty(FTM_Type* ftmn, uint8_t ch, uint32_t duty)
{
  uint32_t cv;
  uint32_t mod = 0;
  mod=ftmn->MOD;
  
  if(ftmn==FTM0)
  {
    cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
  }
  else if(ftmn==FTM1)
  {
    cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
  }
  else if(ftmn==FTM2)
  {
    cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
  }
  else if(ftmn==FTM3)
  {
    cv = (duty * (mod - 0 + 1)) / FTM3_PRECISON;
  }
  
  ftmn->CONTROLS[ch].CnV = cv;
}

/*============================================
函数名：ftm_quad_init(FTM_Type* ftmn)
作用:初始化正交解码
作者:ZZS
说明:和山外函数唯一区别就是不会设置port管脚,需要自己设置
==========================================*/

void ftm_quad_init(FTM_Type* ftmn)
{
  
  if(ftmn==FTM0)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
  }
  else if(ftmn==FTM1)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
  }
  else if(ftmn==FTM2)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM2_MASK;
  }
  else if(ftmn==FTM3)
  {
    SIM->SCGC6 |= SIM_SCGC6_FTM3_MASK;
  }
  
  ftmn->MODE |= FTM_MODE_WPDIS_MASK;
  ftmn->MODE |= FTM_MODE_FTMEN_MASK;
  
  ftmn->QDCTRL |= FTM_QDCTRL_QUADMODE_MASK;
   
  ftmn->CNTIN = 0;
  
  ftmn->MOD = FTM_MOD_MOD_MASK;
  
  ftmn->QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  
  ftmn->CNT = 0;
}