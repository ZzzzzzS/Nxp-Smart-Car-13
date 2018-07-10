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
	 uint8_t column = 0;             //列
    uint8_t row = 59;                //行
	uint32_t line_sum = 0;
	uint32_t average = 0;

    for(int i=MT9V034_W-1;i>=0;i-=2)
    {
        row = 59;
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
			--row;
		}
        ++column;
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

volatile uint16_t map[60*94] = {
0 ,0 ,0 ,0 ,0 ,1316 ,1317 ,1318 ,1319 ,1320 ,1321 ,1322 ,1323 ,1325 ,1326 ,1327 ,1328 ,1329 ,1330 ,1331 ,1332 ,1333 ,1334 ,1335 ,1336 ,1338 ,1339 ,1340 ,1341 ,1342 ,1343 ,1344 ,1345 ,1346 ,1347 ,1348 ,1349 ,1350 ,1351 ,1353 ,1354 ,1355 ,1356 ,1357 ,1358 ,1359 ,1360 ,1361 ,1362 ,1363 ,1364 ,1365 ,1367 ,1368 ,1369 ,1370 ,1371 ,1372 ,1373 ,1374 ,1375 ,1376 ,1377 ,1378 ,1379 ,1380 ,1382 ,1383 ,1384 ,1385 ,1386 ,1387 ,1388 ,1389 ,1390 ,1391 ,1392 ,1393 ,1395 ,1396 ,1397 ,1398 ,1399 ,1400 ,1401 ,1402 ,1403 ,1404 ,1405 ,1406 ,1407 ,1408 ,1410 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,1316 ,1318 ,1319 ,1320 ,1321 ,1322 ,1323 ,1324 ,1325 ,1326 ,1327 ,1328 ,1330 ,1331 ,1332 ,1333 ,1334 ,1335 ,1336 ,1337 ,1338 ,1339 ,1340 ,1342 ,1343 ,1344 ,1345 ,1346 ,1347 ,1348 ,1349 ,1350 ,1351 ,1352 ,1353 ,1355 ,1356 ,1357 ,1358 ,1359 ,1360 ,1361 ,1362 ,1363 ,1364 ,1366 ,1367 ,1368 ,1369 ,1370 ,1371 ,1372 ,1373 ,1374 ,1375 ,1376 ,1378 ,1379 ,1380 ,1381 ,1382 ,1383 ,1384 ,1385 ,1386 ,1387 ,1388 ,1389 ,1391 ,1392 ,1393 ,1394 ,1395 ,1396 ,1397 ,1398 ,1399 ,1400 ,1402 ,1403 ,1404 ,1405 ,1406 ,1407 ,1408 ,1409 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,1317 ,1318 ,1319 ,1320 ,1321 ,1322 ,1324 ,1325 ,1326 ,1327 ,1328 ,1329 ,1330 ,1331 ,1332 ,1333 ,1335 ,1336 ,1337 ,1338 ,1339 ,1340 ,1341 ,1342 ,1343 ,1345 ,1346 ,1347 ,1348 ,1349 ,1350 ,1351 ,1352 ,1353 ,1355 ,1356 ,1357 ,1358 ,1359 ,1360 ,1361 ,1362 ,1363 ,1365 ,1366 ,1367 ,1368 ,1369 ,1370 ,1371 ,1372 ,1373 ,1374 ,1376 ,1377 ,1378 ,1379 ,1380 ,1381 ,1382 ,1383 ,1384 ,1386 ,1387 ,1388 ,1389 ,1390 ,1391 ,1392 ,1393 ,1394 ,1396 ,1397 ,1398 ,1399 ,1400 ,1401 ,1402 ,1403 ,1404 ,1405 ,1407 ,1408 ,1409 ,1410 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,1316 ,1317 ,1319 ,1320 ,1321 ,1322 ,1323 ,1324 ,1325 ,1326 ,1327 ,1329 ,1330 ,1331 ,1332 ,1333 ,1334 ,1335 ,1336 ,1338 ,1339 ,1340 ,1341 ,1342 ,1343 ,1344 ,1345 ,1347 ,1348 ,1349 ,1350 ,1351 ,1352 ,1353 ,1354 ,1356 ,1357 ,1358 ,1359 ,1360 ,1361 ,1362 ,1363 ,1365 ,1366 ,1367 ,1368 ,1369 ,1370 ,1371 ,1372 ,1374 ,1375 ,1376 ,1377 ,1378 ,1379 ,1380 ,1381 ,1383 ,1384 ,1385 ,1386 ,1387 ,1388 ,1389 ,1390 ,1392 ,1393 ,1394 ,1395 ,1396 ,1397 ,1398 ,1399 ,1401 ,1402 ,1403 ,1404 ,1405 ,1406 ,1407 ,1408 ,1410 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1411 ,1412 ,1413 ,1414 ,1415 ,1416 ,1418 ,1419 ,1420 ,1421 ,1422 ,1423 ,1424 ,1426 ,1427 ,1428 ,1429 ,1430 ,1431 ,1432 ,1433 ,1435 ,1436 ,1437 ,1438 ,1439 ,1440 ,1442 ,1443 ,1444 ,1445 ,1446 ,1447 ,1448 ,1449 ,1451 ,1452 ,1453 ,1454 ,1455 ,1456 ,1458 ,1459 ,1460 ,1461 ,1462 ,1463 ,1464 ,1466 ,1467 ,1468 ,1469 ,1470 ,1471 ,1472 ,1473 ,1475 ,1476 ,1477 ,1478 ,1479 ,1480 ,1482 ,1483 ,1484 ,1485 ,1486 ,1487 ,1488 ,1489 ,1491 ,1492 ,1493 ,1494 ,1495 ,1496 ,1498 ,1499 ,1500 ,1501 ,1502 ,1503 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1410 ,1411 ,1412 ,1414 ,1415 ,1416 ,1417 ,1418 ,1419 ,1421 ,1422 ,1423 ,1424 ,1425 ,1426 ,1427 ,1429 ,1430 ,1431 ,1432 ,1433 ,1434 ,1435 ,1437 ,1438 ,1439 ,1440 ,1441 ,1442 ,1444 ,1445 ,1446 ,1447 ,1448 ,1449 ,1451 ,1452 ,1453 ,1454 ,1455 ,1456 ,1458 ,1459 ,1460 ,1461 ,1462 ,1463 ,1465 ,1466 ,1467 ,1468 ,1469 ,1470 ,1471 ,1473 ,1474 ,1475 ,1476 ,1477 ,1478 ,1480 ,1481 ,1482 ,1483 ,1484 ,1485 ,1487 ,1488 ,1489 ,1490 ,1491 ,1492 ,1494 ,1495 ,1496 ,1497 ,1498 ,1499 ,1501 ,1502 ,1503 ,1504 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1410 ,1412 ,1413 ,1414 ,1415 ,1416 ,1418 ,1419 ,1420 ,1421 ,1422 ,1423 ,1425 ,1426 ,1427 ,1428 ,1429 ,1430 ,1432 ,1433 ,1434 ,1435 ,1436 ,1438 ,1439 ,1440 ,1441 ,1442 ,1443 ,1445 ,1446 ,1447 ,1448 ,1449 ,1451 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1460 ,1461 ,1462 ,1464 ,1465 ,1466 ,1467 ,1468 ,1469 ,1471 ,1472 ,1473 ,1474 ,1475 ,1477 ,1478 ,1479 ,1480 ,1481 ,1482 ,1484 ,1485 ,1486 ,1487 ,1488 ,1490 ,1491 ,1492 ,1493 ,1494 ,1495 ,1497 ,1498 ,1499 ,1500 ,1501 ,1502 ,1504 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1411 ,1412 ,1413 ,1415 ,1416 ,1417 ,1418 ,1419 ,1421 ,1422 ,1423 ,1424 ,1425 ,1427 ,1428 ,1429 ,1430 ,1431 ,1432 ,1434 ,1435 ,1436 ,1437 ,1439 ,1440 ,1441 ,1442 ,1443 ,1444 ,1446 ,1447 ,1448 ,1449 ,1451 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1460 ,1461 ,1462 ,1464 ,1465 ,1466 ,1467 ,1469 ,1470 ,1471 ,1472 ,1473 ,1474 ,1476 ,1477 ,1478 ,1479 ,1481 ,1482 ,1483 ,1484 ,1485 ,1486 ,1488 ,1489 ,1490 ,1491 ,1492 ,1494 ,1495 ,1496 ,1497 ,1498 ,1500 ,1501 ,1502 ,1503 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1410 ,1412 ,1413 ,1414 ,1415 ,1416 ,1418 ,1419 ,1420 ,1421 ,1422 ,1424 ,1425 ,1426 ,1427 ,1429 ,1430 ,1431 ,1432 ,1433 ,1435 ,1436 ,1437 ,1438 ,1439 ,1441 ,1442 ,1443 ,1444 ,1446 ,1447 ,1448 ,1449 ,1450 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1460 ,1461 ,1463 ,1464 ,1465 ,1466 ,1468 ,1469 ,1470 ,1471 ,1472 ,1474 ,1475 ,1476 ,1477 ,1479 ,1480 ,1481 ,1482 ,1483 ,1485 ,1486 ,1487 ,1488 ,1489 ,1491 ,1492 ,1493 ,1494 ,1496 ,1497 ,1498 ,1499 ,1500 ,1502 ,1503 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1411 ,1412 ,1413 ,1414 ,1416 ,1417 ,1418 ,1419 ,1421 ,1422 ,1423 ,1424 ,1426 ,1427 ,1428 ,1429 ,1431 ,1432 ,1433 ,1434 ,1436 ,1437 ,1438 ,1439 ,1440 ,1442 ,1443 ,1444 ,1445 ,1447 ,1448 ,1449 ,1450 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1460 ,1462 ,1463 ,1464 ,1465 ,1467 ,1468 ,1469 ,1470 ,1472 ,1473 ,1474 ,1475 ,1477 ,1478 ,1479 ,1480 ,1481 ,1483 ,1484 ,1485 ,1486 ,1488 ,1489 ,1490 ,1491 ,1493 ,1494 ,1495 ,1496 ,1497 ,1499 ,1500 ,1501 ,1502 ,1504 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1410 ,1411 ,1413 ,1414 ,1415 ,1416 ,1418 ,1419 ,1420 ,1421 ,1423 ,1424 ,1425 ,1426 ,1428 ,1429 ,1430 ,1431 ,1433 ,1434 ,1435 ,1436 ,1438 ,1439 ,1440 ,1441 ,1443 ,1444 ,1445 ,1447 ,1448 ,1449 ,1450 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1460 ,1462 ,1463 ,1464 ,1465 ,1467 ,1468 ,1469 ,1471 ,1472 ,1473 ,1474 ,1476 ,1477 ,1478 ,1479 ,1481 ,1482 ,1483 ,1484 ,1486 ,1487 ,1488 ,1489 ,1491 ,1492 ,1493 ,1495 ,1496 ,1497 ,1498 ,1500 ,1501 ,1502 ,1503 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1411 ,1412 ,1413 ,1414 ,1416 ,1417 ,1418 ,1420 ,1421 ,1422 ,1423 ,1425 ,1426 ,1427 ,1428 ,1430 ,1431 ,1432 ,1434 ,1435 ,1436 ,1437 ,1439 ,1440 ,1441 ,1443 ,1444 ,1445 ,1446 ,1448 ,1449 ,1450 ,1452 ,1453 ,1454 ,1455 ,1457 ,1458 ,1459 ,1461 ,1462 ,1463 ,1464 ,1466 ,1467 ,1468 ,1470 ,1471 ,1472 ,1473 ,1475 ,1476 ,1477 ,1478 ,1480 ,1481 ,1482 ,1484 ,1485 ,1486 ,1488 ,1489 ,1490 ,1491 ,1493 ,1494 ,1495 ,1496 ,1498 ,1499 ,1500 ,1502 ,1503 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1505 ,1506 ,1508 ,1509 ,1510 ,1512 ,1513 ,1514 ,1515 ,1517 ,1518 ,1519 ,1521 ,1522 ,1523 ,1525 ,1526 ,1527 ,1529 ,1530 ,1531 ,1532 ,1534 ,1535 ,1536 ,1538 ,1539 ,1540 ,1542 ,1543 ,1544 ,1545 ,1547 ,1548 ,1549 ,1551 ,1552 ,1553 ,1555 ,1556 ,1557 ,1559 ,1560 ,1561 ,1563 ,1564 ,1565 ,1567 ,1568 ,1569 ,1570 ,1572 ,1573 ,1574 ,1576 ,1577 ,1578 ,1580 ,1581 ,1582 ,1583 ,1585 ,1586 ,1587 ,1589 ,1590 ,1591 ,1593 ,1594 ,1595 ,1596 ,1598 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1504 ,1506 ,1507 ,1508 ,1510 ,1511 ,1512 ,1514 ,1515 ,1516 ,1518 ,1519 ,1520 ,1521 ,1523 ,1524 ,1526 ,1527 ,1528 ,1529 ,1531 ,1532 ,1534 ,1535 ,1536 ,1537 ,1539 ,1540 ,1542 ,1543 ,1544 ,1545 ,1547 ,1548 ,1549 ,1551 ,1552 ,1554 ,1555 ,1556 ,1557 ,1559 ,1560 ,1562 ,1563 ,1564 ,1565 ,1567 ,1568 ,1569 ,1571 ,1572 ,1573 ,1575 ,1576 ,1577 ,1579 ,1580 ,1581 ,1583 ,1584 ,1585 ,1587 ,1588 ,1589 ,1591 ,1592 ,1593 ,1595 ,1596 ,1597 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1505 ,1506 ,1508 ,1509 ,1510 ,1512 ,1513 ,1514 ,1516 ,1517 ,1518 ,1520 ,1521 ,1522 ,1524 ,1525 ,1526 ,1528 ,1529 ,1531 ,1532 ,1533 ,1535 ,1536 ,1537 ,1539 ,1540 ,1541 ,1543 ,1544 ,1545 ,1547 ,1548 ,1550 ,1551 ,1552 ,1554 ,1555 ,1556 ,1558 ,1559 ,1560 ,1562 ,1563 ,1564 ,1566 ,1567 ,1568 ,1570 ,1571 ,1573 ,1574 ,1575 ,1577 ,1578 ,1579 ,1581 ,1582 ,1583 ,1585 ,1586 ,1587 ,1589 ,1590 ,1592 ,1593 ,1594 ,1596 ,1597 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1505 ,1507 ,1508 ,1509 ,1511 ,1512 ,1514 ,1515 ,1516 ,1518 ,1519 ,1520 ,1522 ,1523 ,1525 ,1526 ,1527 ,1529 ,1530 ,1532 ,1533 ,1534 ,1536 ,1537 ,1539 ,1540 ,1541 ,1543 ,1544 ,1545 ,1547 ,1548 ,1550 ,1551 ,1552 ,1554 ,1555 ,1557 ,1558 ,1559 ,1561 ,1562 ,1563 ,1565 ,1566 ,1568 ,1569 ,1570 ,1572 ,1573 ,1574 ,1576 ,1577 ,1579 ,1580 ,1581 ,1583 ,1584 ,1585 ,1587 ,1588 ,1590 ,1591 ,1592 ,1594 ,1595 ,1596 ,1598 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1505 ,1506 ,1507 ,1509 ,1510 ,1512 ,1513 ,1514 ,1516 ,1517 ,1519 ,1520 ,1521 ,1523 ,1524 ,1526 ,1527 ,1528 ,1530 ,1531 ,1533 ,1534 ,1536 ,1537 ,1538 ,1540 ,1541 ,1542 ,1544 ,1545 ,1547 ,1548 ,1550 ,1551 ,1552 ,1554 ,1555 ,1557 ,1558 ,1560 ,1561 ,1562 ,1564 ,1565 ,1566 ,1568 ,1569 ,1571 ,1572 ,1574 ,1575 ,1576 ,1578 ,1579 ,1581 ,1582 ,1583 ,1585 ,1586 ,1588 ,1589 ,1590 ,1592 ,1593 ,1595 ,1596 ,1597 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1505 ,1507 ,1508 ,1510 ,1511 ,1512 ,1514 ,1515 ,1517 ,1518 ,1519 ,1521 ,1522 ,1524 ,1525 ,1527 ,1528 ,1530 ,1531 ,1532 ,1534 ,1535 ,1537 ,1538 ,1540 ,1541 ,1542 ,1544 ,1545 ,1547 ,1548 ,1550 ,1551 ,1552 ,1554 ,1555 ,1557 ,1558 ,1560 ,1561 ,1563 ,1564 ,1565 ,1567 ,1568 ,1570 ,1571 ,1573 ,1574 ,1575 ,1577 ,1578 ,1580 ,1581 ,1583 ,1584 ,1586 ,1587 ,1588 ,1590 ,1591 ,1593 ,1594 ,1595 ,1597 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1598 ,1600 ,1601 ,1603 ,1604 ,1606 ,1607 ,1609 ,1610 ,1611 ,1613 ,1614 ,1616 ,1617 ,1619 ,1620 ,1622 ,1623 ,1625 ,1626 ,1627 ,1629 ,1630 ,1632 ,1633 ,1635 ,1636 ,1638 ,1639 ,1641 ,1642 ,1644 ,1645 ,1647 ,1648 ,1650 ,1651 ,1652 ,1654 ,1655 ,1657 ,1658 ,1660 ,1661 ,1663 ,1664 ,1666 ,1667 ,1669 ,1670 ,1672 ,1673 ,1674 ,1676 ,1677 ,1679 ,1680 ,1682 ,1683 ,1685 ,1686 ,1688 ,1689 ,1691 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1599 ,1600 ,1602 ,1603 ,1605 ,1606 ,1608 ,1609 ,1611 ,1612 ,1614 ,1615 ,1617 ,1618 ,1620 ,1621 ,1623 ,1624 ,1626 ,1627 ,1629 ,1630 ,1632 ,1633 ,1635 ,1636 ,1638 ,1639 ,1641 ,1642 ,1644 ,1645 ,1647 ,1648 ,1650 ,1651 ,1653 ,1654 ,1656 ,1657 ,1659 ,1660 ,1662 ,1663 ,1665 ,1666 ,1668 ,1669 ,1671 ,1672 ,1674 ,1675 ,1677 ,1678 ,1680 ,1681 ,1683 ,1684 ,1686 ,1687 ,1688 ,1690 ,1691 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1598 ,1599 ,1601 ,1603 ,1604 ,1606 ,1607 ,1609 ,1610 ,1612 ,1613 ,1615 ,1616 ,1618 ,1619 ,1621 ,1622 ,1624 ,1625 ,1627 ,1629 ,1630 ,1632 ,1633 ,1635 ,1636 ,1638 ,1639 ,1641 ,1642 ,1644 ,1645 ,1647 ,1648 ,1650 ,1651 ,1653 ,1654 ,1656 ,1658 ,1659 ,1661 ,1662 ,1664 ,1665 ,1667 ,1668 ,1670 ,1671 ,1673 ,1674 ,1676 ,1677 ,1679 ,1680 ,1682 ,1683 ,1685 ,1686 ,1688 ,1689 ,1691 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1599 ,1600 ,1602 ,1603 ,1605 ,1606 ,1608 ,1610 ,1611 ,1613 ,1614 ,1616 ,1617 ,1619 ,1620 ,1622 ,1623 ,1625 ,1627 ,1628 ,1630 ,1631 ,1633 ,1634 ,1636 ,1638 ,1639 ,1641 ,1642 ,1644 ,1645 ,1647 ,1649 ,1650 ,1652 ,1653 ,1655 ,1656 ,1658 ,1659 ,1661 ,1662 ,1664 ,1666 ,1667 ,1669 ,1670 ,1672 ,1673 ,1675 ,1677 ,1678 ,1680 ,1681 ,1683 ,1684 ,1686 ,1687 ,1689 ,1691 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1599 ,1601 ,1602 ,1604 ,1606 ,1607 ,1609 ,1610 ,1612 ,1614 ,1615 ,1617 ,1618 ,1620 ,1622 ,1623 ,1625 ,1626 ,1628 ,1629 ,1631 ,1633 ,1634 ,1636 ,1637 ,1639 ,1641 ,1642 ,1644 ,1646 ,1647 ,1649 ,1650 ,1652 ,1653 ,1655 ,1657 ,1658 ,1660 ,1661 ,1663 ,1665 ,1666 ,1668 ,1669 ,1671 ,1672 ,1674 ,1676 ,1677 ,1679 ,1681 ,1682 ,1684 ,1685 ,1687 ,1688 ,1690 ,1692 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1692 ,1694 ,1696 ,1697 ,1699 ,1700 ,1702 ,1704 ,1705 ,1707 ,1709 ,1710 ,1712 ,1713 ,1715 ,1717 ,1718 ,1720 ,1722 ,1723 ,1725 ,1726 ,1728 ,1730 ,1731 ,1733 ,1735 ,1736 ,1738 ,1740 ,1741 ,1743 ,1744 ,1746 ,1748 ,1749 ,1751 ,1753 ,1754 ,1756 ,1757 ,1759 ,1761 ,1762 ,1764 ,1766 ,1767 ,1769 ,1770 ,1772 ,1774 ,1775 ,1777 ,1779 ,1780 ,1782 ,1783 ,1785 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1693 ,1695 ,1696 ,1698 ,1700 ,1701 ,1703 ,1705 ,1706 ,1708 ,1710 ,1711 ,1713 ,1715 ,1716 ,1718 ,1720 ,1721 ,1723 ,1725 ,1726 ,1728 ,1730 ,1731 ,1733 ,1735 ,1736 ,1738 ,1740 ,1741 ,1743 ,1745 ,1746 ,1748 ,1750 ,1751 ,1753 ,1755 ,1756 ,1758 ,1760 ,1761 ,1763 ,1765 ,1766 ,1768 ,1770 ,1771 ,1773 ,1775 ,1776 ,1778 ,1780 ,1781 ,1783 ,1785 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1694 ,1695 ,1697 ,1699 ,1701 ,1702 ,1704 ,1706 ,1707 ,1709 ,1711 ,1712 ,1714 ,1716 ,1718 ,1719 ,1721 ,1723 ,1724 ,1726 ,1728 ,1729 ,1731 ,1733 ,1735 ,1736 ,1738 ,1740 ,1741 ,1743 ,1745 ,1747 ,1748 ,1750 ,1752 ,1753 ,1755 ,1757 ,1758 ,1760 ,1762 ,1764 ,1765 ,1767 ,1769 ,1770 ,1772 ,1774 ,1775 ,1777 ,1779 ,1781 ,1782 ,1784 ,1786 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1693 ,1694 ,1696 ,1698 ,1700 ,1701 ,1703 ,1705 ,1707 ,1708 ,1710 ,1712 ,1714 ,1715 ,1717 ,1719 ,1721 ,1722 ,1724 ,1726 ,1728 ,1729 ,1731 ,1733 ,1735 ,1736 ,1738 ,1740 ,1742 ,1743 ,1745 ,1747 ,1748 ,1750 ,1752 ,1754 ,1755 ,1757 ,1759 ,1761 ,1762 ,1764 ,1766 ,1768 ,1769 ,1771 ,1773 ,1775 ,1776 ,1778 ,1780 ,1782 ,1783 ,1785 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1787 ,1789 ,1791 ,1793 ,1794 ,1796 ,1798 ,1800 ,1802 ,1803 ,1805 ,1807 ,1809 ,1811 ,1812 ,1814 ,1816 ,1818 ,1819 ,1821 ,1823 ,1825 ,1827 ,1829 ,1830 ,1832 ,1834 ,1836 ,1838 ,1839 ,1841 ,1843 ,1845 ,1846 ,1848 ,1850 ,1852 ,1854 ,1855 ,1857 ,1859 ,1861 ,1863 ,1864 ,1866 ,1868 ,1870 ,1871 ,1873 ,1875 ,1877 ,1879 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1786 ,1788 ,1790 ,1792 ,1794 ,1796 ,1797 ,1799 ,1801 ,1803 ,1805 ,1807 ,1808 ,1810 ,1812 ,1814 ,1816 ,1817 ,1819 ,1821 ,1823 ,1825 ,1827 ,1828 ,1830 ,1832 ,1834 ,1836 ,1838 ,1839 ,1841 ,1843 ,1845 ,1847 ,1849 ,1850 ,1852 ,1854 ,1856 ,1858 ,1860 ,1861 ,1863 ,1865 ,1867 ,1869 ,1871 ,1872 ,1874 ,1876 ,1878 ,1880 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1787 ,1789 ,1791 ,1793 ,1795 ,1796 ,1798 ,1800 ,1802 ,1804 ,1806 ,1808 ,1810 ,1811 ,1813 ,1815 ,1817 ,1819 ,1821 ,1823 ,1825 ,1826 ,1828 ,1830 ,1832 ,1834 ,1836 ,1838 ,1840 ,1842 ,1843 ,1845 ,1847 ,1849 ,1851 ,1853 ,1855 ,1857 ,1858 ,1860 ,1862 ,1864 ,1866 ,1868 ,1870 ,1872 ,1874 ,1876 ,1877 ,1879 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1788 ,1790 ,1792 ,1794 ,1795 ,1798 ,1799 ,1801 ,1803 ,1805 ,1807 ,1809 ,1811 ,1813 ,1815 ,1817 ,1819 ,1821 ,1823 ,1825 ,1826 ,1828 ,1830 ,1832 ,1834 ,1836 ,1838 ,1840 ,1842 ,1844 ,1846 ,1848 ,1850 ,1852 ,1854 ,1855 ,1858 ,1859 ,1861 ,1863 ,1865 ,1867 ,1869 ,1871 ,1873 ,1875 ,1877 ,1879 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1881 ,1883 ,1885 ,1887 ,1889 ,1891 ,1893 ,1895 ,1897 ,1899 ,1900 ,1903 ,1904 ,1907 ,1908 ,1910 ,1912 ,1914 ,1916 ,1918 ,1920 ,1922 ,1924 ,1926 ,1928 ,1930 ,1932 ,1934 ,1936 ,1938 ,1940 ,1942 ,1944 ,1946 ,1948 ,1950 ,1952 ,1954 ,1956 ,1958 ,1960 ,1962 ,1964 ,1966 ,1968 ,1970 ,1972 ,1974 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1882 ,1884 ,1886 ,1888 ,1890 ,1892 ,1894 ,1896 ,1898 ,1900 ,1902 ,1904 ,1906 ,1908 ,1910 ,1912 ,1914 ,1916 ,1918 ,1920 ,1922 ,1924 ,1926 ,1929 ,1930 ,1933 ,1935 ,1937 ,1939 ,1941 ,1943 ,1945 ,1947 ,1949 ,1951 ,1953 ,1955 ,1957 ,1959 ,1961 ,1963 ,1965 ,1967 ,1969 ,1971 ,1973 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1880 ,1882 ,1885 ,1886 ,1889 ,1891 ,1893 ,1895 ,1897 ,1899 ,1901 ,1903 ,1906 ,1907 ,1910 ,1912 ,1914 ,1916 ,1918 ,1920 ,1922 ,1924 ,1927 ,1929 ,1931 ,1933 ,1935 ,1937 ,1939 ,1941 ,1943 ,1946 ,1947 ,1950 ,1952 ,1954 ,1956 ,1958 ,1960 ,1962 ,1964 ,1967 ,1968 ,1971 ,1973 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1975 ,1977 ,1979 ,1982 ,1984 ,1986 ,1988 ,1990 ,1992 ,1995 ,1997 ,1999 ,2001 ,2003 ,2005 ,2008 ,2010 ,2012 ,2014 ,2016 ,2018 ,2021 ,2023 ,2025 ,2027 ,2029 ,2032 ,2034 ,2036 ,2038 ,2040 ,2042 ,2044 ,2046 ,2049 ,2051 ,2053 ,2055 ,2057 ,2059 ,2062 ,2064 ,2066 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1976 ,1978 ,1981 ,1983 ,1985 ,1987 ,1990 ,1992 ,1994 ,1996 ,1998 ,2001 ,2003 ,2005 ,2007 ,2009 ,2012 ,2014 ,2016 ,2018 ,2021 ,2023 ,2025 ,2027 ,2030 ,2032 ,2034 ,2036 ,2038 ,2041 ,2043 ,2045 ,2047 ,2050 ,2052 ,2054 ,2056 ,2059 ,2061 ,2063 ,2065 ,2067 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2069 ,2071 ,2073 ,2076 ,2078 ,2080 ,2083 ,2085 ,2087 ,2089 ,2092 ,2094 ,2096 ,2099 ,2101 ,2103 ,2106 ,2108 ,2110 ,2112 ,2115 ,2117 ,2119 ,2122 ,2124 ,2126 ,2129 ,2131 ,2133 ,2136 ,2138 ,2140 ,2142 ,2145 ,2147 ,2149 ,2152 ,2154 ,2156 ,2159 ,2161 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2070 ,2072 ,2074 ,2077 ,2079 ,2082 ,2084 ,2086 ,2089 ,2091 ,2093 ,2096 ,2098 ,2101 ,2103 ,2105 ,2108 ,2110 ,2112 ,2115 ,2117 ,2120 ,2122 ,2124 ,2127 ,2129 ,2132 ,2134 ,2136 ,2139 ,2141 ,2143 ,2146 ,2148 ,2151 ,2153 ,2155 ,2158 ,2160 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2162 ,2165 ,2167 ,2170 ,2172 ,2175 ,2177 ,2180 ,2182 ,2184 ,2187 ,2189 ,2192 ,2194 ,2197 ,2199 ,2201 ,2204 ,2206 ,2209 ,2212 ,2214 ,2216 ,2219 ,2221 ,2224 ,2226 ,2229 ,2231 ,2233 ,2236 ,2238 ,2241 ,2243 ,2246 ,2248 ,2251 ,2253 ,2256 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2163 ,2166 ,2168 ,2171 ,2174 ,2176 ,2179 ,2181 ,2184 ,2186 ,2189 ,2191 ,2194 ,2196 ,2199 ,2201 ,2204 ,2206 ,2209 ,2212 ,2214 ,2217 ,2219 ,2222 ,2224 ,2227 ,2229 ,2232 ,2234 ,2237 ,2240 ,2242 ,2245 ,2247 ,2250 ,2252 ,2255 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2258 ,2261 ,2264 ,2266 ,2269 ,2272 ,2274 ,2277 ,2279 ,2282 ,2285 ,2287 ,2290 ,2293 ,2295 ,2298 ,2300 ,2303 ,2306 ,2308 ,2311 ,2314 ,2317 ,2319 ,2322 ,2324 ,2327 ,2329 ,2332 ,2335 ,2338 ,2340 ,2343 ,2345 ,2348 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2257 ,2260 ,2262 ,2265 ,2268 ,2271 ,2273 ,2276 ,2279 ,2282 ,2284 ,2287 ,2290 ,2292 ,2295 ,2298 ,2300 ,2303 ,2306 ,2309 ,2312 ,2314 ,2317 ,2320 ,2323 ,2325 ,2328 ,2331 ,2333 ,2336 ,2339 ,2341 ,2344 ,2347 ,2350 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2352 ,2355 ,2358 ,2360 ,2363 ,2366 ,2369 ,2372 ,2375 ,2377 ,2380 ,2383 ,2386 ,2389 ,2392 ,2394 ,2397 ,2400 ,2403 ,2406 ,2409 ,2412 ,2415 ,2418 ,2420 ,2423 ,2426 ,2429 ,2432 ,2435 ,2437 ,2440 ,2443 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2444 ,2447 ,2450 ,2453 ,2456 ,2459 ,2462 ,2465 ,2468 ,2471 ,2474 ,2477 ,2480 ,2483 ,2486 ,2489 ,2492 ,2495 ,2498 ,2501 ,2503 ,2507 ,2509 ,2512 ,2515 ,2518 ,2521 ,2524 ,2527 ,2530 ,2533 ,2536 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2446 ,2449 ,2452 ,2455 ,2458 ,2461 ,2464 ,2467 ,2470 ,2473 ,2476 ,2480 ,2482 ,2486 ,2489 ,2492 ,2495 ,2498 ,2501 ,2504 ,2507 ,2510 ,2513 ,2516 ,2520 ,2522 ,2526 ,2529 ,2532 ,2535 ,2538 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2541 ,2544 ,2547 ,2550 ,2554 ,2557 ,2560 ,2563 ,2567 ,2570 ,2573 ,2576 ,2580 ,2583 ,2586 ,2589 ,2592 ,2596 ,2599 ,2602 ,2605 ,2609 ,2612 ,2615 ,2618 ,2622 ,2625 ,2628 ,2631 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2633 ,2636 ,2640 ,2643 ,2647 ,2650 ,2653 ,2656 ,2660 ,2663 ,2667 ,2670 ,2673 ,2677 ,2680 ,2684 ,2687 ,2690 ,2694 ,2697 ,2700 ,2704 ,2707 ,2711 ,2714 ,2717 ,2720 ,2724 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2729 ,2732 ,2736 ,2739 ,2743 ,2746 ,2750 ,2753 ,2757 ,2760 ,2764 ,2767 ,2771 ,2774 ,2778 ,2781 ,2785 ,2788 ,2792 ,2795 ,2799 ,2802 ,2806 ,2810 ,2813 ,2817 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2820 ,2824 ,2828 ,2832 ,2835 ,2839 ,2842 ,2846 ,2850 ,2854 ,2857 ,2861 ,2865 ,2869 ,2873 ,2876 ,2880 ,2883 ,2887 ,2891 ,2895 ,2898 ,2902 ,2906 ,2910 ,2913 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3010 ,3014 ,3018 ,3022 ,3026 ,3029 ,3034 ,3037 ,3041 ,3045 ,3049 ,3053 ,3057 ,3061 ,3065 ,3069 ,3072 ,3077 ,3080 ,3084 ,3088 ,3092 ,3096 ,3100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3106 ,3110 ,3114 ,3118 ,3122 ,3127 ,3130 ,3135 ,3139 ,3143 ,3147 ,3151 ,3156 ,3159 ,3164 ,3168 ,3172 ,3176 ,3180 ,3184 ,3188 ,3192 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3291 ,3296 ,3300 ,3305 ,3309 ,3313 ,3317 ,3322 ,3326 ,3331 ,3335 ,3340 ,3344 ,3348 ,3353 ,3357 ,3362 ,3366 ,3370 ,3375 ,3379 ,3383 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3387 ,3392 ,3397 ,3401 ,3406 ,3410 ,3415 ,3420 ,3425 ,3429 ,3434 ,3439 ,3443 ,3448 ,3452 ,3457 ,3462 ,3467 ,3471 ,3476 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3573 ,3577 ,3583 ,3587 ,3593 ,3597 ,3602 ,3607 ,3612 ,3617 ,3622 ,3628 ,3632 ,3637 ,3642 ,3647 ,3652 ,3657 ,3662 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3856 ,3862 ,3867 ,3873 ,3878 ,3883 ,3888 ,3894 ,3899 ,3905 ,3910 ,3916 ,3921 ,3926 ,3932 ,3937 ,3943 ,3948 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,4047 ,4053 ,4059 ,4064 ,4070 ,4076 ,4082 ,4087 ,4093 ,4099 ,4105 ,4111 ,4116 ,4122 ,4128 ,4134 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,4326 ,4332 ,4339 ,4344 ,4351 ,4357 ,4364 ,4369 ,4376 ,4383 ,4388 ,4395 ,4401 ,4407 ,4413 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,4704 ,4712 ,4718 ,4725 ,4732 ,4739 ,4746 ,4753 ,4760 ,4767 ,4774 ,4780 ,4788 ,4794 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,5076 ,5084 ,5092 ,5100 ,5107 ,5115 ,5122 ,5130 ,5138 ,5145 ,5153 ,5160 ,5168 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,5551 ,5558 ,5567 ,5575 ,5584 ,5592 ,5601 ,5610 ,5618 ,5626 ,5634 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 
};
