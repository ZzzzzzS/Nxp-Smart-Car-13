#include "include.h"

void SteerControlor()
{
    SteerPWMCalculator(0);
    SteerOut();
}

void ImageControlor(uint8_t* img)  //ÁÐ188£¬ÐÐ120
{
        uint8_t use_flag = 1;
		uint16_t Left_One=0;
		uint16_t Right_One=0;
		uint8_t delay_count=0;

   		Left_One  =(uint16_t)(100*(InductanceVal[0]-Left_side.min)/(Left_side.max-Left_side.min));
        Right_One =(uint16_t)(100*(InductanceVal[1]-Right_side.min)/(Right_side.max-Right_side.min));

        
        if(READ_LEFT){
          g_Speed+=100;
          if(g_Speed>10000)
            g_Speed=0;
          Display_Number(0,6,g_Speed,YELLOW,RED);
        }
        
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
		  
		  if(Left_One>100){
			 if(DISTANCE_RECORD_FLAG==0&&DistanceRecord<1000){
			 	DISTANCE_RECORD_FLAG=1;
				 if((LeftOrRight=JudgeDirection(small_image))=='l')
         	 		SteerPWMCalculator(-30);
				 else 
         	 		SteerPWMCalculator(30);
				delay_count = 10;
			 }else{
			 	if(DistanceRecord>2000)
				{
					DISTANCE_RECORD_FLAG = 0;
				}
			 }
		  }
		  else{
			 if(delay_count!=0)
				delay_count--;
			 else 
				SteerPWMCalculator(0);
		  }

		  if(DISTANCE_RECORD_FLAG==0&&DistanceRecord>5000)
			  DistanceRecord = 0;

		  if(DISTANCE_RECORD_FLAG&&DistanceRecord>10000)
			  DISTANCE_RECORD_FLAG=0;

   		  SteerOut();
		  
          //SendAdValue(InductanceVal,sizeof(InductanceVal));
        }
        
        
}
