#include "include.h"

ADside_t ADside[MAX_POSITION];



void AD_Get_side()
{
    uint16_t Read_Data[MAX_POSITION];

    Display_ASCII8X16(0,0,"Uniforming",BLACK,WHITE);

    for(int i=0;i<MAX_POSITION;i++)
    {
        ADside[i].min=10000;
        ADside[i].max=0;
    }

    while(READ_KEY1)
    {
      delay_ms(50);
      GetADCValWithoutUniformization(Read_Data);
      Display_Number(0,1,Read_Data[LEFT],YELLOW,RED);
      Display_Number(0,2,Read_Data[MIDDLE],YELLOW,RED);
      Display_Number(0,3,Read_Data[RIGHT],YELLOW,RED);
      
      Display_Number(0,4,ADside[LEFT].max,YELLOW,RED);
      Display_Number(0,5,ADside[MIDDLE].max,YELLOW,RED);
      Display_Number(0,6,ADside[RIGHT].max,YELLOW,RED);
      Display_Number(9,4,ADside[LEFT].min,YELLOW,RED);
      Display_Number(9,5,ADside[MIDDLE].min,YELLOW,RED);
      Display_Number(9,6,ADside[RIGHT].min,YELLOW,RED);
         
         for(int i=0;i<MAX_POSITION;i++)
         {
            if(Read_Data[i]>ADside[i].max)
                ADside[i].max=Read_Data[i];
            else if(Read_Data[i]<ADside[i].min)
                ADside[i].min=Read_Data[i];
            
            if(ADside[i].min<50)
              ADside[i].min=50;
         }
         
     
    }
}

