#include "include.h"

//通过局部变量减少除法运算
static const uint8_t wigth = MT9V034_W/2;
static const uint8_t height = MT9V034_H/2;
static const uint8_t midline = MT9V034_W/4;   //寻线的中点
uint8_t divide_gray=60;
//用来存储所有边界
LineBorder linesborder[MT9V034_H/2];

uint8_t small_image[MT9V034_H/2][MT9V034_W/2];
uint8_t converted_image[MT9V034_H/2][MT9V034_W/2];

// 
//
// 以下为人工势场
//
//　

#if 0
uint8_t buffer_list[Circle_Big_R+2][Circle_Big_R+2]={0};

Point center={(uint8_t)((Circle_Big_R+2)/2),(uint8_t)((Circle_Big_R+2)/2)};

float circle_cos[8] = {0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.0};
float circle_sin[8] = {0.714,0.8,0.86,0.92,0.95,0.98,0.99,1};


__ramfunc int16_t ROUND(float num)
{
	return num-(int)num>=0.5? (int)(num+1):(int)(num);
}

__ramfunc void plant(void)
{
	uint8_t tempX=0;
	uint8_t tempY=0;
	//画布中心点

	for(int i=0;i<8;i++)
	{
		tempX=ROUND(Circle_R*circle_cos[i]);
		tempY=ROUND(Circle_R*circle_sin[i]);

		buffer_list[center.y+tempY][center.x+tempX]=1;
		buffer_list[center.y+tempY][center.x-tempX]=1;
		buffer_list[center.y-tempY][center.x+tempX]=1;
		buffer_list[center.y-tempY][center.x-tempX]=1;
		
		tempY=ROUND(Circle_R*circle_cos[i]);
		tempX=ROUND(Circle_R*circle_sin[i]);

		buffer_list[center.y+tempY][center.x+tempX]=1;
		buffer_list[center.y+tempY][center.x-tempX]=1;
		buffer_list[center.y-tempY][center.x+tempX]=1;
		buffer_list[center.y-tempY][center.x-tempX]=1;

		tempX=ROUND(Circle_Big_R*circle_cos[i]);
		tempY=ROUND(Circle_Big_R*circle_sin[i]);

		buffer_list[center.y+tempY][center.x+tempX]=1;
		buffer_list[center.y+tempY][center.x-tempX]=1;
		buffer_list[center.y-tempY][center.x+tempX]=1;
		buffer_list[center.y-tempY][center.x-tempX]=1;
		
		tempY=ROUND(Circle_Big_R*circle_cos[i]);
		tempX=ROUND(Circle_Big_R*circle_sin[i]);

		buffer_list[center.y+tempY][center.x+tempX]=1;
		buffer_list[center.y+tempY][center.x-tempX]=1;
		buffer_list[center.y-tempY][center.x+tempX]=1;
		buffer_list[center.y-tempY][center.x-tempX]=1;

	}
}

__ramfunc void repulation_small(uint8_t* img,Point NowPoint,Point* target)
{
   int32_t addX=0;
   int32_t addY=0;
   int16_t distanceX=0;
   int16_t distanceY=0;
   
   for(int row = center.y-Circle_R;row<=center.y+Circle_R;row++)
	   for(int col = center.x-Circle_R;col<=center.x+Circle_R;col++)
	   {
		   if(buffer_list[row][col]==1)
		   {
			   distanceX = col - center.x;
			   distanceY = row - center.x;
			
			 if(NowPoint.y+distanceY>0&&NowPoint.y+distanceY<60&&NowPoint.x+distanceX>0&&NowPoint.x+distanceX<94)
			   if(img[NowPoint.y+distanceY*MT9V034_W/2+NowPoint.x+distanceX]==0)
			   {
					addX-=distanceX;
					addY-=distanceY;
			   }
		   }

	   }
   target->x+=addX;
   target->y+=addY;
 
}

__ramfunc void repulation_big(uint8_t* img,Point NowPoint,Point* target)
{
   int32_t addX=0;
   int32_t addY=0;
   int16_t distanceX=0;
   int16_t distanceY=0;
   
   for(int row = 0;row<Circle_Big_R+2;row++)
	   for(int col = 0;col<Circle_Big_R+2;col++)
	   {
		 if(!(row>center.y-Circle_R&&row<center.y+Circle_R&&col>center.x-Circle_R&&col<center.x+Circle_R))
		   if(buffer_list[row][col]==1)
		   {
			   distanceX = col - center.x;
			   distanceY = row - center.x;
			   
			 if(NowPoint.y+distanceY>0&&NowPoint.y+distanceY<60&&NowPoint.x+distanceX>0&&NowPoint.x+distanceX<94)
			   if(img[NowPoint.y+distanceY*MT9V034_W/2+NowPoint.x+distanceX]==0)
			   {
					addX-=distanceX;
					addY-=distanceY;
			   }
		   }

	   }
   target->x+=addX;
   target->y+=addY;
   
}

__ramfunc void gravitation(Point NowPoint,Point* target,float32_t GravitationK,float32_t K_Up)
{
  float32_t deltaX = 0.0;
  float32_t deltaY = 0.0;
  Point GravF;
  deltaX = NowPoint.x - target->x;
  deltaY = NowPoint.y - target->y;
  deltaY = deltaY-F_abs(deltaX)* NowPoint.y*NowPoint.y/ K_Up;
  
  GravF.x = ROUND( GravitationK * deltaX / sqrt( deltaX*deltaX + deltaY*deltaY ) );
  GravF.y = ROUND( GravitationK * deltaY / sqrt( deltaX*deltaX + deltaY*deltaY ) );
  
  if(target->x+GravF.x>0&&target->x+GravF.x<94&&target->y+GravF.y>0&&target->y+GravF.y<60)
  {
  	target->x+=GravF.x;
  	target->y+=GravF.y;
  }
}


__ramfunc void generatepath(uint8_t* img)
{
	Point nowpoint = {47,START_LINE};
	Point targetPoint;
	targetPoint.x = nowpoint.x;
	targetPoint.y = nowpoint.y-1;

	for(int i = START_LINE;i>0;i++)
	{
	  gravitation(nowpoint,&targetPoint,200,5);
	  if(targetPoint.x>0&&targetPoint.x<94&&targetPoint.y>0&&targetPoint.y<60)
	  {
	  
	    repulation_small(img,nowpoint,&targetPoint);
		repulation_big(img,nowpoint,&targetPoint);
		
	  	if(targetPoint.x>0&&targetPoint.x<94&&targetPoint.y>0&&targetPoint.y<60)
		{
			nowpoint.x = targetPoint.x;
			nowpoint.y = targetPoint.y;
			
			targetPoint.y-=1;

		}
	  }else{
		  break;
	  }
	}
	
	targetPoint.x = nowpoint.x;
	targetPoint.y = nowpoint.y+1;

	for(int i=nowpoint.y;i<60;i++)
	{
	  gravitation(nowpoint,&targetPoint,-200,5);
	  if(targetPoint.x>0&&targetPoint.x<94&&targetPoint.y>0&&targetPoint.y<60)
	  {
	  
	    repulation_small(img,nowpoint,&targetPoint);
		repulation_big(img,nowpoint,&targetPoint);
		
	  	if(targetPoint.x>0&&targetPoint.x<94&&targetPoint.y>0&&targetPoint.y<60)
		{
			nowpoint.x = targetPoint.x;
			nowpoint.y = targetPoint.y;
			
			
			targetPoint.y-=1;

		}
	  }else{
		  break;
	  }

	}	
}
#endif 
// 
//				以上为人工势场
//

