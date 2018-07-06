/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,Aether
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属Aether所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留Aether的版权声明。
 */

#ifndef __GLOBALSTRUCTURES_H__
#define __GLOBALSTRUCTURES_H__

#define ARM_MATH_CM7                    //定义内核为CM7内核
#include "MKV58F24.h"
#include "fsl_common.h"
#include "arm_math.h"


//#define CAR_NEW
/*============================================
电机控制相关定义
==========================================*/

#define MOTOR_HZ    17000       //定义电机工作频率
#define MOTOR_FTM			FTM0
#define RIGHT_PWM_BACK	3
#define RIGHT_PWM       4
#define LEFT_PWM	1
#define LEFT_PWM_BACK	2

#define MAX_SPEED  5000
#define MIN_SPEED  -5000


typedef enum
{
  LeftWheel,
  RightWheel
}wheel_e;

typedef enum        					//PID误差枚举
{
	NowError,
	lastError,
	lastestError
}PID_Error_e;

typedef struct
{
  int16_t SetSpeed;
  int16_t AimSpeed;                 //pid目标速度
  int16_t NowSpeed;	                //pid当前速度
  int16_t IncrementSpeed;           //pid速度增量(pid输出结果)
  arm_pid_instance_f32 PidCore;     //pid结构体
}pid_control_config_t;

typedef struct
{
  pid_control_config_t Pid[2];
  int16_t OutSpeed[2];
}speed_control_config_t;


typedef struct 
{
	uint8_t  stop;
	uint8_t  Empty;
	uint16_t distance_between;
}Message_t; 
//Soft IIC
#define SDA_GPIO GPIOC
#define SDA_PIN 11
#define SCL_GPIO GPIOC
#define SCL_PIN 10

/*============================================
舵机控制相关定义
==========================================*/
#define STEER_BASE_PORT PORTD
#define STEER_PIN  0U
#define STEER_FTM FTM3
#define STEER_FTM_CHANAL 0
#define STEER_FTM_FREQ  100
#define INDUCTANCE_MIDDLE  0
#define MEETING_MIDDLE  20

extern uint16_t STEER_MIDDLE;

typedef struct{
  float Steer_P;
  float Steer_D;
  float Steer_P_Small;
  float Steer_D_Small;
}steer_PD_control_config_t;

typedef struct{
  int16_t ErrorDistance;
  int16_t LastErrorDistance;
  steer_PD_control_config_t PD;
}steer_config_t;

typedef enum{
  IMG_A,
  IMG_B,
  IMG_N
}IMGS;

//双数组采集互斥元
typedef enum{
	Using_A,
	Using_B
}Using_Status;

/*============================================
电感采集相关
==========================================*/
typedef enum 		//枚举定义电感位置
{
	LEFT,
        RIGHT,
        MIDDLE,
	FRONT_LEFT,
	FRONT_RIGHT,
  MAX_POSITION
}InductancePosition_e;


#define Rk 1
#define Rb 0
#define Lk 1
#define Lb 0

#endif
