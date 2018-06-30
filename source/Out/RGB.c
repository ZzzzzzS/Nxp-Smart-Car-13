#include "include.h"

void RGB_Init()
{
    PORT_SetPinMux(PORTE,3U,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE,4U,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE,5U,kPORT_MuxAsGpio);

    gpio_init(GPIOE,3,OUT,LOW);
    gpio_init(GPIOE,4,OUT,LOW);
    gpio_init(GPIOE,5,OUT,LOW);
}

void led_red(uint8_t status)
{
  if(status==1)
    gpio_write(GPIOE,3,HIGH);
  else
    gpio_write(GPIOE,3,LOW);
}

void led_green(uint8_t status)
{
  if(status==1)
    gpio_write(GPIOE,4,HIGH);
  else
    gpio_write(GPIOE,4,LOW);
}


void led_blue(uint8_t status)
{
  if(status==1)
    gpio_write(GPIOE,5,HIGH);
  else
    gpio_write(GPIOE,5,LOW);
}

void (*led[])(uint8_t) ={led_red,led_green,led_blue};

void led_light_one(uint8_t input){
  for(int i=0;i<3;i++)
  {
    if(input%3==i)
      led[i](1);
    else
      led[i](0);
  }
}

void led_down(){
  for(int i=0;i<3;i++)
  {
      led[i](0);
  }
}

void led_circle()
{
  for(int i=0;i<3;i++)
  {
    led_light_one(i);
  }
}
