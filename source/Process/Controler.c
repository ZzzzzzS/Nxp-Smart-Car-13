#include "include.h"

void SteerControlor()
{
    SteerPWMCalculator();
    SteerOut();
}

void ImageControlor(uint8_t* img)
{
        uint8_t use_flag = 1;
        uint32_t big_sum=0;
        uint32_t big_sum_count=0;
        
        
        if(READ_LEFT){
          g_Speed+=100;
          Display_Number(0,6,g_Speed,YELLOW,RED);
        }
        
        //自动调节阈值
        for(int loop=40*94;loop<120*184;loop+=8)
        {
          big_sum+=img[loop];
          big_sum_count++;
        }
        
        divide_gray = big_sum/big_sum_count;
        
        getSmallImage(img,small_image);
        if(Using_Flag==Using_A)
           Using_Flag=Using_B;
        else if(Using_Flag==Using_B)
            Using_Flag=Using_A;
        
        if((small_image[3][20]&&small_image[3][70]&&small_image[55][20]&&small_image[55][70])||(small_image[3][20]==0&&small_image[3][70]==0&&small_image[55][20]==0&&small_image[55][70]==0))
            use_flag=0;
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

          SteerControlor();
        }
        
        
        
}
