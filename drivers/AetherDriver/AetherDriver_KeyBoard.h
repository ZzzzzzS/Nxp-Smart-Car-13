#ifndef __AETHER_KEYBOARD__
#define __AETHER_KEYBOARD__

#include "include.h"

#define KEY_BASE GPIOD
#define KEY_PORT_BASE PORTD 

#define KEY1 0U
#define KEY2 1U
#define KEY3 2U
#define KEY4 3U


#define KEY_UP !gpio_read(GPIOE,8)
#define KEY_DOWN !gpio_read(GPIOE,6)
#define KEY_LEFT !gpio_read(GPIOE,7)
#define KEY_RIGHT !gpio_read(GPIOE,9)
#define KEY_ENTER !gpio_read(GPIOE,10)

#define BUTTON_BASE GPIOE 
#define BUTTON_PORT_BASE PORTE 

#define BUTTON_LEFT  30U
#define BUTTON_RIGHT 29U

#define READ_LEFT    !gpio_read(BUTTON_BASE,BUTTON_LEFT)
#define READ_RIGHT   !gpio_read(BUTTON_BASE,BUTTON_RIGHT)

#define READ_KEY1 gpio_read(KEY_BASE,KEY1)
extern void KeyBoard_Init(void); 
static inline uint8_t Key_read(uint8_t key)
{
    return (((KEY_BASE->PDIR) >> key) & 0x01U);
}

extern void Button_Init();
extern void FiveKey_Init();
#endif
