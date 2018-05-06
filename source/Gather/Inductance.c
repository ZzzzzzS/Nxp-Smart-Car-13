#include "include.h"

ADside  Left_side={0,10000},Right_side={0,10000};


void AD_Get_side()
{
    uint16_t Read_Data[2];

    Display_ASCII8X16(0,0,"BE ONEing",BLACK,WHITE);
    while(READ_KEY1)
    {
		
		 GetADCVal(Read_Data);
         
         if(Read_Data[0]>Left_side.max)
			 Left_side.max=Read_Data[0];
         if(Read_Data[0]<Left_side.min)
			 Left_side.min=Read_Data[0];
         if(Read_Data[1]>Right_side.max)
			 Right_side.max=Read_Data[1];
         if(Read_Data[1]<Right_side.min)
			 Right_side.min=Read_Data[1];

    }
}

