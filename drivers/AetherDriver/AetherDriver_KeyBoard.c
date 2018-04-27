#include "include.h"

void KeyBoard_Init(void)
{
    PORT_SetPinMux(KEY_PORT_BASE,KEY1,kPORT_MuxAsGpio);
    PORT_SetPinMux(KEY_PORT_BASE,KEY2,kPORT_MuxAsGpio);
    PORT_SetPinMux(KEY_PORT_BASE,KEY3,kPORT_MuxAsGpio);
    PORT_SetPinMux(KEY_PORT_BASE,KEY4,kPORT_MuxAsGpio);

    gpio_init(KEY_BASE,KEY1,IN,LOW);
    gpio_init(KEY_BASE,KEY2,IN,LOW);
    gpio_init(KEY_BASE,KEY3,IN,LOW);
    gpio_init(KEY_BASE,KEY4,IN,LOW);
}

void FiveKey_Init()
{
    port_pin_config_t config = {
      kPORT_PullUp,
      kPORT_FastSlewRate,
      kPORT_PassiveFilterDisable,
      kPORT_OpenDrainDisable,
      kPORT_LowDriveStrength,
      kPORT_MuxAsGpio,
      kPORT_UnlockRegister,
	 };
 
    PORT_SetPinConfig(PORTE,6U,&config);
    PORT_SetPinConfig(PORTE,7U,&config);
    PORT_SetPinConfig(PORTE,8U,&config);
    PORT_SetPinConfig(PORTE,9U,&config);
    PORT_SetPinConfig(PORTE,10U,&config);

    gpio_init(GPIOE,6U,IN,LOW);  
    gpio_init(GPIOE,7U,IN,LOW);
    gpio_init(GPIOE,8U,IN,LOW);
    gpio_init(GPIOE,9U,IN,LOW);
    gpio_init(GPIOE,10U,IN,LOW);
}

void Button_Init()
{
  port_pin_config_t config = {
      kPORT_PullUp,
      kPORT_FastSlewRate,
      kPORT_PassiveFilterDisable,
      kPORT_OpenDrainDisable,
      kPORT_LowDriveStrength,
      kPORT_MuxAsGpio,
      kPORT_UnlockRegister,
 };
 
    PORT_SetPinConfig(BUTTON_PORT_BASE,BUTTON_LEFT,&config);
    PORT_SetPinConfig(BUTTON_PORT_BASE,BUTTON_RIGHT,&config); 
    gpio_init(BUTTON_PORT_BASE,BUTTON_LEFT,IN,LOW);
    gpio_init(BUTTON_PORT_BASE,BUTTON_RIGHT,IN,LOW);
}
