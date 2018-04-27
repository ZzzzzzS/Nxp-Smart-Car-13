#ifndef __AETHERDRIVER_UART_DATAANALYSIS_H
#define __AETHERDRIVER_UART_DATAANALYSIS_H

typedef struct
{
    unsigned char *pHead;//用来存储buff的首地址
    unsigned char *pTail;//用来存储buff的尾部地址
    
    unsigned char *pStart;//数据队列首
    unsigned char *pEnd;//书队列尾部
    unsigned char length;

}RingQueue;


extern RingQueue Queue;
extern void InitQueue(RingQueue *pQingQueue,unsigned char *buff,unsigned char length);
extern void PushQueue(RingQueue *pQingQueue,unsigned char data);
extern void DataAnalysis(const RingQueue *pQingQueue,int *x,int *y);
#endif