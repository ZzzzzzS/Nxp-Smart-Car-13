#include "include.h"

void SteerControlor()
{
    SteerPWMCalculator(0);
    SteerOut();
}

void ImageControlor(uint8_t* img)  //列188，行120
{
        uint8_t use_flag = 1;
		uint16_t Left_One=0;
		uint16_t Right_One=0;

   		Left_One  =(uint16_t)InductanceVal[0];
        Right_One =(uint16_t)InductanceVal[1];

        
        if(READ_LEFT){
          g_Speed+=100;
          if(g_Speed>10000)
            g_Speed=0;
          Display_Number(0,6,g_Speed,YELLOW,RED);
        }
		        
		//缩放加二值化
       getSmallImage(img,small_image);
        

        if(Using_Flag==Using_A)
           Using_Flag=Using_B;
        else if(Using_Flag==Using_B)
            Using_Flag=Using_A;
        
        //if((small_image[3][20]&&small_image[3][70]&&small_image[55][20]&&small_image[55][70])||(small_image[3][20]==0&&small_image[3][70]==0&&small_image[55][20]==0&&small_image[55][70]==0))
          //  use_flag=0;
        if(use_flag)
        {
          //correctSmallImage(small_image,converted_image);
          //findWayByPicture(small_image);
          findMiddlePointBySpace(small_image);
          convolution(small_image);
          if(DISPLAY_FLAG){
            LCD_DrawPicture_Small(small_image);
            for(int i=0;i<SpaceMiddles.count;i++)
            {
              PutPixel(SpaceMiddles.points[i].x,SpaceMiddles.points[i].y,RED);
            }
			for(int i=0;i<EdgeLeft.count;i++)
            {
              PutPixel(EdgeLeft.points[i].x,EdgeLeft.points[i].y,RED);
            }
			for(int i=0;i<EdgeRight.count;i++)
            {
              PutPixel(EdgeRight.points[i].x,EdgeRight.points[i].y,RED);
            }
            //UpperCOM_SendImg(small_image,sizeof(small_image));
          }
	  
		  
   		   for(int loop=SpaceMiddles.count-1;loop>0;--loop)
    		{
     		 	if(SpaceMiddles.points[loop].y>33){
        			SpaceMiddles.count=loop+1;
       				break;
    			  }
   			 }

//***************************电感逻辑********************************************//
		 //判断到了圆环附近 
		  if(Left_One>22000&&DISTANCE_RECORD_FLAG==0&&C_OUT==0)
		  {
			  DISTANCE_RECORD_FLAG = 1;
	      }

		  if(DISTANCE_RECORD_FLAG)
		  {
			 if(READ_KEY4&&findColumnSpaceMiddle(small_image,92)>SpaceMiddles.points[SpaceMiddles.count-1].y)
			 {
		 		 SpaceMiddles.points[SpaceMiddles.count-1].x = (SpaceMiddles.points[SpaceMiddles.count-1].x+92)/2;
			 }
			 if(READ_KEY3&&findColumnSpaceMiddle(small_image,3)>SpaceMiddles.points[SpaceMiddles.count-1].y)
			 {
		 		 SpaceMiddles.points[SpaceMiddles.count-1].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+3)/2;
			 }
		  }
		  
		  if(Left_One>20000&&DistanceRecord>1000)
		  {
			  C_OUT = 1;
			  DISTANCE_RECORD_FLAG = 0;
			  DistanceRecord = 0;
		  }

		  if(C_OUT&&Left_One<10000)
		  {
			  C_OUT = 0;
		  }

		  if(I_abs(findColumnSpaceMiddle(small_image,92)-findColumnSpaceMiddle(small_image,3))>10)
				Beep_Up();
		  else 
			  	Beep_Down();
			  

//*********************************************************************************************
          SteerPWMCalculator(0);
   		  SteerOut();
	      //MotorOut(&GV_speedControlT);
		  //停车检查
		  if(!STOP_FLAG)
		  {
			//因为存在远处反光导致误判的原因，先把这个去了，最后再调
			//stop_car(small_image);
		  }

		  		  
          //SendAdValue(InductanceVal,sizeof(InductanceVal));
        }
        
        
}

void stop_car(uint8_t* img)
{
	uint8_t jump_point_count=0;
	uint32_t jump_sum=0;
        
        if(g_Time>500){
		for(int i=0;i<92;i++)
		{
			if(img[50*94+i]!=img[50*94+i+1])
				++jump_point_count;
		}
	}
        if(jump_point_count>=8)
        {
          jump_point_count=0;
          for(int i=0;i<92;i++)
            if(img[50*94+i]==0){
              jump_sum+=i;
              jump_point_count++;
            }
          if(I_abs(jump_sum/jump_point_count-46)<10)
            STOP_FLAG = 1;
        }
        
 
	
}
