#ifndef __AETHERDRIVER_RINGBUFF_H
#define __AETHERDRIVER_RINGBUFF_H


typedef struct 
{
    unsigned char *pHead;
    unsigned char *pTail;
    unsigned char *pWrite;//写进环形队列指针
    unsigned char *pRead;//读指针
    unsigned char length;
    unsigned char Overflow;
}RingBuff;

extern RingBuff UART_buff;

extern void InitalizeRingBuff(RingBuff* pRingBuff,unsigned char * buff,unsigned char length);
extern void BuffClear(RingBuff* pRingBuff);
extern void BuffPush(RingBuff* pRingBuff,unsigned char value);
extern unsigned char BuffPop(RingBuff* pRingBuff);
extern unsigned char BuffGetCount(const RingBuff * pRingBuff);
extern unsigned char BuffIsEmpty(const RingBuff * pRingBuff);
extern unsigned char BuffIsFull(const RingBuff * pRingBuff);
#endif