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
  
  while (1)
  {
    delay_ms(100);
    Display_Number(0,1,InductanceVal[LEFT],YELLOW,RED);
    Display_Number(0,2,InductanceVal[MIDDLE],YELLOW,RED);
    Display_Number(0,3,InductanceVal[RIGHT],YELLOW,RED);
    //meetingControl();
    //stop_car();
    //LCD_DrawPicture(IMG_NOW);
    led_red(1);
    delay_ms(100);
    led_red(0);
    
  }
}
