#include "include.h"

//初始化队列
void InitQueue(RingQueue *pQingQueue,unsigned char *buff,unsigned char length)
{
    pQingQueue->pHead=buff;
    pQingQueue->pTail=buff+length;

    pQingQueue->pStart=buff;
    pQingQueue->pEnd=buff+length-1;

    pQingQueue->length=length;
}
//后来的数据压入队列尾部，同时队首数据丢弃
void PushQueue(RingQueue *pQingQueue,unsigned char data)
{
    unsigned char *enext=pQingQueue->pEnd+1;
    if(enext>=pQingQueue->pTail)
    {
        enext-=pQingQueue->length;
    }
    pQingQueue->pEnd=enext;
    *pQingQueue->pEnd=data;//将数据送入队列尾部
    unsigned char *snext=pQingQueue->pStart+1;
    if(snext>=pQingQueue->pTail)
    {
      snext-=pQingQueue->length;
    }
    pQingQueue->pStart=snext;

}
void DataAnalysis(const RingQueue *pQingQueue,int *x,int *y)
{
   //符合数据协议
    if(*pQingQueue->pStart==0x03 && *pQingQueue->pEnd==0xfc)//true
    {
       unsigned char *p = pQingQueue->pStart +1;
       unsigned char *q = pQingQueue->pStart +2;
       if(p>=pQingQueue->pTail) p-=pQingQueue->length;
       if(q>=pQingQueue->pTail) q-=pQingQueue->length;
       *x=(*p<<8|*q);

       p = pQingQueue->pStart +3;
       q = pQingQueue->pStart +4;
       if(p>=pQingQueue->pTail) p-=pQingQueue->length;
       if(q>=pQingQueue->pTail) q-=pQingQueue->length;
       *y=(*p<<8|*q);
  
    }
}