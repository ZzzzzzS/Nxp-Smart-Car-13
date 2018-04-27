#include "include.h"

void Beep_Init()
{
    PORT_SetPinMux(BEEP_PORT_BASE,BEEP_PIN,kPORT_MuxAsGpio);
    gpio_init(BEEP_BASE,BEEP_PIN,OUT,LOW);
}