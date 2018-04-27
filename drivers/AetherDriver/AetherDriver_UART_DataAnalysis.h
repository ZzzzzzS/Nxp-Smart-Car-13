#ifndef __AETHERDRIVER_UART_DATAANALYSIS_H
#define __AETHERDRIVER_UART_DATAANALYSIS_H

typedef struct
{
    unsigned char *pHead;//�����洢buff���׵�ַ
    unsigned char *pTail;//�����洢buff��β����ַ
    
    unsigned char *pStart;//���ݶ�����
    unsigned char *pEnd;//�����β��
    unsigned char length;

}RingQueue;


extern RingQueue Queue;
extern void InitQueue(RingQueue *pQingQueue,unsigned char *buff,unsigned char length);
extern void PushQueue(RingQueue *pQingQueue,unsigned char data);
extern void DataAnalysis(const RingQueue *pQingQueue,int *x,int *y);
#endif