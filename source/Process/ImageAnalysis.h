#ifndef __IMAGE_ANALYSIS__
#define __IMAGE_ANALYSIS__

#define START_LINE 54	//从下往上的起始点
#define Circle_R   5
#define Circle_Big_R 10
extern uint8_t divide_gray;  //二值化阈值

typedef struct{
    uint8_t left;
    uint8_t right;
    uint8_t mid_x;
    uint8_t mid_y;
    uint8_t flag;
}LineBorder;

typedef struct{
	uint8_t x;
	uint8_t y;
}Point;

typedef struct{
	Point points[60];
	uint8_t count;	
}Stack;

typedef struct{
    uint8_t count;
    uint16_t point[3];
}edges;


extern LineBorder linesborder[MT9V034_H/2];
extern uint8_t small_image[MT9V034_H/2][MT9V034_W/2];   //二值化后图像
extern uint8_t converted_image[MT9V034_H/2][MT9V034_W/2];
extern volatile uint16_t map[60*94];
extern Stack SpaceMiddles;
extern Stack EdgeLeft;
extern Stack EdgeRight;

extern __ramfunc uint8_t findCircle(uint8_t* img);
extern __ramfunc uint8_t findOurCircle(uint8_t* img);
extern __ramfunc int16_t I_pow(int16_t num);
extern __ramfunc int16_t I_abs(int num);
extern uint8_t findColumnSpaceMiddle(uint8_t* img,uint8_t row);
extern __ramfunc uint8_t getSmallImage(uint8_t* origin_image, uint8_t* newimage);
extern __ramfunc void  ConvertImg(uint8_t image1[ MT9V034_H/2][ MT9V034_W/2], uint8_t image2[MT9V034_H/2][ MT9V034_W/2]);//桶形失真
extern __ramfunc void correctSmallImage(uint8_t* smallimage, uint8_t* IMAGEMAP);
extern __ramfunc void divide_gray_ajust();
extern __ramfunc uint8_t node(uint8_t* in);
extern __ramfunc void convolution(uint8_t* img);
extern __ramfunc uint8_t JudgeDirection(uint8_t* img);
#if 0
extern __ramfunc int16_t ROUND(float num);
extern __ramfunc void plant(void);
extern __ramfunc void repulation_small(uint8_t* img,Point NowPoint,Point* target);
extern __ramfunc void repulation_big(uint8_t* img,Point NowPoint,Point* target);
extern __ramfunc void gravitation(Point NowPoint,Point* target,float32_t GravitationK,float32_t K_Up);
extern __ramfunc void generatepath(uint8_t* img);
#endif 
extern __ramfunc float32_t F_abs(float32_t num);
extern __ramfunc void findMiddlePointBySpace(uint8_t* img);

#endif
