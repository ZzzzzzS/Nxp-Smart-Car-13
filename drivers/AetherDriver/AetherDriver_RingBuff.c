#include "include.h"
/**
  * @brief  InitalizeRingBuff，将缓冲区信息填入结构体
  * @param  pRingBuff:ringbuffer结构体
	*         buff：数据缓冲区
	*         length：缓冲区大小
 * */
void InitalizeRingBuff(RingBuff* pRingBuff,unsigned char * buff,unsigned char length)
{
    pRingBuff->pHead=buff;
    pRingBuff->pTail=buff+length;
    pRingBuff->pWrite=buff;
    pRingBuff->pRead=buff;
    pRingBuff->length=length;
    pRingBuff->Overflow=0;
}

/**
  * @brief  清除ringbuffer结构体的相关信息
  * @param  pRingBuff：待处理的ringbuffer
  * @note   
  * @retval void
  * @author xiaodaqi
 * */
void BuffClear(RingBuff* pRingBuff)
{
    pRingBuff->pWrite=pRingBuff->pHead;
    pRingBuff->pRead=pRingBuff->pTail;
    pRingBuff->Overflow=0;
}

void BuffPush(RingBuff* pRingBuff,unsigned char value)
{
     unsigned char *pWriteNext=pRingBuff->pWrite+1;
     if(pWriteNext==pRingBuff->pTail)
     {
         pWriteNext-=pRingBuff->length;
     }
     if(pWriteNext==pRingBuff->pRead)
     {
        pRingBuff->Overflow=1;//溢出了
     } 
     else
     {
         *pRingBuff->pWrite=value;//将值写入buff
         pRingBuff->pWrite=pWriteNext;//移动指针到下一个字节
     }  
}
unsigned char BuffPop(RingBuff* pRingBuff)
{
    if(pRingBuff->pRead==pRingBuff->pWrite) return 0;//empty
    unsigned char value=*(pRingBuff->pRead);
    pRingBuff->pRead++;
    if(pRingBuff->pRead==pRingBuff->pTail)
    {
        pRingBuff->pRead-=pRingBuff->length;
    }
    return value;
}
//获取缓冲区未处理的数据
unsigned char BuffGetCount(const RingBuff * pRingBuff)
{
  return (pRingBuff->pWrite -pRingBuff->pRead +pRingBuff->length)%pRingBuff->length;
}
//缓冲区是否为空 空返回1
unsigned char BuffIsEmpty(const RingBuff * pRingBuff)
{
    return (pRingBuff->pWrite==pRingBuff->pRead);
}
//判断缓冲区是否满
//满为1
unsigned char BuffIsFull(const RingBuff * pRingBuff)
{
    return ((pRingBuff->pRead-pRingBuff->pWrite + pRingBuff->length -1)%pRingBuff->length==0);
}

