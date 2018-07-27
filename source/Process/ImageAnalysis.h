#ifndef __IMAGE_ANALYSIS__
#define __IMAGE_ANALYSIS__

extern __ramfunc uint8_t getSmallImage(uint8_t* origin_image, uint8_t* newimage);
extern __ramfunc void correctSmallImage(uint8_t* smallimage, uint8_t* IMAGEMAP);
extern uint8_t small_image[MT9V034_H/2][MT9V034_W/2];

extern void FindMeetingArea(uint8_t *Img);
extern void Get_01_Value(uint8_t* Image_Use);

#endif
