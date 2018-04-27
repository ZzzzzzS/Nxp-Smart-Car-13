#include "include.h"

typedef union
{
  float pidvalue;
  int16_t   speedvalue;
  char value_byte[2];
}value;

value data_buffer;

unsigned char ucRxBuffer[360];


unsigned char ucRxCnt = 0;	

unsigned char ucRingBuffer[200];
RingBuff UART_buff;


//WARN
unsigned char buffQueue[7];
RingQueue Queue;


void GetDataFromController2(unsigned char ucData)
{
	//char i;
	unsigned char cmd;
//	static unsigned char ucRxBuffer[60];
//	static unsigned char ucRxCnt = 0;	

	//unsigned char sum=0;
		
	ucRxBuffer[ucRxCnt++]=ucData;
	//UART4_Put_Char(ucData);
	//UART4_Put_String("yes1");
	
	if(ucRxBuffer[0]!=0xaa)
	{
		ucRxCnt=0;
	//	e=99;
		return;
	}
	if(ucRxCnt<2) return;
        
        if(ucRxBuffer[1]!=0xbb) 
	{
		ucRxCnt=0;
	//	d=2;
		return;
	}
        
	if(ucRxCnt<3) return;
	cmd =ucRxBuffer[2];
	
	switch (cmd)
	{
        case 0x10:
         if(ucRxCnt<16) 
          {
            //d=3;
            return;
          }
          else
          {

              data_buffer.value_byte[0]=ucRxBuffer[4]; //1p
              data_buffer.value_byte[1]=ucRxBuffer[5];
              PID_Motor.PidCore.Kp=data_buffer.pidvalue;
              
              data_buffer.value_byte[0]=ucRxBuffer[6];  //1i
              data_buffer.value_byte[1]=ucRxBuffer[7];
              PID_Motor.PidCore.Ki=data_buffer.pidvalue;

              data_buffer.value_byte[0]=ucRxBuffer[8];  //1i
              data_buffer.value_byte[1]=ucRxBuffer[9];
              PID_Motor.PidCore.Kd=data_buffer.pidvalue; 
           
              ucRxCnt=0;
              
            }	
            break;
          
          
        case 0x03:
          if(ucRxCnt<23) 
          {
//            d=5;
            return;
          }
          else
          {
           
              
              ucRxCnt=0;
            }	
            break;
        default:ucRxCnt=0;return;
	}

}

void UART4_Init(void)
{
    PORT_SetPinMux(PORTE, 24U, kPORT_MuxAlt8); // PTE24 ~ UART4_TX
    PORT_SetPinMux(PORTE, 25U, kPORT_MuxAlt8);   // PTE25 ~ UART4_RX

    uart_config_t UART4_config;
    
    UART4_config.baudRate_Bps = 115200U;                          // 波特率：9600
    UART4_config.parityMode = kUART_ParityDisabled;             // 校验位：None
    UART4_config.stopBitCount = kUART_OneStopBit;               // 停止位：1
    UART4_config.txFifoWatermark = 0;                           // tx缓冲：0
    UART4_config.rxFifoWatermark = 1;                           // rx缓冲：1
    UART4_config.enableRx = true;
    UART4_config.enableTx = true;
    
    UART_Init(UART4, &UART4_config,CLOCK_GetFreq(kCLOCK_FastPeriphClk));
    
    
    (UART4->C2) &= ~UART_C2_TIE_MASK; //关闭串口发送中断
    (UART4->C2) &= ~UART_C2_TCIE_MASK;//关闭发送完成中断
    (UART4->C2) |= UART_C2_RIE_MASK;//开接收中断
    
    (UART4->C3) &=~UART_C3_ORIE_MASK;//关闭overrun中断
    (UART4->C3) &=~UART_C3_NEIE_MASK;//关闭nosie error中断
    (UART4->C3) &=~UART_C3_FEIE_MASK;//关闭framing error 中断
    (UART4->C3) &=~UART_C3_PEIE_MASK;//关闭奇偶检验错误中断

    EnableIRQ(UART4_RX_TX_IRQn);
    //环形队列缓冲区和数据分析队列的初始化
    InitalizeRingBuff(&UART_buff,ucRingBuffer,sizeof(ucRingBuffer)/sizeof(unsigned char));
    InitQueue(&Queue,buffQueue,(sizeof(buffQueue)/sizeof(unsigned char))-1);
}

void UpperCOM_PutBuff(uint8_t *buff, uint32_t len)
{
    UART_WriteBlocking(UART4,buff,len);
}

void UpperCOM_SendImg(uint8_t *ImgAddr,uint32_t size)
{
    uint8_t HEAD[2] = { 0x01, 0xFE };
    uint8_t TAIL[2] = { 0xFE, 0x01 };

    UpperCOM_PutBuff(HEAD, sizeof(HEAD));          //先发送命令
    UART_WriteBlocking(UART4,ImgAddr,size);       //发送数据
    
    UpperCOM_PutBuff(TAIL, sizeof(TAIL));          //再发送命令
}

void UART4_RX_TX_IRQHandler(void)
{
    //硬件自动清楚标志位
  unsigned char ch;
  //进中断读取一个字节，每来一个字节就会有一个中断
  UART_ReadBlocking(UART4,&ch, 1);
  //将读取的数据放入缓冲区等待处理
  BuffPush(&UART_buff,ch);
 
}
