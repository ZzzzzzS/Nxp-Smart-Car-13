#ifndef __AETHER_UART__
#define __AETHER_UART__



extern void UART4_Init(void);
extern void UpperCOM_PutBuff(uint8_t *buff, uint32_t len);
extern void UpperCOM_SendImg(uint8_t *ImgAddr,uint32_t size);

#endif