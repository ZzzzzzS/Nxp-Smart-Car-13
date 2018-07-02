#ifndef __AETHER_CONTROLER__
#define __AETHER_CONTROLER__

#include "include.h"


extern void ImageControlor(uint8_t* img);
extern void SteerControlor();
extern void ActiveDiffSpeed();
extern void stop_car();
extern void SystemCtrl_PIT0CallBack();
extern void meetingControl();
#endif