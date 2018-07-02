#ifndef MAGANA_H
#define MAGANA_H
#include "include.h"

extern int getDirectionError3(int16_t* value);//用3电感获取误差
extern int getDirectionError5(int16_t* value);//用5电感获取误差
extern void circleAnalysis(int16_t* value);
#endif