/*
__ramfunc void convolution(uint8_t* img)
{
	EdgeLeft.count=0;
	EdgeRight.count=0;
        
        Point Max_L;
        Point Min_L;
        Point Max_R;
        Point Min_R;
        
	for(int i=0;i<SpaceMiddles.count;i++)
	{
                
		for(int j=SpaceMiddles.points[i].x;j>1;--j)
			if(img[SpaceMiddles.points[i].y*94+j]==0&&img[SpaceMiddles.points[i].y*94+j-1]==0&&img[SpaceMiddles.points[i].y*94+j-2]==0)
			{
                                if(EdgeLeft.count==0)
                                {
                                  Max_L.x = j;
                                  Max_L.y = SpaceMiddles.points[i].y;
                                  Min_L.x = j;
                                  Min_L.y = SpaceMiddles.points[i].y;
                                }
                                
                                if(EdgeLeft.count>10&&Max_L.x!=Min_L.x)
                                {
                                  if(Min_L.x == EdgeLeft.points[0].x&&j>=Max_L.x)
                                  {
                                    EdgeLeft.points[EdgeLeft.count].x=j;
                                    EdgeLeft.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                    ++EdgeLeft.count;
                                  }else if(Max_L.x == EdgeLeft.points[0].x && j<= Min_L.x)
                                  {
                                    EdgeLeft.points[EdgeLeft.count].x=j;
                                    EdgeLeft.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                    ++EdgeLeft.count;
                                  }
                                 
                                }else
                                {
                                  if(j>Max_L.x){
                                    Max_L.x = j;
                                    Max_L.y = SpaceMiddles.points[i].y;
                                  }
                                  if(j<Min_L.x){
                                    Min_L.x = j;
                                    Min_L.y = SpaceMiddles.points[i].y;
                                  }
                            
                                  EdgeLeft.points[EdgeLeft.count].x=j;
                                  EdgeLeft.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                  ++EdgeLeft.count;
                                }
								break;
			}
		for(int j=SpaceMiddles.points[i].x;j<=90;++j)
			if(img[SpaceMiddles.points[i].y*94+j]==0&&img[SpaceMiddles.points[i].y*94+j+1]==0&&img[SpaceMiddles.points[i].y*94+j+2]==0)
			{
                                if(EdgeRight.count==0)
                                {
                                  Max_R.x = j;
                                  Max_R.y = SpaceMiddles.points[i].y;
                                  Min_R.x = j;
                                  Min_R.y = SpaceMiddles.points[i].y;
                                }
                                
                                if(EdgeRight.count>10&&Max_R.x!=Min_R.x)
                                {
                                  if(Min_R.x == EdgeRight.points[0].x&&j>=Max_R.x)
                                  {
                                    EdgeRight.points[EdgeLeft.count].x=j;
                                    EdgeRight.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                    ++EdgeRight.count;
                                  }else if(Max_R.x == EdgeRight.points[0].x && j<= Min_R.x)
                                  {
                                    EdgeRight.points[EdgeLeft.count].x=j;
                                    EdgeRight.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                    ++EdgeRight.count;
                                  }
                                 
                                }else
                                {
                                  if(j>Max_R.x){
                                    Max_R.x = j;
                                    Max_R.y = SpaceMiddles.points[i].y;
                                  }
                                  if(j<Min_R.x){
                                    Min_R.x = j;
                                    Min_R.y = SpaceMiddles.points[i].y;
                                  }
                            
                                  EdgeRight.points[EdgeLeft.count].x=j;
                                  EdgeRight.points[EdgeLeft.count].y=SpaceMiddles.points[i].y;
                                  ++EdgeRight.count;
                                }
				break;
			}
	}

}


__ramfunc uint8_t JudgeDirection(uint8_t* img)
{
	uint8_t left_black_count = 0 ;
	uint8_t right_black_count = 0;

	for(int i = 20;i<60;i++)
	{
		if(img[i*94+3]==0)
			left_black_count++;
		if(img[i*94+90]==0)
			right_black_count++;
	}

	if(left_black_count<right_black_count)
		return 'l';
	else 
		return 'r';
}	
__ramfunc void findMiddlePointBySpace(uint8_t* img)
{
	uint32_t sum_temp=0;
	uint8_t sum_count_temp=0;
	Stack line_has_points_temp;
  Stack Usable_Point_temp;
	line_has_points_temp.count = 0;
  Usable_Point_temp.count = 0;
        Point Max;
        Point Min;
        
	SpaceMiddles.count = 0;
	for(int i=58;i>25;i-=1)
	{
		line_has_points_temp.count = 0;
		//扫描行
		for(int j=0;j<94;j++)
		{

			   if(img[i*94+j]!=0)
				{
					sum_count_temp++;
					sum_temp+=j;
				}else{
					if(sum_count_temp!=0)
					{
						line_has_points_temp.points[line_has_points_temp.count].x = (uint8_t)(sum_temp /(uint32_t)sum_count_temp);
						line_has_points_temp.points[line_has_points_temp.count].y = i;
                                                int offset = line_has_points_temp.points[line_has_points_temp.count].y*94+line_has_points_temp.points[line_has_points_temp.count].x;
                                                if(!(img[offset-1]==0||img[offset-2]==0||img[offset+1]==0||img[offset+2]==0))
                                                  line_has_points_temp.count++;
						
						sum_temp=0;
						sum_count_temp=0;
					}
				}
		}
                if(sum_count_temp!=0)
                {
                  line_has_points_temp.points[line_has_points_temp.count].x = (uint8_t)(sum_temp /(uint32_t)sum_count_temp);
                  line_has_points_temp.points[line_has_points_temp.count].y = i;
                  line_has_points_temp.count++;
                  sum_temp=0;
                  sum_count_temp=0;
                }
		//存在白点
		if(line_has_points_temp.count!=0)
		{
			//判断是不是第一行
			if(SpaceMiddles.count==0){
                                if(i!=58)
                                  break;
				//是第一行直接取第一个白点中心
                                uint8_t min = 0;
                                uint8_t min_value = I_abs(line_has_points_temp.points[0].x-46);
                                for(int loop=0;loop<line_has_points_temp.count;loop++)
                                {
                                    if(I_abs(line_has_points_temp.points[loop].x-46)<min_value)
                                    {
                                      min_value = I_abs(line_has_points_temp.points[loop].x-46);
                                      min = loop;
                                    }
                                }
                                Max.x = line_has_points_temp.points[min].x;
                                Max.y = line_has_points_temp.points[min].y;
                                
                                Min.x = line_has_points_temp.points[min].x;
                                Min.y = line_has_points_temp.points[min].y;
                                
				SpaceMiddles.points[SpaceMiddles.count].x = line_has_points_temp.points[min].x;
				SpaceMiddles.points[SpaceMiddles.count].y = line_has_points_temp.points[min].y;
				SpaceMiddles.count++;
			}else{
				//不是第一行，遍历该行所有白点中心
        Usable_Point_temp.count = 0;
				for(int loop = 0;loop<line_has_points_temp.count;loop++)
				{
					
					int test_flag=0;
					//求每个白点中心和上一个有效点的距离
					int disX = line_has_points_temp.points[loop].x-SpaceMiddles.points[SpaceMiddles.count-1].x;
					int disY = line_has_points_temp.points[loop].y-SpaceMiddles.points[SpaceMiddles.count-1].y;
					//避免后面的除０错误
					if(disX==0){
						for(int loop_in=1;loop_in<I_abs(disY);loop_in++)
						{
							//检测白点中心和上一个有效点的连线上是否存在黑点
							if(img[(SpaceMiddles.points[SpaceMiddles.count-1].y-loop_in)*94+SpaceMiddles.points[SpaceMiddles.count-1].x]==0)
							{test_flag=1;break;}
						}
                                       
						//该白点中心作废，下一个
						if(test_flag)
							continue;
						//否则，取用该白点中心作为有效点
            Usable_Point_temp.points[Usable_Point_temp.count].x = line_has_points_temp.points[loop].x;
            Usable_Point_temp.points[Usable_Point_temp.count].y = line_has_points_temp.points[loop].y;
            Usable_Point_temp.count++;
					}
					//斜率
					float dis_temp  = (float)disY/(float)disX;
					for(int loop_in = 1 ;loop_in < I_abs(disX);loop_in++)
					{
						if(img[94*(SpaceMiddles.points[SpaceMiddles.count-1].y+(int8_t)(loop_in*disX/I_abs(disX)*dis_temp))+SpaceMiddles.points[SpaceMiddles.count-1].x+loop_in*disX/I_abs(disX)]==0)
						{test_flag=1;break;}
					}
                                        if(I_abs(disX)>20)
                                          test_flag=1;
                                        if(SpaceMiddles.count>10&&Max.x!=Min.x)
                                        {
                                          if(Min.x == SpaceMiddles.points[0].x&&line_has_points_temp.points[loop].x<Max.x)
                                            test_flag = 1;
                                          if(Max.x == SpaceMiddles.points[0].x&&line_has_points_temp.points[loop].x>Min.x)
                                            test_flag = 1;
                                        }
					if(test_flag)
						continue;
                                        
                                        if(line_has_points_temp.points[loop].x>=Max.x)
                                        {
                                          Max.x = line_has_points_temp.points[loop].x;
                                          Max.y = line_has_points_temp.points[loop].y;
                                        }
                                        if(line_has_points_temp.points[loop].x<=Min.x)
                                        {
                                          Min.x = line_has_points_temp.points[loop].x;
                                          Min.y = line_has_points_temp.points[loop].y;
                                        }
                                        
                                        
		  Usable_Point_temp.points[Usable_Point_temp.count].x = line_has_points_temp.points[loop].x;
          Usable_Point_temp.points[Usable_Point_temp.count].y = line_has_points_temp.points[loop].y;
          Usable_Point_temp.count++;    
				}

                SpaceMiddles.points[SpaceMiddles.count].x = Usable_Point_temp.points[0].x;
                SpaceMiddles.points[SpaceMiddles.count].y = Usable_Point_temp.points[0].y;
                SpaceMiddles.count++;
			}
		}
	}
}

uint8_t findColumnSpaceMiddle(uint8_t* img,uint8_t row)
{
	uint32_t sum=0;
	uint8_t sum_count=0;
	for(int i=59;i>20;i--)
	{
		if(img[i*94+row]!=0)
		{
			sum+=i;
			sum_count++;
		}
	}
	
	return sum_count>0? sum/sum_count : 0;
}

__ramfunc uint8_t findOurCircle(uint8_t* img)
{
	uint8_t topline = 25;
	uint8_t bottomline =40;
	uint8_t topcount = 0;
	uint8_t bottomcount = 0;

   	for(int i=0;i<93;i++)
	{
		if(img[topline*94+i]!=0)
			topcount++;
		if(img[bottomline*94+i]==0)
			bottomcount++;
	}


	Display_Number(0,3,topcount,WHITE,BLACK);
	Display_Number(4,3,bottomcount,WHITE,BLACK);

	if(bottomcount<5&&topline<5)
		return 1;
	else 
		return 0;

}
__ramfunc uint8_t findCircle(uint8_t* img)
{
	uint8_t middle = 47;
	uint8_t in_count_right = 0;
	uint8_t small_right = 100;
	uint8_t index_right=50;
	uint8_t in_count_left = 0;
	uint8_t index_left=50;
	uint8_t small_left=100;
	uint8_t right_flag=0;
	uint8_t left_flag=0;

	for(int i=42;i>27;i--)
	{

		in_count_left = in_count_right = 0;
		for(int r=middle,l=middle;r<92;r++,l--)
		{
			if(img[i*94+r]!=0)
				in_count_right++;
			if(img[i*94+l]!=0)
				in_count_left++;
		}
		if(in_count_right<small_right)
		{
			small_right = in_count_right;
			index_right = i;
		}
		if(in_count_left<small_left)
		{
			small_left=in_count_left;
			index_left = i;
		}

	}
	if(I_abs(26-index_right)!=0&&I_abs(index_right-42)!=0)
	{
		right_flag=1;
	}
	
	if(I_abs(26-index_left)!=0&&I_abs(index_left-42)!=0)
	{
		left_flag =1;
	}

	Display_Number(0,4,index_left,WHITE,BLACK);
	Display_Number(4,4,index_right,WHITE,BLACK);

	if(!left_flag&&!right_flag)
		return 0;
	else if(left_flag&&right_flag)
		return 1;
	else if(left_flag)
		return 2;
	else 
		return 3;	
}
*/

__ramfunc uint8_t getSmallImage(uint8_t* origin_image, uint8_t* newimage)
{
	 uint8_t column = 94;             //列
    uint8_t row = 0;                //行
	uint32_t line_sum = 0;
	uint32_t average = 0;

    for(int i=MT9V034_W-1;i>=0;i-=2)
    {
        row = 0;
	line_sum = 0;
        for(int j=0;j<MT9V034_H;j+=2)
        {
            //隔点选取并二值化
			line_sum += origin_image[j*MT9V034_W+i];
        }

		if(average==0)
			average = line_sum*2/MT9V034_H;
		else 
			average = (line_sum*2/MT9V034_H + average) / 2;
		
		

		for(int j=0;j<MT9V034_H;j+=2)
		{
			newimage[row*94+column] = origin_image[j*MT9V034_W+i]<average? 0:255;
			if(origin_image[j*MT9V034_W+i]>180)
				newimage[row*94+column]=255;
			else if(origin_image[j*MT9V034_W+i]<40)
				newimage[row*94+column]=0;
			++row;
		}
        --column;
    }
    return column>wigth||row>height? 0:1;   //对数组越界进行检测　
}

__ramfunc void correctSmallImage(uint8_t* smallimage, uint8_t* IMAGEMAP)
{
    smallimage[0]=0;
    for(int i = 0;i<60*94;i++)
        IMAGEMAP[i] = smallimage[map[i]];
}

__ramfunc void  ConvertImg(uint8_t image1[ MT9V034_H/2][ MT9V034_W/2], uint8_t image2[MT9V034_H/2][ MT9V034_W/2])//桶形失真
{
  int i=0,j=0;
  int x=0,y=0;
  int h = height/2;
  int w = wigth/2;
  float k1=-0.000023,k2=-0.000025;//-0.00000230,k2=-0.00000120;//发现图不对可修改这两个参数来调整
  for(i=-h;i<h;i++)
    for(j=-w;j<w;j++)
    {
      x=(int)(i*(1+k1*i*i+k2*j*j))+h;
      y=(int)(j*(1+k1*i*i+k2*j*j))+w;
      //*(*(image2+(i+60)*160)+(j+80))=*(*(image1+x*160)+y);
      image2[i+h][j+w]=image1[x][y];
    } 
}

__ramfunc float32_t F_abs(float32_t num)
{
	return num>=0? num:-num;
}
__ramfunc int16_t I_abs(int num)
{
    return num>=0? num:-(int)num;
}

__ramfunc int16_t I_pow(int16_t num)
{
    return num*num;
}

__ramfunc void divide_gray_ajust()
{  
  if(READ_LEFT)
  {  
    delay_ms(30);
    if(READ_LEFT)
        divide_gray+=1;
    
    if(divide_gray>254)
      divide_gray=254;
  }
  if(READ_RIGHT)
  {
    delay_ms(30);
    if(READ_RIGHT)
        divide_gray-=1;
    if(divide_gray<1)
     divide_gray=1;
  }  
  
  Display_Number(0,5,divide_gray,YELLOW,RED);
}

