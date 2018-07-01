#include "include.h"

ADside_t ADside[MAX_POSITION];



void AD_Get_side()
{
    uint16_t Read_Data[MAX_POSITION];

    Display_ASCII8X16(0,0,"Uniforming",BLACK,WHITE);

    for(int i=0;i<MAX_POSITION;i++)
    {
        ADside[i].max=10000;
    }

    while(READ_KEY1)
    {
		 GetADCValWithoutUniformization(Read_Data);
         
         for(int i=0;i<MAX_POSITION;i++)
         {
            if(Read_Data[i]>ADside[i].max)
                ADside[i].max=Read_Data[i];
            else if(Read_Data[i]<ADside[i].min)
                ADside[i].min=Read_Data[i];
         }
    }
}

