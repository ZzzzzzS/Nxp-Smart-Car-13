#ifndef __INDUCTANCE__
#define __INDUCTANCE__ 
typedef struct 
{
    int16_t max;
    int16_t min;
}ADside_t;

extern ADside_t ADside[MAX_POSITION];
extern void AD_Get_side();


#endif 
