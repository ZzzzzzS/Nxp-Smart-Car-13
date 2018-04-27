#ifndef __AETHER_BEE_
#define __AETHER_BEE_

#include "include.h"

#define BEEP_BASE       GPIOE
#define BEEP_PORT_BASE  PORTE 
#define BEEP_PIN        0

extern void Beep_Init();

static inline void Beep_Up(){
    BEEP_BASE->PDOR |= (1U<<BEEP_PIN);
}

static inline void Beep_Down(){
    BEEP_BASE->PDOR &= ~(1U<<BEEP_PIN);
}


#endif