__ramfunc uint8_t node(uint8_t* in){
    int i,j;
    double uk1[10]={0,0,0,0,0,0,0,0,0,0},yk1[10]={0,0,0,0,0,0,0,0,0,0};
    double quan1[10][100]={0.002699,-0.004887,-0.005488,0.000795,0.001372,0.001727,0.000679,-0.003878,-0.004606,-0.002582,0.000000,-0.001125,-0.000761,-0.003475,-0.001738,-0.001909,-0.001101,0.004560,-0.001110,0.004369,0.000654,0.004191,-0.004891,-0.002257,-0.005295,-0.004519,-0.003646,0.002701,-0.005351,0.002034,0.002525,-0.003590,-0.005549,-0.004009,0.000809,-0.001162,-0.003053,-0.003428,0.000915,-0.004028,-0.001047,0.000933,-0.001676,-0.004700,-0.002887,-0.002887,0.000544,-0.006241,-0.000138,0.003188,-0.004658,0.000392,-0.006457,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002767,0.000815,-0.003374,-0.003495,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.005139,-0.001858,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.003073,0.001396,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,0.001341,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.002887,-0.005385,-0.060155,-0.042558,-0.014158,-0.018696,-0.006514,-0.019312,-0.070534,0.002021,0.015311,0.000000,-0.040161,-0.063020,-0.030943,0.103092,-0.092319,-0.011545,0.008761,0.017592,-0.064205,0.026135,0.035225,0.017378,0.041111,0.082724,0.167115,0.082223,0.076355,0.017808,0.099547,0.055196,0.043155,0.133110,-0.004487,-0.020860,-0.004273,0.001571,-0.068461,-0.010774,-0.033018,0.074585,0.066156,-0.012832,0.018707,0.004852,0.004852,0.003845,-0.002845,0.002523,0.015447,-0.124993,-0.003224,0.010043,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,-0.026922,-0.060250,0.003331,-0.001098,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,-0.063452,-0.004259,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,-0.019228,0.003418,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.000054,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.004852,0.055648,0.046347,0.002436,0.013442,-0.050207,-0.010034,0.000000,-0.088016,0.072755,0.083524,0.000000,0.002024,-0.193774,0.018451,0.033867,0.000001,0.082974,-0.014708,-0.030412,0.072402,0.054950,-0.000008,-0.080395,-0.081642,0.004152,0.080721,0.028996,0.021009,-0.060129,0.133235,0.052783,0.013600,0.026044,-0.056513,-0.018898,0.005533,-0.000547,0.025154,-0.076054,0.043467,0.013556,-0.017511,-0.027593,-0.007905,0.001862,0.001862,0.000000,-0.000811,-0.007292,0.025555,0.034888,-0.000995,-0.000885,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.003448,0.011619,-0.001703,-0.002725,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.016855,-0.002955,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.004002,-0.008666,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,-0.010230,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,0.001862,-0.000647,-0.046829,-0.006214,-0.014490,0.062294,0.032177,-0.021802,0.000895,0.033286,0.033391,0.000000,0.004393,0.081079,0.060727,0.100318,0.021900,0.005747,0.013230,0.033707,0.021012,-0.031478,0.014304,0.011704,0.033686,0.032217,0.017133,-0.000063,-0.035693,-0.045862,-0.085864,0.000720,0.040878,-0.104374,0.014441,0.012280,0.016810,0.014221,-0.019959,-0.026415,-0.092447,-0.055069,0.014853,0.022876,0.008636,-0.000329,-0.000329,0.001838,0.017620,-0.057100,0.053162,0.013654,0.019548,0.003233,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.063425,0.010042,0.010440,0.018188,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,0.017914,0.020268,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,0.021298,0.021206,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,0.024179,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.000329,-0.002030,0.000057,-0.004310,0.002458,0.000478,-0.005327,-0.003928,-0.004039,0.002241,0.001853,0.000000,0.002255,0.000952,-0.002940,-0.003736,-0.003240,-0.005544,-0.005883,-0.006286,0.002782,0.004362,-0.005782,0.000758,0.004452,-0.002150,0.002151,0.000637,-0.000033,-0.003150,-0.005150,0.001010,0.001469,-0.006702,-0.000556,-0.008477,-0.002120,-0.004532,0.000981,-0.005368,-0.001800,0.004218,-0.003594,-0.006700,-0.001757,-0.003376,-0.003376,0.000833,-0.002083,-0.004689,0.000777,-0.000925,-0.001548,0.000558,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.001254,-0.001267,-0.006753,-0.004517,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.002559,-0.001505,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.001917,-0.005573,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.001298,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,-0.003376,0.004921,-0.003801,0.002321,-0.001648,0.002565,0.001208,0.001626,0.004767,-0.000428,0.001941,0.000000,0.003507,-0.001614,-0.004443,-0.003767,0.003130,0.000814,-0.002440,-0.003218,0.001020,0.001160,-0.002063,0.001354,0.004734,0.001917,0.006011,0.004743,0.005283,0.003613,0.001399,0.004856,-0.000968,-0.003109,-0.001760,0.004661,0.000975,-0.002002,-0.001721,-0.001691,0.003972,0.005414,-0.003533,-0.002784,0.006147,0.001591,0.001591,0.001594,0.006155,0.002266,0.005307,0.001040,0.004051,0.001124,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,-0.001295,0.001338,0.002144,0.003092,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,-0.003159,-0.001093,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.002469,-0.000648,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.000173,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,0.001591,-0.003000,0.003603,-0.003880,0.001856,0.002574,0.003783,0.003306,0.001402,0.000933,0.002925,0.000000,-0.001134,-0.001559,0.001165,-0.002660,0.002819,-0.004466,-0.001513,-0.000954,0.001283,-0.002360,0.004833,-0.003878,0.001225,0.000643,0.005744,-0.001865,0.002283,-0.001576,-0.002453,-0.001388,-0.004156,-0.001537,0.000900,-0.002435,0.006371,0.006257,0.001854,0.005836,0.004506,-0.000567,-0.000839,0.002842,-0.001486,0.001639,0.001639,0.006692,0.004414,-0.000714,-0.003278,-0.001954,0.004800,0.000531,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,-0.002534,0.001540,0.003268,0.002294,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.004602,-0.002553,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.003308,-0.002101,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,-0.002597,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,0.001639,-0.003274,0.006220,0.005887,0.004787,-0.003185,0.002045,0.000991,0.005401,-0.002416,0.001137,0.000000,0.001492,0.001932,-0.003837,0.003293,0.001986,0.003879,-0.002475,0.003475,0.000228,0.002587,0.000705,-0.002655,-0.004645,0.001432,0.003448,-0.000928,0.005133,0.001780,0.001076,0.003861,-0.004069,0.004819,-0.002546,-0.002557,0.005065,0.000706,-0.000086,-0.000445,-0.001223,0.003819,0.005945,0.003706,0.002888,0.002117,0.002117,0.001429,0.002701,0.003519,0.001427,0.001223,-0.002215,0.006425,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,-0.002710,0.000235,0.006136,-0.002640,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,-0.000143,-0.000390,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,-0.000293,-0.001218,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,-0.002702,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.002117,0.063513,-0.310911,0.045430,-0.131216,0.056033,0.027402,-0.090513,0.148613,-0.041542,-0.054616,0.000000,0.057909,0.058881,0.054166,-0.003176,0.041731,0.023384,-0.067271,0.107490,0.232308,0.028938,0.053949,-0.054362,0.114361,-0.149083,-0.015047,-0.023825,0.137464,-0.008958,-0.022079,-0.201804,-0.058989,-0.057661,-0.138442,-0.019791,0.004027,-0.007841,0.100302,0.159707,0.057132,0.071894,-0.121791,-0.024528,-0.026026,0.003077,0.003077,-0.019259,-0.011663,0.039847,-0.007138,0.009629,-0.012014,-0.021820,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,-0.011070,0.007368,-0.015715,-0.009675,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.012304,0.012844,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.022297,0.003853,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.002655,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.003077,0.114678,-0.060081,-0.087170,0.010233,0.342331,0.178006,0.103538,-0.076992,0.044751,0.155164,0.000000,0.003887,0.161817,0.061852,0.289907,0.040314,-0.053392,0.103120,0.011449,-0.105341,-0.084495,0.043359,-0.169824,0.157189,0.015472,-0.023709,0.132563,0.017549,0.102070,-0.138021,-0.050052,-0.164694,-0.031555,0.247166,-0.002805,-0.020369,-0.021082,-0.006729,0.039746,-0.079308,0.326115,-0.094782,-0.006415,-0.014330,-0.015130,-0.015130,-0.015116,-0.018642,-0.054673,-0.039609,0.039867,-0.014289,-0.015855,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.057561,0.070856,-0.019867,-0.018344,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,0.068666,-0.019617,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,0.102699,-0.020839,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.013871,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130,-0.015130};
    double bk1[10]={-3.5564,0.2298,2.2580,-1.8726,-0.4166,-1.1712,0.7356,-0.7264,7.7650,1.3577};

    for(i=0;i<10;i++)
    {
        for(j=0;j<100;j++)
        {
            uk1[i]+=in[j]*quan1[i][j];
        }
        yk1[i]=1/(1+exp(-uk1[i]-bk1[i]));
    }

    double quan2[10]={-0.1052 , -14.3225 ,  27.6998  , 16.8277  , -0.0947 ,   4.3070 ,   4.2939 , 4.4994 ,  28.6647 ,  -4.8927};
    double bk2=4.8443;
    double sum;
    double out;
    for(i=0;i<10;i++)
    {
        sum+=quan2[i]*yk1[i];
    }
    return (uint8_t)sum;
}

const uint16_t map[60*94] = 

