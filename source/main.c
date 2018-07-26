/**
 * This is template for main module created by MCUXpresso Project Generator.
// //  *Enjoy!
 **/

#include "include.h"

#define FLASH_IMG 1

bool MT9V034_CaptureAccomplished = false;
volatile uint8_t MT9V034_IMGBUFF_A[MT9V034_H][MT9V034_W] = {0};
volatile uint8_t MT9V034_IMGBUFF_B[MT9V034_H][MT9V034_W] = {0};
volatile uint8_t* IMG_NOW=(uint8_t*)MT9V034_IMGBUFF_A;
uint32_t interflag = 0;


int main(void) 
{
  Init();
  g_Time=1100;

  GV_steerPwmOutValueI=STEER_PWM_MIN;
  FTM_ClearQuadDecoderCounterValue(FTM1);
  FTM_ClearQuadDecoderCounterValue(FTM2);
  getLeftSpeed();
  getRightSpeed();
  if(READ_KEY1)
  {
    CircleQueue.Queue[0]=LEFT;
  }
  else
  {
    CircleQueue.Queue[0]=RIGHT;
  }
  if(READ_KEY3)
  {
    CircleQueue.Queue[1]=LEFT;
  }
  else
  {
    CircleQueue.Queue[1]=RIGHT;
  }
  if(READ_KEY4)
  {
    CircleQueue.Queue[2]=LEFT;
  }
  else
  {
    CircleQueue.Queue[2]=RIGHT;
  }

  delay_ms(25);
  AllDistance=10;
  
  while (1)
  {
    if(!DISPLAY_FLAG)
    {   
        Display_Number(0,1,InductanceVal[LEFT],YELLOW,RED);
        Display_Number(0,2,InductanceVal[MIDDLE],YELLOW,RED);
        Display_Number(0,3,InductanceVal[RIGHT],YELLOW,RED);
        Display_Number(10,1,InductanceVal[FRONT_LEFT],YELLOW,RED);
        Display_Number(10,2,InductanceVal[FRONT_RIGHT],YELLOW,RED);

        Display_Number(0,4,GV_steerControlT.ErrorDistance,YELLOW,RED);
        Display_Number(0,5,GV_speedControlT.Pid[LeftWheel].NowSpeed,YELLOW,RED);
        Display_Number(10,5,GV_speedControlT.Pid[RightWheel].NowSpeed,YELLOW,RED);

        Display_Number(0,7,DistanceAddFlag,YELLOW,RED);
        //Display_Number(5,7,Circle_Flag,YELLOW,RED);
        Display_Number(5,7,Message.distance_between,YELLOW,RED);
        Display_Number(10,7,AllDistance/100,YELLOW,RED);
        
    }
    //meetingControl();
    //stop_car();
    //LCD_DrawPicture(IMG_NOW);
    //led_red(1);   
    //led_red(0);
    InductanceVal[7]=(InductanceVal[LEFT]+InductanceVal[MIDDLE]+InductanceVal[RIGHT]);
    InductanceVal[6]=GV_steerControlT.ErrorDistance;
    InductanceVal[5]=-GV_steerPwmOutValueI +STEER_MIDDLE;
    //SendAdValue(AllDistance, sizeof(AllDistance));//发送到山外上位机显示
    if(Using_Flag==Using_A&&IMG_NOW==(uint8_t*)MT9V034_IMGBUFF_B)
      {
        ImageControlor(MT9V034_IMGBUFF_A);
        Using_Flag=Using_B;
      }
      else if(Using_Flag==Using_B&&IMG_NOW==(uint8_t*)MT9V034_IMGBUFF_A)
      {
        ImageControlor(MT9V034_IMGBUFF_B);
        Using_Flag=Using_A;
      }
    
    //Camera_ajust();
    //if(READ_LEFT)
    //{
     // GV_steerPwmOutValueI+=5;
   // }

   if(g_Time>2000)
   {
     //FinnalPointHandler();
   }
  }
}
