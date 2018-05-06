#ifndef __INDUCTANCE__
#define __INDUCTANCE__ 
typedef struct 
{
    float max;
    float min;
}ADside;

extern ADside Left_side, Right_side;
extern void AD_Get_side();


#endif 
