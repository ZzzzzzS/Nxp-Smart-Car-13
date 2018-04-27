/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */

#include "include.h"

void PIDInit(pid_control_config_t* base,float P,float I,float D)
{
  memset(base,0,sizeof(pid_control_config_t));

  base->PidCore.Kp=P;
  base->PidCore.Ki=I;
  base->PidCore.Kd=D;
}

void PIDControl(pid_control_config_t* base)
{
  base->PidCore.state[NowError] = base->AimSpeed - base->NowSpeed;

  base->IncrementSpeed = (int16_t)((base->PidCore.Kp) *  (base->PidCore.state[NowError]))+(int16_t)(base->PidCore.Ki * (base->PidCore.state[NowError] + base->PidCore.state[lastError]));
 
  base->PidCore.state[lastestError] = base->PidCore.state[lastError];
  base->PidCore.state[lastError] = base->PidCore.state[NowError];

}

void SpeedComput(speed_control_config_t* base)
{
  base->OutSpeed[LeftWheel]+= base->Pid[LeftWheel].IncrementSpeed;
  base->OutSpeed[RightWheel]+= base->Pid[RightWheel].IncrementSpeed;

  if(base->OutSpeed[LeftWheel]>MAX_SPEED)
    base->OutSpeed[LeftWheel] = MAX_SPEED;
  else if(base->OutSpeed[LeftWheel]<MIN_SPEED)
    base->OutSpeed[LeftWheel] = MIN_SPEED;

  if(base->OutSpeed[RightWheel]>MAX_SPEED)
    base->OutSpeed[RightWheel] = MAX_SPEED;
  else if(base->OutSpeed[RightWheel]<MIN_SPEED)
    base->OutSpeed[RightWheel] = MIN_SPEED;
  
}

void MotorOut(speed_control_config_t *base)
{
  if (base->OutSpeed[RightWheel] >= 0)
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 10*1000U, base->OutSpeed[RightWheel]);		//电机正转
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 10*1000U, 0);
		}
		else if (base->OutSpeed[RightWheel] < 0)																//电机反转
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 10*1000U, 0);		//电机正转
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 10*1000U, -(base->OutSpeed[RightWheel]));
		}

		if (base->OutSpeed[LeftWheel] >= 0)																		//电机正转
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_3, kFTM_EdgeAlignedPwm, 10*1000U, base->OutSpeed[LeftWheel]);		//电机正转
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_2, kFTM_EdgeAlignedPwm, 10*1000U, 0);
		}
		else if (base->OutSpeed[LeftWheel] < 0)																//电机反转
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_3, kFTM_EdgeAlignedPwm, 10*1000U, 0);		//电机正转
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_2, kFTM_EdgeAlignedPwm, 10*1000U, -(base->OutSpeed[LeftWheel]));
		}
}
  
void MotorOut_PWM(uint16_t num)
{
  FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 10*1000U, num);		//电机正转
  FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 10*1000U, 0);
  
  FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_3, kFTM_EdgeAlignedPwm, 10*1000U, num);		//电机正转
  FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_2, kFTM_EdgeAlignedPwm, 10*1000U, 0);
}

void MotorInit()
{
//  ftm_pwm_init(MOTOR_FTM, LEFT_PWM, MOTOR_HZ, 0);      //初始化 电机 PWM
//  ftm_pwm_init(MOTOR_FTM, LEFT_PWM_BACK, MOTOR_HZ, 0);      //初始化 电机 PWM
//  ftm_pwm_init(MOTOR_FTM, RIGHT_PWM, MOTOR_HZ, 0);      //初始化 电机 PWM
//  ftm_pwm_init(MOTOR_FTM, RIGHT_PWM_BACK, MOTOR_HZ, 0);      //初始化 电机 PWM
  
  
        PORT_SetPinMux(PORTC, 1, kPORT_MuxAlt4);
        PORT_SetPinMux(PORTC, 2, kPORT_MuxAlt4);
        PORT_SetPinMux(PORTC, 3, kPORT_MuxAlt4);
        PORT_SetPinMux(PORTC, 4, kPORT_MuxAlt4);
     
        ftm_config_t FTM0Info;
        ftm_chnl_pwm_signal_param_t ftmParam[4];
    
        /* Configures the FTM parameters with frequency 20 kHZ */
        ftmParam[0].chnlNumber = kFTM_Chnl_0;       
        ftmParam[0].level = kFTM_HighTrue;          
        ftmParam[0].dutyCyclePrecision = 10*1000U;  
        ftmParam[0].dutyCyclePercent = 0U;          
        ftmParam[0].firstEdgeDelayPercent = 0U;     
        
        ftmParam[1].chnlNumber = kFTM_Chnl_1;       
        ftmParam[1].level = kFTM_HighTrue;          
        ftmParam[1].dutyCyclePrecision = 10*1000U;  
        ftmParam[1].dutyCyclePercent = 0U;          
        ftmParam[1].firstEdgeDelayPercent = 0U;     
        
        ftmParam[2].chnlNumber = kFTM_Chnl_2;       
        ftmParam[2].level = kFTM_HighTrue;          
        ftmParam[2].dutyCyclePrecision = 10*1000U;  
        ftmParam[2].dutyCyclePercent = 0U;          
        ftmParam[2].firstEdgeDelayPercent = 0U;     
        
        ftmParam[3].chnlNumber = kFTM_Chnl_3;       
        ftmParam[3].level = kFTM_HighTrue;          
        ftmParam[3].dutyCyclePrecision = 10*1000U;  
        ftmParam[3].dutyCyclePercent = 0U;          
        ftmParam[3].firstEdgeDelayPercent = 0U;     
        
        
        FTM_GetDefaultConfig(&FTM0Info);
        //FTM0Info.prescale = kFTM_Prescale_Divide_4;
        //FTM0Info.pwmSyncMode  = kFTM_HardwareTrigger_0;
        FTM0Info.reloadPoints = kFTM_CntMax;
        FTM0Info.chnlPolarity = 0;
        
        /* Initializes the FTM module. */
        FTM_Init(FTM0, &FTM0Info);
        FTM_SetupPwm(FTM0, ftmParam, sizeof(ftmParam)/sizeof(ftm_chnl_pwm_signal_param_t), kFTM_EdgeAlignedPwm, 20*1000U, CLOCK_GetFixedFreqClkFreq());    // Ƶ��20K
        FTM_StartTimer(FTM0, kFTM_FixedClock);
        
        //FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 10*1000U, 50);
        //FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 10*1000U, 50);
        //FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_2, kFTM_EdgeAlignedPwm, 10*1000U, 50);
        //FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_3, kFTM_EdgeAlignedPwm, 10*1000U, 50);
  
}
