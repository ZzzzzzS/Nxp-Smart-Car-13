#include "include.h"

void SteerControlor()
{
    SteerPWMCalculator(0);
    SteerOut();
}

void ImageControlor(uint8_t* img)  //列188，行120
{
        uint8_t use_flag = 1;
	int16_t Left_One=0;
	int16_t Right_One=0;
	static uint16_t g_Speed_Cp = 0;
   	Left_One  =(int16_t)InductanceVal[0];
        Right_One =(int16_t)InductanceVal[1];
        
        if(READ_LEFT){
          GV_speedControlT.Pid[0].AimSpeed +=10;
          GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
          Display_Number(0,6,GV_speedControlT.Pid[0].AimSpeed,YELLOW,RED);
        }
        
        led_down();
        if(READ_KEY2){
          NRF24L01_SetMode(MODE_TX);
        
          NRF24L01_CE_L;
          NRF24L01_WriteTxPayload_NOACK((uint8_t*)(&Message), sizeof(Message));
      // NRF24L01_WriteTxPayload_NOACK((uint8_t*)data, sizeof(data));
        
        }
    NRF24L01_CE_H;
		        
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
		  if(Left_One>3500&&DISTANCE_RECORD_FLAG==0&&C_OUT==0)
		  {
			  DISTANCE_RECORD_FLAG = 1;
      }

		  if(DISTANCE_RECORD_FLAG)
		  {
                         Beep_Up();
          
                         if(DistanceRecord>2000&&DistanceRecord<4000){
                           if(circle_angle==0)
                             circle_angle = GV_steerPwmOutValueI;
                           else 
                             circle_angle = (GV_steerPwmOutValueI+circle_angle)/2;
                         }
			 if(READ_KEY4/*&&findColumnSpaceMiddle(small_image,92)>SpaceMiddles.points[SpaceMiddles.count-1].y*/)
			 {
                                 if(DistanceRecord<2000){
                                   SpaceMiddles.points[SpaceMiddles.count-1].x = (SpaceMiddles.points[SpaceMiddles.count-1].x+80)/2;
                                  SpaceMiddles.points[SpaceMiddles.count-2].x = (SpaceMiddles.points[SpaceMiddles.count-1].x+75)/2;
                                 }
			 }
			 if(READ_KEY3/*&&findColumnSpaceMiddle(small_image,3)>SpaceMiddles.points[SpaceMiddles.count-1].y*/)
			 {
                                SpaceMiddles.points[SpaceMiddles.count-1].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+10)/2;	
                                if(DistanceRecord<2000){
                                  SpaceMiddles.points[SpaceMiddles.count-1].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+15)/2;
                                  SpaceMiddles.points[SpaceMiddles.count-2].x =(SpaceMiddles.points[SpaceMiddles.count-1].x+30)/2;
                                }
			 }
                
		  }
		  
		  if(Left_One>1500&&DistanceRecord>5000)
		  {
                          GV_speedControlT.Pid[0].PidCore.Kp = 0.8;
                           GV_speedControlT.Pid[1].PidCore.Kp =0.8;
                          GV_speedControlT.Pid[0].AimSpeed = 80;
                          GV_speedControlT.Pid[1].AimSpeed = 80;
                          Circle_Flag++;
                          Beep_Down();
                          circle_angle=0;
			  C_OUT = 1;
			  DISTANCE_RECORD_FLAG = 0;
			  DistanceRecord = 0;
		  }

		  if(C_OUT&&Left_One<1000)
		  {
			  C_OUT = 0;
		  }
//会车
      if(READ_KEY2&&Message.distance_between<1500)
      {
          Message.stop = 22;
          Meet = 1;
      }

      if(!READ_KEY2&&NRF_RxBuf[1]==22)
      {
        Meet = 1;
      }

      if(Meet)
      {
         GV_speedControlT.Pid[0].AimSpeed = 40;
         GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
         img_middle = 60;
      }
      
      if(Meet_distance>1000)
      {
        Message.stop = 10;
      }

      if(Meet_distance>2500)
      {
          Meet = 0;
          Message.stop = 10;
         GV_speedControlT.Pid[0].AimSpeed = 80;
         GV_speedControlT.Pid[1].AimSpeed = GV_speedControlT.Pid[0].AimSpeed;
         img_middle =IMG_MIDDLE ;
         Meet_distance=0;
      }
      

//*********************************************************************************************
          SteerPWMCalculator(0);
   		  SteerOut();
	      //MotorOut(&GV_speedControlT);
		  //停车检查
               if((g_Time>100&&g_Time<150)||(g_Time>325))
		  MotorOut(&GV_speedControlT);
               else 
                 MotorOut_PWM(0);
               
	  	  if(STOP_FLAG) 
	      {
                
	    	img_middle = IMG_MIDDLE - 10;
	    	MotorOut_PWM(0);
		  }
		  if(!STOP_FLAG)
		  {
			//因为存在远处反光导致误判的原因，先把这个去了，最后再调
			stop_car(small_image);
		  }
		  
          //SendAdValue(InductanceVal,sizeof(InductanceVal));
        }
        
        
}

void stop_car(uint8_t* img)
{
	uint8_t jump_point_count=0;
	uint32_t jump_sum=0;
        
        if(g_Time>2000){
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
          if(I_abs(jump_sum/jump_point_count-46)<5)
            STOP_FLAG = 1;
        }
        
	
}