{1243 ,1244 ,1244 ,1245 ,1245 ,1246 ,1246 ,1247 ,1247 ,1248 ,1248 ,1249 ,1249 ,1250 ,1250 ,1251 ,1252 ,1252 ,1253 ,1253 ,1254 ,1254 ,1255 ,1255 ,1256 ,1256 ,1257 ,1257 ,1258 ,1258 ,1259 ,1259 ,1260 ,1261 ,1261 ,1262 ,1262 ,1263 ,1263 ,1264 ,1264 ,1265 ,1265 ,1266 ,1266 ,1267 ,1267 ,1268 ,1269 ,1269 ,1270 ,1270 ,1271 ,1271 ,1272 ,1272 ,1273 ,1273 ,1274 ,1274 ,1275 ,1275 ,1276 ,1277 ,1277 ,1278 ,1278 ,1279 ,1279 ,1280 ,1280 ,1281 ,1281 ,1282 ,1282 ,1283 ,1283 ,1284 ,1284 ,1285 ,1286 ,1286 ,1287 ,1287 ,1288 ,1288 ,1289 ,1289 ,1290 ,1290 ,1291 ,1291 ,1292 ,1292 ,
1243 ,1243 ,1244 ,1244 ,1245 ,1245 ,1246 ,1247 ,1247 ,1248 ,1248 ,1249 ,1249 ,1250 ,1250 ,1251 ,1251 ,1252 ,1252 ,1253 ,1254 ,1254 ,1255 ,1255 ,1256 ,1256 ,1257 ,1257 ,1258 ,1258 ,1259 ,1259 ,1260 ,1261 ,1261 ,1262 ,1262 ,1263 ,1263 ,1264 ,1264 ,1265 ,1265 ,1266 ,1266 ,1267 ,1267 ,1268 ,1269 ,1269 ,1270 ,1270 ,1271 ,1271 ,1272 ,1272 ,1273 ,1273 ,1274 ,1274 ,1275 ,1276 ,1276 ,1277 ,1277 ,1278 ,1278 ,1279 ,1279 ,1280 ,1280 ,1281 ,1281 ,1282 ,1282 ,1283 ,1284 ,1284 ,1285 ,1285 ,1286 ,1286 ,1287 ,1287 ,1288 ,1288 ,1289 ,1289 ,1290 ,1291 ,1291 ,1292 ,1292 ,1293 ,
1337 ,1337 ,1338 ,1338 ,1339 ,1339 ,1340 ,1340 ,1341 ,1341 ,1342 ,1343 ,1343 ,1344 ,1344 ,1345 ,1345 ,1346 ,1346 ,1347 ,1347 ,1348 ,1349 ,1349 ,1350 ,1350 ,1351 ,1351 ,1352 ,1352 ,1353 ,1353 ,1354 ,1354 ,1355 ,1356 ,1356 ,1357 ,1357 ,1358 ,1358 ,1359 ,1359 ,1360 ,1360 ,1361 ,1361 ,1362 ,1363 ,1363 ,1364 ,1364 ,1365 ,1365 ,1366 ,1366 ,1367 ,1367 ,1368 ,1369 ,1369 ,1370 ,1370 ,1371 ,1371 ,1372 ,1372 ,1373 ,1373 ,1374 ,1374 ,1375 ,1376 ,1376 ,1377 ,1377 ,1378 ,1378 ,1379 ,1379 ,1380 ,1380 ,1381 ,1381 ,1382 ,1383 ,1383 ,1384 ,1384 ,1385 ,1385 ,1386 ,1386 ,1387 ,
1336 ,1337 ,1338 ,1338 ,1339 ,1339 ,1340 ,1340 ,1341 ,1341 ,1342 ,1342 ,1343 ,1344 ,1344 ,1345 ,1345 ,1346 ,1346 ,1347 ,1347 ,1348 ,1348 ,1349 ,1350 ,1350 ,1351 ,1351 ,1352 ,1352 ,1353 ,1353 ,1354 ,1354 ,1355 ,1355 ,1356 ,1357 ,1357 ,1358 ,1358 ,1359 ,1359 ,1360 ,1360 ,1361 ,1361 ,1362 ,1363 ,1363 ,1364 ,1364 ,1365 ,1365 ,1366 ,1366 ,1367 ,1367 ,1368 ,1369 ,1369 ,1370 ,1370 ,1371 ,1371 ,1372 ,1372 ,1373 ,1373 ,1374 ,1375 ,1375 ,1376 ,1376 ,1377 ,1377 ,1378 ,1378 ,1379 ,1379 ,1380 ,1381 ,1381 ,1382 ,1382 ,1383 ,1383 ,1384 ,1384 ,1385 ,1385 ,1386 ,1387 ,1387 ,
1430 ,1431 ,1431 ,1432 ,1432 ,1433 ,1434 ,1434 ,1435 ,1435 ,1436 ,1436 ,1437 ,1437 ,1438 ,1438 ,1439 ,1440 ,1440 ,1441 ,1441 ,1442 ,1442 ,1443 ,1443 ,1444 ,1445 ,1445 ,1446 ,1446 ,1447 ,1447 ,1448 ,1448 ,1449 ,1449 ,1450 ,1451 ,1451 ,1452 ,1452 ,1453 ,1453 ,1454 ,1454 ,1455 ,1455 ,1456 ,1457 ,1457 ,1458 ,1458 ,1459 ,1459 ,1460 ,1460 ,1461 ,1462 ,1462 ,1463 ,1463 ,1464 ,1464 ,1465 ,1465 ,1466 ,1466 ,1467 ,1468 ,1468 ,1469 ,1469 ,1470 ,1470 ,1471 ,1471 ,1472 ,1473 ,1473 ,1474 ,1474 ,1475 ,1475 ,1476 ,1476 ,1477 ,1477 ,1478 ,1479 ,1479 ,1480 ,1480 ,1481 ,1481 ,
1430 ,1431 ,1431 ,1432 ,1432 ,1433 ,1433 ,1434 ,1434 ,1435 ,1436 ,1436 ,1437 ,1437 ,1438 ,1438 ,1439 ,1439 ,1440 ,1441 ,1441 ,1442 ,1442 ,1443 ,1443 ,1444 ,1444 ,1445 ,1446 ,1446 ,1447 ,1447 ,1448 ,1448 ,1449 ,1449 ,1450 ,1451 ,1451 ,1452 ,1452 ,1453 ,1453 ,1454 ,1454 ,1455 ,1455 ,1456 ,1457 ,1457 ,1458 ,1458 ,1459 ,1459 ,1460 ,1460 ,1461 ,1462 ,1462 ,1463 ,1463 ,1464 ,1464 ,1465 ,1465 ,1466 ,1467 ,1467 ,1468 ,1468 ,1469 ,1469 ,1470 ,1470 ,1471 ,1472 ,1472 ,1473 ,1473 ,1474 ,1474 ,1475 ,1475 ,1476 ,1477 ,1477 ,1478 ,1478 ,1479 ,1479 ,1480 ,1480 ,1481 ,1482 ,
1524 ,1524 ,1525 ,1526 ,1526 ,1527 ,1527 ,1528 ,1528 ,1529 ,1529 ,1530 ,1531 ,1531 ,1532 ,1532 ,1533 ,1533 ,1534 ,1534 ,1535 ,1536 ,1536 ,1537 ,1537 ,1538 ,1538 ,1539 ,1539 ,1540 ,1541 ,1541 ,1542 ,1542 ,1543 ,1543 ,1544 ,1544 ,1545 ,1546 ,1546 ,1547 ,1547 ,1548 ,1548 ,1549 ,1549 ,1550 ,1551 ,1551 ,1552 ,1552 ,1553 ,1553 ,1554 ,1555 ,1555 ,1556 ,1556 ,1557 ,1557 ,1558 ,1558 ,1559 ,1560 ,1560 ,1561 ,1561 ,1562 ,1562 ,1563 ,1563 ,1564 ,1565 ,1565 ,1566 ,1566 ,1567 ,1567 ,1568 ,1568 ,1569 ,1570 ,1570 ,1571 ,1571 ,1572 ,1572 ,1573 ,1573 ,1574 ,1575 ,1575 ,1576 ,
1524 ,1524 ,1525 ,1525 ,1526 ,1526 ,1527 ,1528 ,1528 ,1529 ,1529 ,1530 ,1530 ,1531 ,1531 ,1532 ,1533 ,1533 ,1534 ,1534 ,1535 ,1535 ,1536 ,1537 ,1537 ,1538 ,1538 ,1539 ,1539 ,1540 ,1541 ,1541 ,1542 ,1542 ,1543 ,1543 ,1544 ,1544 ,1545 ,1546 ,1546 ,1547 ,1547 ,1548 ,1548 ,1549 ,1550 ,1550 ,1551 ,1551 ,1552 ,1552 ,1553 ,1553 ,1554 ,1555 ,1555 ,1556 ,1556 ,1557 ,1557 ,1558 ,1559 ,1559 ,1560 ,1560 ,1561 ,1561 ,1562 ,1562 ,1563 ,1564 ,1564 ,1565 ,1565 ,1566 ,1566 ,1567 ,1568 ,1568 ,1569 ,1569 ,1570 ,1570 ,1571 ,1571 ,1572 ,1573 ,1573 ,1574 ,1574 ,1575 ,1575 ,1576 ,
1617 ,1618 ,1619 ,1619 ,1620 ,1620 ,1621 ,1621 ,1622 ,1623 ,1623 ,1624 ,1624 ,1625 ,1625 ,1626 ,1626 ,1627 ,1628 ,1628 ,1629 ,1629 ,1630 ,1630 ,1631 ,1632 ,1632 ,1633 ,1633 ,1634 ,1634 ,1635 ,1636 ,1636 ,1637 ,1637 ,1638 ,1638 ,1639 ,1640 ,1640 ,1641 ,1641 ,1642 ,1642 ,1643 ,1644 ,1644 ,1645 ,1645 ,1646 ,1646 ,1647 ,1647 ,1648 ,1649 ,1649 ,1650 ,1650 ,1651 ,1651 ,1652 ,1653 ,1653 ,1654 ,1654 ,1655 ,1655 ,1656 ,1657 ,1657 ,1658 ,1658 ,1659 ,1659 ,1660 ,1661 ,1661 ,1662 ,1662 ,1663 ,1663 ,1664 ,1664 ,1665 ,1666 ,1666 ,1667 ,1667 ,1668 ,1668 ,1669 ,1670 ,1670 ,
1617 ,1618 ,1618 ,1619 ,1619 ,1620 ,1621 ,1621 ,1622 ,1622 ,1623 ,1623 ,1624 ,1625 ,1625 ,1626 ,1626 ,1627 ,1627 ,1628 ,1629 ,1629 ,1630 ,1630 ,1631 ,1632 ,1632 ,1633 ,1633 ,1634 ,1634 ,1635 ,1636 ,1636 ,1637 ,1637 ,1638 ,1638 ,1639 ,1640 ,1640 ,1641 ,1641 ,1642 ,1642 ,1643 ,1644 ,1644 ,1645 ,1645 ,1646 ,1646 ,1647 ,1648 ,1648 ,1649 ,1649 ,1650 ,1650 ,1651 ,1652 ,1652 ,1653 ,1653 ,1654 ,1654 ,1655 ,1656 ,1656 ,1657 ,1657 ,1658 ,1658 ,1659 ,1660 ,1660 ,1661 ,1661 ,1662 ,1662 ,1663 ,1664 ,1664 ,1665 ,1665 ,1666 ,1666 ,1667 ,1668 ,1668 ,1669 ,1669 ,1670 ,1670 ,
1711 ,1712 ,1712 ,1713 ,1713 ,1714 ,1714 ,1715 ,1716 ,1716 ,1717 ,1717 ,1718 ,1718 ,1719 ,1720 ,1720 ,1721 ,1721 ,1722 ,1723 ,1723 ,1724 ,1724 ,1725 ,1725 ,1726 ,1727 ,1727 ,1728 ,1728 ,1729 ,1729 ,1730 ,1731 ,1731 ,1732 ,1732 ,1733 ,1733 ,1734 ,1735 ,1735 ,1736 ,1736 ,1737 ,1738 ,1738 ,1739 ,1739 ,1740 ,1740 ,1741 ,1742 ,1742 ,1743 ,1743 ,1744 ,1744 ,1745 ,1746 ,1746 ,1747 ,1747 ,1748 ,1748 ,1749 ,1750 ,1750 ,1751 ,1751 ,1752 ,1753 ,1753 ,1754 ,1754 ,1755 ,1755 ,1756 ,1757 ,1757 ,1758 ,1758 ,1759 ,1759 ,1760 ,1761 ,1761 ,1762 ,1762 ,1763 ,1763 ,1764 ,1765 ,
1711 ,1711 ,1712 ,1713 ,1713 ,1714 ,1714 ,1715 ,1715 ,1716 ,1717 ,1717 ,1718 ,1718 ,1719 ,1719 ,1720 ,1721 ,1721 ,1722 ,1722 ,1723 ,1724 ,1724 ,1725 ,1725 ,1726 ,1726 ,1727 ,1728 ,1728 ,1729 ,1729 ,1730 ,1731 ,1731 ,1732 ,1732 ,1733 ,1733 ,1734 ,1735 ,1735 ,1736 ,1736 ,1737 ,1738 ,1738 ,1739 ,1739 ,1740 ,1740 ,1741 ,1742 ,1742 ,1743 ,1743 ,1744 ,1745 ,1745 ,1746 ,1746 ,1747 ,1747 ,1748 ,1749 ,1749 ,1750 ,1750 ,1751 ,1751 ,1752 ,1753 ,1753 ,1754 ,1754 ,1755 ,1756 ,1756 ,1757 ,1757 ,1758 ,1758 ,1759 ,1760 ,1760 ,1761 ,1761 ,1762 ,1763 ,1763 ,1764 ,1764 ,1765 ,
1805 ,1805 ,1806 ,1806 ,1807 ,1807 ,1808 ,1809 ,1809 ,1810 ,1810 ,1811 ,1812 ,1812 ,1813 ,1813 ,1814 ,1815 ,1815 ,1816 ,1816 ,1817 ,1817 ,1818 ,1819 ,1819 ,1820 ,1820 ,1821 ,1822 ,1822 ,1823 ,1823 ,1824 ,1824 ,1825 ,1826 ,1826 ,1827 ,1827 ,1828 ,1829 ,1829 ,1830 ,1830 ,1831 ,1832 ,1832 ,1833 ,1833 ,1834 ,1834 ,1835 ,1836 ,1836 ,1837 ,1837 ,1838 ,1839 ,1839 ,1840 ,1840 ,1841 ,1842 ,1842 ,1843 ,1843 ,1844 ,1844 ,1845 ,1846 ,1846 ,1847 ,1847 ,1848 ,1849 ,1849 ,1850 ,1850 ,1851 ,1851 ,1852 ,1853 ,1853 ,1854 ,1854 ,1855 ,1856 ,1856 ,1857 ,1857 ,1858 ,1859 ,1859 ,
1804 ,1805 ,1805 ,1806 ,1807 ,1807 ,1808 ,1808 ,1809 ,1810 ,1810 ,1811 ,1811 ,1812 ,1813 ,1813 ,1814 ,1814 ,1815 ,1816 ,1816 ,1817 ,1817 ,1818 ,1819 ,1819 ,1820 ,1820 ,1821 ,1821 ,1822 ,1823 ,1823 ,1824 ,1824 ,1825 ,1826 ,1826 ,1827 ,1827 ,1828 ,1829 ,1829 ,1830 ,1830 ,1831 ,1832 ,1832 ,1833 ,1833 ,1834 ,1834 ,1835 ,1836 ,1836 ,1837 ,1837 ,1838 ,1839 ,1839 ,1840 ,1840 ,1841 ,1842 ,1842 ,1843 ,1843 ,1844 ,1845 ,1845 ,1846 ,1846 ,1847 ,1848 ,1848 ,1849 ,1849 ,1850 ,1850 ,1851 ,1852 ,1852 ,1853 ,1853 ,1854 ,1855 ,1855 ,1856 ,1856 ,1857 ,1858 ,1858 ,1859 ,1859 ,
1898 ,1899 ,1899 ,1900 ,1900 ,1901 ,1902 ,1902 ,1903 ,1903 ,1904 ,1905 ,1905 ,1906 ,1906 ,1907 ,1908 ,1908 ,1909 ,1909 ,1910 ,1911 ,1911 ,1912 ,1912 ,1913 ,1914 ,1914 ,1915 ,1915 ,1916 ,1917 ,1917 ,1918 ,1918 ,1919 ,1920 ,1920 ,1921 ,1921 ,1922 ,1923 ,1923 ,1924 ,1924 ,1925 ,1926 ,1926 ,1927 ,1927 ,1928 ,1929 ,1929 ,1930 ,1930 ,1931 ,1932 ,1932 ,1933 ,1933 ,1934 ,1934 ,1935 ,1936 ,1936 ,1937 ,1937 ,1938 ,1939 ,1939 ,1940 ,1940 ,1941 ,1942 ,1942 ,1943 ,1943 ,1944 ,1945 ,1945 ,1946 ,1946 ,1947 ,1948 ,1948 ,1949 ,1949 ,1950 ,1951 ,1951 ,1952 ,1952 ,1953 ,1954 ,
1898 ,1898 ,1899 ,1900 ,1900 ,1901 ,1901 ,1902 ,1903 ,1903 ,1904 ,1904 ,1905 ,1906 ,1906 ,1907 ,1907 ,1908 ,1909 ,1909 ,1910 ,1910 ,1911 ,1912 ,1912 ,1913 ,1914 ,1914 ,1915 ,1915 ,1916 ,1917 ,1917 ,1918 ,1918 ,1919 ,1920 ,1920 ,1921 ,1921 ,1922 ,1923 ,1923 ,1924 ,1924 ,1925 ,1926 ,1926 ,1927 ,1927 ,1928 ,1929 ,1929 ,1930 ,1930 ,1931 ,1932 ,1932 ,1933 ,1933 ,1934 ,1935 ,1935 ,1936 ,1936 ,1937 ,1938 ,1938 ,1939 ,1939 ,1940 ,1941 ,1941 ,1942 ,1942 ,1943 ,1944 ,1944 ,1945 ,1945 ,1946 ,1947 ,1947 ,1948 ,1948 ,1949 ,1950 ,1950 ,1951 ,1951 ,1952 ,1953 ,1953 ,1954 ,
1992 ,1992 ,1993 ,1993 ,1994 ,1995 ,1995 ,1996 ,1996 ,1997 ,1998 ,1998 ,1999 ,1999 ,2000 ,2001 ,2001 ,2002 ,2003 ,2003 ,2004 ,2004 ,2005 ,2006 ,2006 ,2007 ,2007 ,2008 ,2009 ,2009 ,2010 ,2010 ,2011 ,2012 ,2012 ,2013 ,2013 ,2014 ,2015 ,2015 ,2016 ,2017 ,2017 ,2018 ,2018 ,2019 ,2020 ,2020 ,2021 ,2021 ,2022 ,2023 ,2023 ,2024 ,2024 ,2025 ,2026 ,2026 ,2027 ,2027 ,2028 ,2029 ,2029 ,2030 ,2030 ,2031 ,2032 ,2032 ,2033 ,2034 ,2034 ,2035 ,2035 ,2036 ,2037 ,2037 ,2038 ,2038 ,2039 ,2040 ,2040 ,2041 ,2041 ,2042 ,2043 ,2043 ,2044 ,2044 ,2045 ,2046 ,2046 ,2047 ,2048 ,2048 ,
1991 ,1992 ,1993 ,1993 ,1994 ,1994 ,1995 ,1996 ,1996 ,1997 ,1997 ,1998 ,1999 ,1999 ,2000 ,2001 ,2001 ,2002 ,2002 ,2003 ,2004 ,2004 ,2005 ,2005 ,2006 ,2007 ,2007 ,2008 ,2009 ,2009 ,2010 ,2010 ,2011 ,2012 ,2012 ,2013 ,2013 ,2014 ,2015 ,2015 ,2016 ,2016 ,2017 ,2018 ,2018 ,2019 ,2020 ,2020 ,2021 ,2021 ,2022 ,2023 ,2023 ,2024 ,2024 ,2025 ,2026 ,2026 ,2027 ,2028 ,2028 ,2029 ,2029 ,2030 ,2031 ,2031 ,2032 ,2032 ,2033 ,2034 ,2034 ,2035 ,2036 ,2036 ,2037 ,2037 ,2038 ,2039 ,2039 ,2040 ,2040 ,2041 ,2042 ,2042 ,2043 ,2043 ,2044 ,2045 ,2045 ,2046 ,2047 ,2047 ,2048 ,2048 ,
2085 ,2086 ,2086 ,2087 ,2088 ,2088 ,2089 ,2089 ,2090 ,2091 ,2091 ,2092 ,2093 ,2093 ,2094 ,2094 ,2095 ,2096 ,2096 ,2097 ,2097 ,2098 ,2099 ,2099 ,2100 ,2101 ,2101 ,2102 ,2102 ,2103 ,2104 ,2104 ,2105 ,2106 ,2106 ,2107 ,2107 ,2108 ,2109 ,2109 ,2110 ,2110 ,2111 ,2112 ,2112 ,2113 ,2114 ,2114 ,2115 ,2115 ,2116 ,2117 ,2117 ,2118 ,2119 ,2119 ,2120 ,2120 ,2121 ,2122 ,2122 ,2123 ,2123 ,2124 ,2125 ,2125 ,2126 ,2127 ,2127 ,2128 ,2128 ,2129 ,2130 ,2130 ,2131 ,2132 ,2132 ,2133 ,2133 ,2134 ,2135 ,2135 ,2136 ,2136 ,2137 ,2138 ,2138 ,2139 ,2140 ,2140 ,2141 ,2141 ,2142 ,2143 ,
2085 ,2085 ,2086 ,2087 ,2087 ,2088 ,2089 ,2089 ,2090 ,2090 ,2091 ,2092 ,2092 ,2093 ,2094 ,2094 ,2095 ,2095 ,2096 ,2097 ,2097 ,2098 ,2099 ,2099 ,2100 ,2100 ,2101 ,2102 ,2102 ,2103 ,2104 ,2104 ,2105 ,2105 ,2106 ,2107 ,2107 ,2108 ,2109 ,2109 ,2110 ,2110 ,2111 ,2112 ,2112 ,2113 ,2114 ,2114 ,2115 ,2115 ,2116 ,2117 ,2117 ,2118 ,2119 ,2119 ,2120 ,2120 ,2121 ,2122 ,2122 ,2123 ,2124 ,2124 ,2125 ,2125 ,2126 ,2127 ,2127 ,2128 ,2129 ,2129 ,2130 ,2130 ,2131 ,2132 ,2132 ,2133 ,2134 ,2134 ,2135 ,2135 ,2136 ,2137 ,2137 ,2138 ,2139 ,2139 ,2140 ,2140 ,2141 ,2142 ,2142 ,2143 ,
2179 ,2179 ,2180 ,2180 ,2181 ,2182 ,2182 ,2183 ,2184 ,2184 ,2185 ,2186 ,2186 ,2187 ,2187 ,2188 ,2189 ,2189 ,2190 ,2191 ,2191 ,2192 ,2192 ,2193 ,2194 ,2194 ,2195 ,2196 ,2196 ,2197 ,2197 ,2198 ,2199 ,2199 ,2200 ,2201 ,2201 ,2202 ,2203 ,2203 ,2204 ,2204 ,2205 ,2206 ,2206 ,2207 ,2208 ,2208 ,2209 ,2209 ,2210 ,2211 ,2211 ,2212 ,2213 ,2213 ,2214 ,2215 ,2215 ,2216 ,2216 ,2217 ,2218 ,2218 ,2219 ,2220 ,2220 ,2221 ,2221 ,2222 ,2223 ,2223 ,2224 ,2225 ,2225 ,2226 ,2226 ,2227 ,2228 ,2228 ,2229 ,2230 ,2230 ,2231 ,2232 ,2232 ,2233 ,2233 ,2234 ,2235 ,2235 ,2236 ,2237 ,2237 ,
2178 ,2179 ,2180 ,2180 ,2181 ,2182 ,2182 ,2183 ,2183 ,2184 ,2185 ,2185 ,2186 ,2187 ,2187 ,2188 ,2189 ,2189 ,2190 ,2190 ,2191 ,2192 ,2192 ,2193 ,2194 ,2194 ,2195 ,2196 ,2196 ,2197 ,2197 ,2198 ,2199 ,2199 ,2200 ,2201 ,2201 ,2202 ,2202 ,2203 ,2204 ,2204 ,2205 ,2206 ,2206 ,2207 ,2208 ,2208 ,2209 ,2209 ,2210 ,2211 ,2211 ,2212 ,2213 ,2213 ,2214 ,2215 ,2215 ,2216 ,2216 ,2217 ,2218 ,2218 ,2219 ,2220 ,2220 ,2221 ,2222 ,2222 ,2223 ,2223 ,2224 ,2225 ,2225 ,2226 ,2227 ,2227 ,2228 ,2229 ,2229 ,2230 ,2230 ,2231 ,2232 ,2232 ,2233 ,2234 ,2234 ,2235 ,2236 ,2236 ,2237 ,2237 ,
2272 ,2273 ,2273 ,2274 ,2275 ,2275 ,2276 ,2277 ,2277 ,2278 ,2278 ,2279 ,2280 ,2280 ,2281 ,2282 ,2282 ,2283 ,2284 ,2284 ,2285 ,2286 ,2286 ,2287 ,2287 ,2288 ,2289 ,2289 ,2290 ,2291 ,2291 ,2292 ,2293 ,2293 ,2294 ,2295 ,2295 ,2296 ,2296 ,2297 ,2298 ,2298 ,2299 ,2300 ,2300 ,2301 ,2302 ,2302 ,2303 ,2304 ,2304 ,2305 ,2305 ,2306 ,2307 ,2307 ,2308 ,2309 ,2309 ,2310 ,2311 ,2311 ,2312 ,2313 ,2313 ,2314 ,2314 ,2315 ,2316 ,2316 ,2317 ,2318 ,2318 ,2319 ,2320 ,2320 ,2321 ,2321 ,2322 ,2323 ,2323 ,2324 ,2325 ,2325 ,2326 ,2327 ,2327 ,2328 ,2329 ,2329 ,2330 ,2330 ,2331 ,2332 ,
2366 ,2366 ,2367 ,2368 ,2368 ,2369 ,2370 ,2370 ,2371 ,2372 ,2372 ,2373 ,2374 ,2374 ,2375 ,2376 ,2376 ,2377 ,2377 ,2378 ,2379 ,2379 ,2380 ,2381 ,2381 ,2382 ,2383 ,2383 ,2384 ,2385 ,2385 ,2386 ,2387 ,2387 ,2388 ,2388 ,2389 ,2390 ,2390 ,2391 ,2392 ,2392 ,2393 ,2394 ,2394 ,2395 ,2396 ,2396 ,2397 ,2398 ,2398 ,2399 ,2399 ,2400 ,2401 ,2401 ,2402 ,2403 ,2403 ,2404 ,2405 ,2405 ,2406 ,2407 ,2407 ,2408 ,2409 ,2409 ,2410 ,2411 ,2411 ,2412 ,2412 ,2413 ,2414 ,2414 ,2415 ,2416 ,2416 ,2417 ,2418 ,2418 ,2419 ,2420 ,2420 ,2421 ,2422 ,2422 ,2423 ,2423 ,2424 ,2425 ,2425 ,2426 ,
2366 ,2366 ,2367 ,2367 ,2368 ,2369 ,2369 ,2370 ,2371 ,2371 ,2372 ,2373 ,2373 ,2374 ,2375 ,2375 ,2376 ,2377 ,2377 ,2378 ,2379 ,2379 ,2380 ,2381 ,2381 ,2382 ,2383 ,2383 ,2384 ,2384 ,2385 ,2386 ,2386 ,2387 ,2388 ,2388 ,2389 ,2390 ,2390 ,2391 ,2392 ,2392 ,2393 ,2394 ,2394 ,2395 ,2396 ,2396 ,2397 ,2398 ,2398 ,2399 ,2400 ,2400 ,2401 ,2401 ,2402 ,2403 ,2403 ,2404 ,2405 ,2405 ,2406 ,2407 ,2407 ,2408 ,2409 ,2409 ,2410 ,2411 ,2411 ,2412 ,2413 ,2413 ,2414 ,2415 ,2415 ,2416 ,2417 ,2417 ,2418 ,2419 ,2419 ,2420 ,2420 ,2421 ,2422 ,2422 ,2423 ,2424 ,2424 ,2425 ,2426 ,2426 ,
2459 ,2460 ,2461 ,2461 ,2462 ,2463 ,2463 ,2464 ,2465 ,2465 ,2466 ,2466 ,2467 ,2468 ,2468 ,2469 ,2470 ,2470 ,2471 ,2472 ,2472 ,2473 ,2474 ,2474 ,2475 ,2476 ,2476 ,2477 ,2478 ,2478 ,2479 ,2480 ,2480 ,2481 ,2482 ,2482 ,2483 ,2484 ,2484 ,2485 ,2486 ,2486 ,2487 ,2488 ,2488 ,2489 ,2490 ,2490 ,2491 ,2492 ,2492 ,2493 ,2494 ,2494 ,2495 ,2496 ,2496 ,2497 ,2498 ,2498 ,2499 ,2500 ,2500 ,2501 ,2502 ,2502 ,2503 ,2503 ,2504 ,2505 ,2505 ,2506 ,2507 ,2507 ,2508 ,2509 ,2509 ,2510 ,2511 ,2511 ,2512 ,2513 ,2513 ,2514 ,2515 ,2515 ,2516 ,2517 ,2517 ,2518 ,2519 ,2519 ,2520 ,2521 ,
2553 ,2554 ,2554 ,2555 ,2556 ,2556 ,2557 ,2558 ,2558 ,2559 ,2560 ,2560 ,2561 ,2562 ,2562 ,2563 ,2564 ,2564 ,2565 ,2566 ,2566 ,2567 ,2568 ,2568 ,2569 ,2570 ,2570 ,2571 ,2572 ,2572 ,2573 ,2574 ,2574 ,2575 ,2576 ,2576 ,2577 ,2578 ,2578 ,2579 ,2580 ,2580 ,2581 ,2582 ,2582 ,2583 ,2584 ,2584 ,2585 ,2586 ,2586 ,2587 ,2588 ,2588 ,2589 ,2590 ,2590 ,2591 ,2592 ,2592 ,2593 ,2594 ,2594 ,2595 ,2596 ,2596 ,2597 ,2598 ,2598 ,2599 ,2600 ,2600 ,2601 ,2602 ,2602 ,2603 ,2604 ,2604 ,2605 ,2606 ,2606 ,2607 ,2608 ,2608 ,2609 ,2610 ,2610 ,2611 ,2612 ,2612 ,2613 ,2614 ,2614 ,2615 ,
2553 ,2553 ,2554 ,2555 ,2555 ,2556 ,2557 ,2557 ,2558 ,2559 ,2559 ,2560 ,2561 ,2561 ,2562 ,2563 ,2563 ,2564 ,2565 ,2565 ,2566 ,2567 ,2567 ,2568 ,2569 ,2569 ,2570 ,2571 ,2572 ,2572 ,2573 ,2574 ,2574 ,2575 ,2576 ,2576 ,2577 ,2578 ,2578 ,2579 ,2580 ,2580 ,2581 ,2582 ,2582 ,2583 ,2584 ,2584 ,2585 ,2586 ,2586 ,2587 ,2588 ,2588 ,2589 ,2590 ,2590 ,2591 ,2592 ,2592 ,2593 ,2594 ,2594 ,2595 ,2596 ,2596 ,2597 ,2598 ,2598 ,2599 ,2600 ,2600 ,2601 ,2602 ,2602 ,2603 ,2604 ,2605 ,2605 ,2606 ,2607 ,2607 ,2608 ,2609 ,2609 ,2610 ,2611 ,2611 ,2612 ,2613 ,2613 ,2614 ,2615 ,2615 ,
2646 ,2647 ,2648 ,2648 ,2649 ,2650 ,2650 ,2651 ,2652 ,2652 ,2653 ,2654 ,2654 ,2655 ,2656 ,2657 ,2657 ,2658 ,2659 ,2659 ,2660 ,2661 ,2661 ,2662 ,2663 ,2663 ,2664 ,2665 ,2665 ,2666 ,2667 ,2667 ,2668 ,2669 ,2669 ,2670 ,2671 ,2672 ,2672 ,2673 ,2674 ,2674 ,2675 ,2676 ,2676 ,2677 ,2678 ,2678 ,2679 ,2680 ,2680 ,2681 ,2682 ,2682 ,2683 ,2684 ,2684 ,2685 ,2686 ,2686 ,2687 ,2688 ,2689 ,2689 ,2690 ,2691 ,2691 ,2692 ,2693 ,2693 ,2694 ,2695 ,2695 ,2696 ,2697 ,2697 ,2698 ,2699 ,2699 ,2700 ,2701 ,2701 ,2702 ,2703 ,2703 ,2704 ,2705 ,2706 ,2706 ,2707 ,2708 ,2708 ,2709 ,2710 ,
2740 ,2741 ,2741 ,2742 ,2743 ,2743 ,2744 ,2745 ,2746 ,2746 ,2747 ,2748 ,2748 ,2749 ,2750 ,2750 ,2751 ,2752 ,2752 ,2753 ,2754 ,2754 ,2755 ,2756 ,2757 ,2757 ,2758 ,2759 ,2759 ,2760 ,2761 ,2761 ,2762 ,2763 ,2763 ,2764 ,2765 ,2765 ,2766 ,2767 ,2768 ,2768 ,2769 ,2770 ,2770 ,2771 ,2772 ,2772 ,2773 ,2774 ,2774 ,2775 ,2776 ,2776 ,2777 ,2778 ,2779 ,2779 ,2780 ,2781 ,2781 ,2782 ,2783 ,2783 ,2784 ,2785 ,2785 ,2786 ,2787 ,2787 ,2788 ,2789 ,2790 ,2790 ,2791 ,2792 ,2792 ,2793 ,2794 ,2794 ,2795 ,2796 ,2796 ,2797 ,2798 ,2798 ,2799 ,2800 ,2801 ,2801 ,2802 ,2803 ,2803 ,2804 ,
2740 ,2740 ,2741 ,2742 ,2742 ,2743 ,2744 ,2745 ,2745 ,2746 ,2747 ,2747 ,2748 ,2749 ,2749 ,2750 ,2751 ,2752 ,2752 ,2753 ,2754 ,2754 ,2755 ,2756 ,2756 ,2757 ,2758 ,2758 ,2759 ,2760 ,2761 ,2761 ,2762 ,2763 ,2763 ,2764 ,2765 ,2765 ,2766 ,2767 ,2767 ,2768 ,2769 ,2770 ,2770 ,2771 ,2772 ,2772 ,2773 ,2774 ,2774 ,2775 ,2776 ,2777 ,2777 ,2778 ,2779 ,2779 ,2780 ,2781 ,2781 ,2782 ,2783 ,2783 ,2784 ,2785 ,2786 ,2786 ,2787 ,2788 ,2788 ,2789 ,2790 ,2790 ,2791 ,2792 ,2792 ,2793 ,2794 ,2795 ,2795 ,2796 ,2797 ,2797 ,2798 ,2799 ,2799 ,2800 ,2801 ,2802 ,2802 ,2803 ,2804 ,2804 ,
2833 ,2834 ,2835 ,2835 ,2836 ,2837 ,2838 ,2838 ,2839 ,2840 ,2840 ,2841 ,2842 ,2843 ,2843 ,2844 ,2845 ,2845 ,2846 ,2847 ,2847 ,2848 ,2849 ,2850 ,2850 ,2851 ,2852 ,2852 ,2853 ,2854 ,2854 ,2855 ,2856 ,2857 ,2857 ,2858 ,2859 ,2859 ,2860 ,2861 ,2861 ,2862 ,2863 ,2864 ,2864 ,2865 ,2866 ,2866 ,2867 ,2868 ,2868 ,2869 ,2870 ,2871 ,2871 ,2872 ,2873 ,2873 ,2874 ,2875 ,2875 ,2876 ,2877 ,2878 ,2878 ,2879 ,2880 ,2880 ,2881 ,2882 ,2882 ,2883 ,2884 ,2885 ,2885 ,2886 ,2887 ,2887 ,2888 ,2889 ,2890 ,2890 ,2891 ,2892 ,2892 ,2893 ,2894 ,2894 ,2895 ,2896 ,2897 ,2897 ,2898 ,2899 ,
2927 ,2928 ,2928 ,2929 ,2930 ,2931 ,2931 ,2932 ,2933 ,2933 ,2934 ,2935 ,2936 ,2936 ,2937 ,2938 ,2938 ,2939 ,2940 ,2941 ,2941 ,2942 ,2943 ,2943 ,2944 ,2945 ,2945 ,2946 ,2947 ,2948 ,2948 ,2949 ,2950 ,2950 ,2951 ,2952 ,2953 ,2953 ,2954 ,2955 ,2955 ,2956 ,2957 ,2958 ,2958 ,2959 ,2960 ,2960 ,2961 ,2962 ,2963 ,2963 ,2964 ,2965 ,2965 ,2966 ,2967 ,2967 ,2968 ,2969 ,2970 ,2970 ,2971 ,2972 ,2972 ,2973 ,2974 ,2975 ,2975 ,2976 ,2977 ,2977 ,2978 ,2979 ,2980 ,2980 ,2981 ,2982 ,2982 ,2983 ,2984 ,2984 ,2985 ,2986 ,2987 ,2987 ,2988 ,2989 ,2989 ,2990 ,2991 ,2992 ,2992 ,2993 ,
3021 ,3021 ,3022 ,3023 ,3024 ,3024 ,3025 ,3026 ,3026 ,3027 ,3028 ,3029 ,3029 ,3030 ,3031 ,3031 ,3032 ,3033 ,3034 ,3034 ,3035 ,3036 ,3036 ,3037 ,3038 ,3039 ,3039 ,3040 ,3041 ,3042 ,3042 ,3043 ,3044 ,3044 ,3045 ,3046 ,3047 ,3047 ,3048 ,3049 ,3049 ,3050 ,3051 ,3052 ,3052 ,3053 ,3054 ,3054 ,3055 ,3056 ,3057 ,3057 ,3058 ,3059 ,3059 ,3060 ,3061 ,3062 ,3062 ,3063 ,3064 ,3064 ,3065 ,3066 ,3067 ,3067 ,3068 ,3069 ,3069 ,3070 ,3071 ,3072 ,3072 ,3073 ,3074 ,3074 ,3075 ,3076 ,3077 ,3077 ,3078 ,3079 ,3079 ,3080 ,3081 ,3082 ,3082 ,3083 ,3084 ,3084 ,3085 ,3086 ,3087 ,3087 ,
3020 ,3021 ,3022 ,3023 ,3023 ,3024 ,3025 ,3025 ,3026 ,3027 ,3028 ,3028 ,3029 ,3030 ,3031 ,3031 ,3032 ,3033 ,3033 ,3034 ,3035 ,3036 ,3036 ,3037 ,3038 ,3038 ,3039 ,3040 ,3041 ,3041 ,3042 ,3043 ,3044 ,3044 ,3045 ,3046 ,3046 ,3047 ,3048 ,3049 ,3049 ,3050 ,3051 ,3052 ,3052 ,3053 ,3054 ,3054 ,3055 ,3056 ,3057 ,3057 ,3058 ,3059 ,3059 ,3060 ,3061 ,3062 ,3062 ,3063 ,3064 ,3065 ,3065 ,3066 ,3067 ,3067 ,3068 ,3069 ,3070 ,3070 ,3071 ,3072 ,3073 ,3073 ,3074 ,3075 ,3075 ,3076 ,3077 ,3078 ,3078 ,3079 ,3080 ,3080 ,3081 ,3082 ,3083 ,3083 ,3084 ,3085 ,3086 ,3086 ,3087 ,3088 ,
3114 ,3115 ,3115 ,3116 ,3117 ,3118 ,3118 ,3119 ,3120 ,3121 ,3121 ,3122 ,3123 ,3124 ,3124 ,3125 ,3126 ,3126 ,3127 ,3128 ,3129 ,3129 ,3130 ,3131 ,3132 ,3132 ,3133 ,3134 ,3135 ,3135 ,3136 ,3137 ,3137 ,3138 ,3139 ,3140 ,3140 ,3141 ,3142 ,3143 ,3143 ,3144 ,3145 ,3146 ,3146 ,3147 ,3148 ,3148 ,3149 ,3150 ,3151 ,3151 ,3152 ,3153 ,3154 ,3154 ,3155 ,3156 ,3156 ,3157 ,3158 ,3159 ,3159 ,3160 ,3161 ,3162 ,3162 ,3163 ,3164 ,3165 ,3165 ,3166 ,3167 ,3167 ,3168 ,3169 ,3170 ,3170 ,3171 ,3172 ,3173 ,3173 ,3174 ,3175 ,3176 ,3176 ,3177 ,3178 ,3178 ,3179 ,3180 ,3181 ,3181 ,3182 ,
3208 ,3208 ,3209 ,3210 ,3211 ,3211 ,3212 ,3213 ,3214 ,3214 ,3215 ,3216 ,3217 ,3217 ,3218 ,3219 ,3220 ,3220 ,3221 ,3222 ,3222 ,3223 ,3224 ,3225 ,3225 ,3226 ,3227 ,3228 ,3228 ,3229 ,3230 ,3231 ,3231 ,3232 ,3233 ,3234 ,3234 ,3235 ,3236 ,3237 ,3237 ,3238 ,3239 ,3239 ,3240 ,3241 ,3242 ,3242 ,3243 ,3244 ,3245 ,3245 ,3246 ,3247 ,3248 ,3248 ,3249 ,3250 ,3251 ,3251 ,3252 ,3253 ,3254 ,3254 ,3255 ,3256 ,3256 ,3257 ,3258 ,3259 ,3259 ,3260 ,3261 ,3262 ,3262 ,3263 ,3264 ,3265 ,3265 ,3266 ,3267 ,3268 ,3268 ,3269 ,3270 ,3271 ,3271 ,3272 ,3273 ,3274 ,3274 ,3275 ,3276 ,3276 ,
3301 ,3302 ,3303 ,3304 ,3304 ,3305 ,3306 ,3307 ,3307 ,3308 ,3309 ,3310 ,3310 ,3311 ,3312 ,3313 ,3313 ,3314 ,3315 ,3316 ,3316 ,3317 ,3318 ,3319 ,3319 ,3320 ,3321 ,3322 ,3322 ,3323 ,3324 ,3324 ,3325 ,3326 ,3327 ,3327 ,3328 ,3329 ,3330 ,3330 ,3331 ,3332 ,3333 ,3333 ,3334 ,3335 ,3336 ,3336 ,3337 ,3338 ,3339 ,3339 ,3340 ,3341 ,3342 ,3342 ,3343 ,3344 ,3345 ,3345 ,3346 ,3347 ,3348 ,3348 ,3349 ,3350 ,3351 ,3351 ,3352 ,3353 ,3354 ,3354 ,3355 ,3356 ,3357 ,3357 ,3358 ,3359 ,3360 ,3360 ,3361 ,3362 ,3363 ,3363 ,3364 ,3365 ,3366 ,3366 ,3367 ,3368 ,3369 ,3369 ,3370 ,3371 ,
3395 ,3396 ,3396 ,3397 ,3398 ,3399 ,3399 ,3400 ,3401 ,3402 ,3403 ,3403 ,3404 ,3405 ,3406 ,3406 ,3407 ,3408 ,3409 ,3409 ,3410 ,3411 ,3412 ,3412 ,3413 ,3414 ,3415 ,3415 ,3416 ,3417 ,3418 ,3418 ,3419 ,3420 ,3421 ,3421 ,3422 ,3423 ,3424 ,3424 ,3425 ,3426 ,3427 ,3427 ,3428 ,3429 ,3430 ,3430 ,3431 ,3432 ,3433 ,3434 ,3434 ,3435 ,3436 ,3437 ,3437 ,3438 ,3439 ,3440 ,3440 ,3441 ,3442 ,3443 ,3443 ,3444 ,3445 ,3446 ,3446 ,3447 ,3448 ,3449 ,3449 ,3450 ,3451 ,3452 ,3452 ,3453 ,3454 ,3455 ,3455 ,3456 ,3457 ,3458 ,3458 ,3459 ,3460 ,3461 ,3461 ,3462 ,3463 ,3464 ,3465 ,3465 ,
3395 ,3395 ,3396 ,3397 ,3398 ,3398 ,3399 ,3400 ,3401 ,3401 ,3402 ,3403 ,3404 ,3405 ,3405 ,3406 ,3407 ,3408 ,3408 ,3409 ,3410 ,3411 ,3411 ,3412 ,3413 ,3414 ,3414 ,3415 ,3416 ,3417 ,3418 ,3418 ,3419 ,3420 ,3421 ,3421 ,3422 ,3423 ,3424 ,3424 ,3425 ,3426 ,3427 ,3427 ,3428 ,3429 ,3430 ,3430 ,3431 ,3432 ,3433 ,3434 ,3434 ,3435 ,3436 ,3437 ,3437 ,3438 ,3439 ,3440 ,3440 ,3441 ,3442 ,3443 ,3443 ,3444 ,3445 ,3446 ,3447 ,3447 ,3448 ,3449 ,3450 ,3450 ,3451 ,3452 ,3453 ,3453 ,3454 ,3455 ,3456 ,3456 ,3457 ,3458 ,3459 ,3460 ,3460 ,3461 ,3462 ,3463 ,3463 ,3464 ,3465 ,3466 ,
3488 ,3489 ,3490 ,3490 ,3491 ,3492 ,3493 ,3494 ,3494 ,3495 ,3496 ,3497 ,3497 ,3498 ,3499 ,3500 ,3501 ,3501 ,3502 ,3503 ,3504 ,3504 ,3505 ,3506 ,3507 ,3508 ,3508 ,3509 ,3510 ,3511 ,3511 ,3512 ,3513 ,3514 ,3514 ,3515 ,3516 ,3517 ,3518 ,3518 ,3519 ,3520 ,3521 ,3521 ,3522 ,3523 ,3524 ,3525 ,3525 ,3526 ,3527 ,3528 ,3528 ,3529 ,3530 ,3531 ,3531 ,3532 ,3533 ,3534 ,3535 ,3535 ,3536 ,3537 ,3538 ,3538 ,3539 ,3540 ,3541 ,3542 ,3542 ,3543 ,3544 ,3545 ,3545 ,3546 ,3547 ,3548 ,3548 ,3549 ,3550 ,3551 ,3552 ,3552 ,3553 ,3554 ,3555 ,3555 ,3556 ,3557 ,3558 ,3559 ,3559 ,3560 ,
3582 ,3583 ,3583 ,3584 ,3585 ,3586 ,3586 ,3587 ,3588 ,3589 ,3590 ,3590 ,3591 ,3592 ,3593 ,3594 ,3594 ,3595 ,3596 ,3597 ,3597 ,3598 ,3599 ,3600 ,3601 ,3601 ,3602 ,3603 ,3604 ,3604 ,3605 ,3606 ,3607 ,3608 ,3608 ,3609 ,3610 ,3611 ,3611 ,3612 ,3613 ,3614 ,3615 ,3615 ,3616 ,3617 ,3618 ,3619 ,3619 ,3620 ,3621 ,3622 ,3622 ,3623 ,3624 ,3625 ,3626 ,3626 ,3627 ,3628 ,3629 ,3629 ,3630 ,3631 ,3632 ,3633 ,3633 ,3634 ,3635 ,3636 ,3637 ,3637 ,3638 ,3639 ,3640 ,3640 ,3641 ,3642 ,3643 ,3644 ,3644 ,3645 ,3646 ,3647 ,3647 ,3648 ,3649 ,3650 ,3651 ,3651 ,3652 ,3653 ,3654 ,3655 ,
3675 ,3676 ,3677 ,3678 ,3679 ,3679 ,3680 ,3681 ,3682 ,3682 ,3683 ,3684 ,3685 ,3686 ,3686 ,3687 ,3688 ,3689 ,3690 ,3690 ,3691 ,3692 ,3693 ,3694 ,3694 ,3695 ,3696 ,3697 ,3698 ,3698 ,3699 ,3700 ,3701 ,3701 ,3702 ,3703 ,3704 ,3705 ,3705 ,3706 ,3707 ,3708 ,3709 ,3709 ,3710 ,3711 ,3712 ,3713 ,3713 ,3714 ,3715 ,3716 ,3717 ,3717 ,3718 ,3719 ,3720 ,3720 ,3721 ,3722 ,3723 ,3724 ,3724 ,3725 ,3726 ,3727 ,3728 ,3728 ,3729 ,3730 ,3731 ,3732 ,3732 ,3733 ,3734 ,3735 ,3735 ,3736 ,3737 ,3738 ,3739 ,3739 ,3740 ,3741 ,3742 ,3743 ,3743 ,3744 ,3745 ,3746 ,3747 ,3747 ,3748 ,3749 ,
3769 ,3770 ,3771 ,3771 ,3772 ,3773 ,3774 ,3775 ,3775 ,3776 ,3777 ,3778 ,3779 ,3779 ,3780 ,3781 ,3782 ,3783 ,3783 ,3784 ,3785 ,3786 ,3787 ,3787 ,3788 ,3789 ,3790 ,3791 ,3791 ,3792 ,3793 ,3794 ,3795 ,3795 ,3796 ,3797 ,3798 ,3799 ,3799 ,3800 ,3801 ,3802 ,3803 ,3803 ,3804 ,3805 ,3806 ,3807 ,3807 ,3808 ,3809 ,3810 ,3811 ,3811 ,3812 ,3813 ,3814 ,3815 ,3815 ,3816 ,3817 ,3818 ,3819 ,3819 ,3820 ,3821 ,3822 ,3823 ,3823 ,3824 ,3825 ,3826 ,3827 ,3827 ,3828 ,3829 ,3830 ,3831 ,3831 ,3832 ,3833 ,3834 ,3835 ,3835 ,3836 ,3837 ,3838 ,3839 ,3839 ,3840 ,3841 ,3842 ,3843 ,3843 ,
3863 ,3863 ,3864 ,3865 ,3866 ,3867 ,3867 ,3868 ,3869 ,3870 ,3871 ,3871 ,3872 ,3873 ,3874 ,3875 ,3875 ,3876 ,3877 ,3878 ,3879 ,3880 ,3880 ,3881 ,3882 ,3883 ,3884 ,3884 ,3885 ,3886 ,3887 ,3888 ,3888 ,3889 ,3890 ,3891 ,3892 ,3892 ,3893 ,3894 ,3895 ,3896 ,3897 ,3897 ,3898 ,3899 ,3900 ,3901 ,3901 ,3902 ,3903 ,3904 ,3905 ,3905 ,3906 ,3907 ,3908 ,3909 ,3910 ,3910 ,3911 ,3912 ,3913 ,3914 ,3914 ,3915 ,3916 ,3917 ,3918 ,3918 ,3919 ,3920 ,3921 ,3922 ,3922 ,3923 ,3924 ,3925 ,3926 ,3927 ,3927 ,3928 ,3929 ,3930 ,3931 ,3931 ,3932 ,3933 ,3934 ,3935 ,3935 ,3936 ,3937 ,3938 ,
3956 ,3957 ,3958 ,3959 ,3959 ,3960 ,3961 ,3962 ,3963 ,3963 ,3964 ,3965 ,3966 ,3967 ,3968 ,3968 ,3969 ,3970 ,3971 ,3972 ,3972 ,3973 ,3974 ,3975 ,3976 ,3977 ,3977 ,3978 ,3979 ,3980 ,3981 ,3982 ,3982 ,3983 ,3984 ,3985 ,3986 ,3986 ,3987 ,3988 ,3989 ,3990 ,3991 ,3991 ,3992 ,3993 ,3994 ,3995 ,3995 ,3996 ,3997 ,3998 ,3999 ,4000 ,4000 ,4001 ,4002 ,4003 ,4004 ,4004 ,4005 ,4006 ,4007 ,4008 ,4009 ,4009 ,4010 ,4011 ,4012 ,4013 ,4013 ,4014 ,4015 ,4016 ,4017 ,4018 ,4018 ,4019 ,4020 ,4021 ,4022 ,4022 ,4023 ,4024 ,4025 ,4026 ,4027 ,4027 ,4028 ,4029 ,4030 ,4031 ,4032 ,4032 ,
4050 ,4050 ,4051 ,4052 ,4053 ,4054 ,4055 ,4055 ,4056 ,4057 ,4058 ,4059 ,4060 ,4060 ,4061 ,4062 ,4063 ,4064 ,4065 ,4065 ,4066 ,4067 ,4068 ,4069 ,4070 ,4070 ,4071 ,4072 ,4073 ,4074 ,4075 ,4075 ,4076 ,4077 ,4078 ,4079 ,4080 ,4080 ,4081 ,4082 ,4083 ,4084 ,4084 ,4085 ,4086 ,4087 ,4088 ,4089 ,4089 ,4090 ,4091 ,4092 ,4093 ,4094 ,4094 ,4095 ,4096 ,4097 ,4098 ,4099 ,4099 ,4100 ,4101 ,4102 ,4103 ,4104 ,4104 ,4105 ,4106 ,4107 ,4108 ,4109 ,4109 ,4110 ,4111 ,4112 ,4113 ,4114 ,4114 ,4115 ,4116 ,4117 ,4118 ,4119 ,4119 ,4120 ,4121 ,4122 ,4123 ,4123 ,4124 ,4125 ,4126 ,4127 ,
4143 ,4144 ,4145 ,4146 ,4147 ,4147 ,4148 ,4149 ,4150 ,4151 ,4152 ,4152 ,4153 ,4154 ,4155 ,4156 ,4157 ,4157 ,4158 ,4159 ,4160 ,4161 ,4162 ,4163 ,4163 ,4164 ,4165 ,4166 ,4167 ,4168 ,4168 ,4169 ,4170 ,4171 ,4172 ,4173 ,4173 ,4174 ,4175 ,4176 ,4177 ,4178 ,4178 ,4179 ,4180 ,4181 ,4182 ,4183 ,4183 ,4184 ,4185 ,4186 ,4187 ,4188 ,4189 ,4189 ,4190 ,4191 ,4192 ,4193 ,4194 ,4194 ,4195 ,4196 ,4197 ,4198 ,4199 ,4199 ,4200 ,4201 ,4202 ,4203 ,4204 ,4204 ,4205 ,4206 ,4207 ,4208 ,4209 ,4210 ,4210 ,4211 ,4212 ,4213 ,4214 ,4215 ,4215 ,4216 ,4217 ,4218 ,4219 ,4220 ,4220 ,4221 ,
4237 ,4238 ,4238 ,4239 ,4240 ,4241 ,4242 ,4243 ,4244 ,4244 ,4245 ,4246 ,4247 ,4248 ,4249 ,4249 ,4250 ,4251 ,4252 ,4253 ,4254 ,4255 ,4255 ,4256 ,4257 ,4258 ,4259 ,4260 ,4261 ,4261 ,4262 ,4263 ,4264 ,4265 ,4266 ,4266 ,4267 ,4268 ,4269 ,4270 ,4271 ,4272 ,4272 ,4273 ,4274 ,4275 ,4276 ,4277 ,4278 ,4278 ,4279 ,4280 ,4281 ,4282 ,4283 ,4283 ,4284 ,4285 ,4286 ,4287 ,4288 ,4289 ,4289 ,4290 ,4291 ,4292 ,4293 ,4294 ,4295 ,4295 ,4296 ,4297 ,4298 ,4299 ,4300 ,4300 ,4301 ,4302 ,4303 ,4304 ,4305 ,4306 ,4306 ,4307 ,4308 ,4309 ,4310 ,4311 ,4312 ,4312 ,4313 ,4314 ,4315 ,4316 ,
4330 ,4331 ,4332 ,4333 ,4334 ,4335 ,4335 ,4336 ,4337 ,4338 ,4339 ,4340 ,4341 ,4341 ,4342 ,4343 ,4344 ,4345 ,4346 ,4347 ,4347 ,4348 ,4349 ,4350 ,4351 ,4352 ,4353 ,4353 ,4354 ,4355 ,4356 ,4357 ,4358 ,4359 ,4360 ,4360 ,4361 ,4362 ,4363 ,4364 ,4365 ,4366 ,4366 ,4367 ,4368 ,4369 ,4370 ,4371 ,4372 ,4372 ,4373 ,4374 ,4375 ,4376 ,4377 ,4378 ,4378 ,4379 ,4380 ,4381 ,4382 ,4383 ,4384 ,4384 ,4385 ,4386 ,4387 ,4388 ,4389 ,4390 ,4391 ,4391 ,4392 ,4393 ,4394 ,4395 ,4396 ,4397 ,4397 ,4398 ,4399 ,4400 ,4401 ,4402 ,4403 ,4403 ,4404 ,4405 ,4406 ,4407 ,4408 ,4409 ,4409 ,4410 ,
4424 ,4425 ,4425 ,4426 ,4427 ,4428 ,4429 ,4430 ,4431 ,4432 ,4432 ,4433 ,4434 ,4435 ,4436 ,4437 ,4438 ,4439 ,4439 ,4440 ,4441 ,4442 ,4443 ,4444 ,4445 ,4446 ,4446 ,4447 ,4448 ,4449 ,4450 ,4451 ,4452 ,4453 ,4453 ,4454 ,4455 ,4456 ,4457 ,4458 ,4459 ,4459 ,4460 ,4461 ,4462 ,4463 ,4464 ,4465 ,4466 ,4466 ,4467 ,4468 ,4469 ,4470 ,4471 ,4472 ,4473 ,4473 ,4474 ,4475 ,4476 ,4477 ,4478 ,4479 ,4480 ,4480 ,4481 ,4482 ,4483 ,4484 ,4485 ,4486 ,4487 ,4487 ,4488 ,4489 ,4490 ,4491 ,4492 ,4493 ,4494 ,4494 ,4495 ,4496 ,4497 ,4498 ,4499 ,4500 ,4500 ,4501 ,4502 ,4503 ,4504 ,4505 ,
4517 ,4518 ,4519 ,4520 ,4521 ,4522 ,4523 ,4523 ,4524 ,4525 ,4526 ,4527 ,4528 ,4529 ,4530 ,4530 ,4531 ,4532 ,4533 ,4534 ,4535 ,4536 ,4537 ,4538 ,4538 ,4539 ,4540 ,4541 ,4542 ,4543 ,4544 ,4545 ,4546 ,4546 ,4547 ,4548 ,4549 ,4550 ,4551 ,4552 ,4553 ,4553 ,4554 ,4555 ,4556 ,4557 ,4558 ,4559 ,4560 ,4561 ,4561 ,4562 ,4563 ,4564 ,4565 ,4566 ,4567 ,4568 ,4568 ,4569 ,4570 ,4571 ,4572 ,4573 ,4574 ,4575 ,4576 ,4576 ,4577 ,4578 ,4579 ,4580 ,4581 ,4582 ,4583 ,4583 ,4584 ,4585 ,4586 ,4587 ,4588 ,4589 ,4590 ,4591 ,4591 ,4592 ,4593 ,4594 ,4595 ,4596 ,4597 ,4598 ,4599 ,4599 ,
4611 ,4612 ,4613 ,4613 ,4614 ,4615 ,4616 ,4617 ,4618 ,4619 ,4620 ,4621 ,4621 ,4622 ,4623 ,4624 ,4625 ,4626 ,4627 ,4628 ,4629 ,4630 ,4630 ,4631 ,4632 ,4633 ,4634 ,4635 ,4636 ,4637 ,4638 ,4638 ,4639 ,4640 ,4641 ,4642 ,4643 ,4644 ,4645 ,4646 ,4647 ,4647 ,4648 ,4649 ,4650 ,4651 ,4652 ,4653 ,4654 ,4655 ,4655 ,4656 ,4657 ,4658 ,4659 ,4660 ,4661 ,4662 ,4663 ,4664 ,4664 ,4665 ,4666 ,4667 ,4668 ,4669 ,4670 ,4671 ,4672 ,4672 ,4673 ,4674 ,4675 ,4676 ,4677 ,4678 ,4679 ,4680 ,4681 ,4681 ,4682 ,4683 ,4684 ,4685 ,4686 ,4687 ,4688 ,4689 ,4689 ,4690 ,4691 ,4692 ,4693 ,4694 ,
4798 ,4799 ,4800 ,4801 ,4802 ,4803 ,4804 ,4805 ,4805 ,4806 ,4807 ,4808 ,4809 ,4810 ,4811 ,4812 ,4813 ,4814 ,4815 ,4815 ,4816 ,4817 ,4818 ,4819 ,4820 ,4821 ,4822 ,4823 ,4824 ,4824 ,4825 ,4826 ,4827 ,4828 ,4829 ,4830 ,4831 ,4832 ,4833 ,4834 ,4834 ,4835 ,4836 ,4837 ,4838 ,4839 ,4840 ,4841 ,4842 ,4843 ,4844 ,4844 ,4845 ,4846 ,4847 ,4848 ,4849 ,4850 ,4851 ,4852 ,4853 ,4853 ,4854 ,4855 ,4856 ,4857 ,4858 ,4859 ,4860 ,4861 ,4862 ,4863 ,4863 ,4864 ,4865 ,4866 ,4867 ,4868 ,4869 ,4870 ,4871 ,4872 ,4873 ,4873 ,4874 ,4875 ,4876 ,4877 ,4878 ,4879 ,4880 ,4881 ,4882 ,4883 ,
4892 ,4893 ,4893 ,4894 ,4895 ,4896 ,4897 ,4898 ,4899 ,4900 ,4901 ,4902 ,4903 ,4904 ,4904 ,4905 ,4906 ,4907 ,4908 ,4909 ,4910 ,4911 ,4912 ,4913 ,4914 ,4915 ,4916 ,4916 ,4917 ,4918 ,4919 ,4920 ,4921 ,4922 ,4923 ,4924 ,4925 ,4926 ,4927 ,4927 ,4928 ,4929 ,4930 ,4931 ,4932 ,4933 ,4934 ,4935 ,4936 ,4937 ,4938 ,4939 ,4939 ,4940 ,4941 ,4942 ,4943 ,4944 ,4945 ,4946 ,4947 ,4948 ,4949 ,4950 ,4950 ,4951 ,4952 ,4953 ,4954 ,4955 ,4956 ,4957 ,4958 ,4959 ,4960 ,4961 ,4961 ,4962 ,4963 ,4964 ,4965 ,4966 ,4967 ,4968 ,4969 ,4970 ,4971 ,4972 ,4973 ,4973 ,4974 ,4975 ,4976 ,4977 ,
4985 ,4986 ,4987 ,4988 ,4989 ,4990 ,4991 ,4992 ,4993 ,4993 ,4994 ,4995 ,4996 ,4997 ,4998 ,4999 ,5000 ,5001 ,5002 ,5003 ,5004 ,5005 ,5006 ,5006 ,5007 ,5008 ,5009 ,5010 ,5011 ,5012 ,5013 ,5014 ,5015 ,5016 ,5017 ,5018 ,5019 ,5020 ,5020 ,5021 ,5022 ,5023 ,5024 ,5025 ,5026 ,5027 ,5028 ,5029 ,5030 ,5031 ,5032 ,5033 ,5034 ,5034 ,5035 ,5036 ,5037 ,5038 ,5039 ,5040 ,5041 ,5042 ,5043 ,5044 ,5045 ,5046 ,5047 ,5047 ,5048 ,5049 ,5050 ,5051 ,5052 ,5053 ,5054 ,5055 ,5056 ,5057 ,5058 ,5059 ,5060 ,5061 ,5061 ,5062 ,5063 ,5064 ,5065 ,5066 ,5067 ,5068 ,5069 ,5070 ,5071 ,5072 ,
5078 ,5079 ,5080 ,5081 ,5082 ,5083 ,5084 ,5085 ,5086 ,5087 ,5088 ,5089 ,5090 ,5091 ,5092 ,5093 ,5094 ,5095 ,5095 ,5096 ,5097 ,5098 ,5099 ,5100 ,5101 ,5102 ,5103 ,5104 ,5105 ,5106 ,5107 ,5108 ,5109 ,5110 ,5111 ,5112 ,5112 ,5113 ,5114 ,5115 ,5116 ,5117 ,5118 ,5119 ,5120 ,5121 ,5122 ,5123 ,5124 ,5125 ,5126 ,5127 ,5128 ,5129 ,5129 ,5130 ,5131 ,5132 ,5133 ,5134 ,5135 ,5136 ,5137 ,5138 ,5139 ,5140 ,5141 ,5142 ,5143 ,5144 ,5145 ,5146 ,5146 ,5147 ,5148 ,5149 ,5150 ,5151 ,5152 ,5153 ,5154 ,5155 ,5156 ,5157 ,5158 ,5159 ,5160 ,5161 ,5162 ,5163 ,5163 ,5164 ,5165 ,5166 ,
5266 ,5267 ,5268 ,5269 ,5270 ,5271 ,5272 ,5273 ,5274 ,5275 ,5275 ,5276 ,5277 ,5278 ,5279 ,5280 ,5281 ,5282 ,5283 ,5284 ,5285 ,5286 ,5287 ,5288 ,5289 ,5290 ,5291 ,5292 ,5293 ,5294 ,5295 ,5296 ,5297 ,5298 ,5298 ,5299 ,5300 ,5301 ,5302 ,5303 ,5304 ,5305 ,5306 ,5307 ,5308 ,5309 ,5310 ,5311 ,5312 ,5313 ,5314 ,5315 ,5316 ,5317 ,5318 ,5319 ,5320 ,5320 ,5321 ,5322 ,5323 ,5324 ,5325 ,5326 ,5327 ,5328 ,5329 ,5330 ,5331 ,5332 ,5333 ,5334 ,5335 ,5336 ,5337 ,5338 ,5339 ,5340 ,5341 ,5342 ,5343 ,5343 ,5344 ,5345 ,5346 ,5347 ,5348 ,5349 ,5350 ,5351 ,5352 ,5353 ,5354 ,5355 ,
5359 ,5360 ,5361 ,5362 ,5363 ,5364 ,5365 ,5366 ,5367 ,5368 ,5369 ,5370 ,5371 ,5372 ,5373 ,5374 ,5375 ,5376 ,5377 ,5378 ,5379 ,5380 ,5381 ,5382 ,5383 ,5384 ,5385 ,5386 ,5386 ,5387 ,5388 ,5389 ,5390 ,5391 ,5392 ,5393 ,5394 ,5395 ,5396 ,5397 ,5398 ,5399 ,5400 ,5401 ,5402 ,5403 ,5404 ,5405 ,5406 ,5407 ,5408 ,5409 ,5410 ,5411 ,5412 ,5413 ,5414 ,5415 ,5416 ,5417 ,5418 ,5419 ,5420 ,5420 ,5421 ,5422 ,5423 ,5424 ,5425 ,5426 ,5427 ,5428 ,5429 ,5430 ,5431 ,5432 ,5433 ,5434 ,5435 ,5436 ,5437 ,5438 ,5439 ,5440 ,5441 ,5442 ,5443 ,5444 ,5445 ,5446 ,5447 ,5448 ,5449 ,5450 ,
5547 ,5548 ,5549 ,5550 ,5551 ,5552 ,5553 ,5554 ,5555 ,5556 ,5557 ,5557 ,5558 ,5559 ,5560 ,5561 ,5562 ,5563 ,5564 ,5565 ,5566 ,5567 ,5568 ,5569 ,5570 ,5571 ,5572 ,5573 ,5574 ,5575 ,5576 ,5577 ,5578 ,5579 ,5580 ,5581 ,5582 ,5583 ,5584 ,5585 ,5586 ,5587 ,5588 ,5589 ,5590 ,5591 ,5592 ,5593 ,5594 ,5595 ,5596 ,5597 ,5598 ,5599 ,5600 ,5601 ,5602 ,5603 ,5604 ,5605 ,5606 ,5607 ,5608 ,5609 ,5610 ,5611 ,5612 ,5613 ,5614 ,5615 ,5616 ,5617 ,5618 ,5619 ,5620 ,5621 ,5622 ,5623 ,5624 ,5625 ,5625 ,5626 ,5627 ,5628 ,5629 ,5630 ,5631 ,5632 ,5633 ,5634 ,5635 ,5636 ,5637 ,5638 
};
