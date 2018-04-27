/**
 * This is template for main module created by MCUXpresso Project Generator.
 *Enjoy!
 **/

#include "include.h"

#define FLASH_IMG 1

bool MT9V034_CaptureAccomplished = false;
volatile uint8_t MT9V034_IMGBUFF_A[MT9V034_H][MT9V034_W] = {0};
volatile uint8_t MT9V034_IMGBUFF_B[MT9V034_H][MT9V034_W] = {0};
volatile uint8_t* IMG_NOW=(uint8_t*)MT9V034_IMGBUFF_A;
uint32_t interflag = 0;

int main(void) {

  Init();

  while (1) {
    
    
    
      
    WAIT:
          
//      if(!BuffIsEmpty(&UART_buff))//串口缓冲区不为空
//      {
//        unsigned char data=BuffPop(&UART_buff);//从串口缓冲区弹出一个数据 
//        PushQueue(&Queue,data);//压入到队列中进行分析
//        //这里需要修改
//        //DataAnalysis(&Queue,&point_x,&point_y);
//      }
  
      if(Using_Flag==Using_A&&IMG_NOW==(uint8_t*)MT9V034_IMGBUFF_B)
      {
        ImageControlor(MT9V034_IMGBUFF_A);
      }else if(Using_Flag==Using_B&&IMG_NOW==(uint8_t*)MT9V034_IMGBUFF_A){
        ImageControlor(MT9V034_IMGBUFF_B);
      }else{
        goto WAIT;
      }
    
  }
}
