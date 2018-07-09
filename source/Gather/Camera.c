#include "include.h"



void MT9V034_WriteReg(uint8_t SlaveAddr, uint8_t RegAddr, uint16_t RegVal)
{
    //SCCB_UnlockI2C();
    MT9V034_writereg_start:
    SCCB_Start();
    SCCB_WriteByte_soft(SlaveAddr, RegAddr, RegVal);
    SCCB_Stop();
    delay_ms(2);
    if((RegAddr !=  MT9V034_RESET) && (RegVal != MT9V034_ReadReg(SlaveAddr, RegAddr)))
    {
        goto MT9V034_writereg_start;
    }
    delay_ms(20);
    return;
}

uint16_t MT9V034_ReadReg(uint8_t SlaveAddr, uint8_t RegAddr)
{
    uint16_t val;
    val = SCCB_ReadByte_soft(SlaveAddr, RegAddr);
    SCCB_Stop();
    delay_ms(2);
    return val;
}

void MT9V034_Reset(uint8_t MT9V034_I2C_ADDR)
{
    //Reset MT9V034, but register config will not change.
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
    delay_ms(10);
    //Unlock MT9V034, allowing user to initiate register settings and readout
   //MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_CHIP_CONTROL, 0x0188);      
    //Reset Again.
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
    delay_ms(10);
}

void MT9V034_SetReservedReg(uint8_t MT9V034_I2C_ADDR)
{
  //Here we write some reserved registers as recommendations from Rev.G datasheet, Table.8
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x13, 0x2D2E);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x20, 0x03C7);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x24, 0x001B);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x2B, 0x0003);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x2F, 0x0003);
}

void MT9V034_SetAutoExposure(uint8_t MT9V034_I2C_ADDR, bool enable)
{ 
    uint16_t reg = MT9V034_ReadReg(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE);
    if(true == enable)
    {
        MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg|MT9V034_AEC_ENABLE);
    }
    else
    {
        MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg&~(MT9V034_AEC_ENABLE|MT9V034_AGC_ENABLE));
    }
}

void MT9V034_SetFrameResolution(uint8_t MT9V034_I2C_ADDR, uint16_t width, uint16_t height)
{
    uint16_t data = 0;
    if((width*4)<=MT9V034_MAX_WIDTH && (height*4)<=MT9V034_MAX_HEIGHT)
    {
        width *= 4;
        height *= 4;
        data |= MT9V034_READ_MODE_ROW_BIN_4;
        data |= MT9V034_READ_MODE_COL_BIN_4;
    }
    else if((width*2)<=MT9V034_MAX_WIDTH && (height*2)<=MT9V034_MAX_HEIGHT)
    {
        width *= 2;
        height *= 2;
        data |= MT9V034_READ_MODE_ROW_BIN_2;
        data |= MT9V034_READ_MODE_COL_BIN_2;
    }
    data |= (MT9V034_READ_MODE_ROW_FLIP);       //LQ-MT9V034 needs vertical mirror to capture correct image   
    data |= (MT9V034_READ_MODE_COL_FLIP);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_READ_MODE, data);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_WINDOW_WIDTH,  width);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_WINDOW_HEIGHT, height);  
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_COL_START, (MT9V034_MAX_WIDTH-width)/2+MT9V034_COL_START_MIN);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_ROW_START, (MT9V034_MAX_HEIGHT-height)/2+MT9V034_ROW_START_MIN);
}

bool MT9V034_Reg_Init(uint8_t MT9V034_I2C_ADDR)
{
     uint16_t id = MT9V034_ReadReg(MT9V034_I2C_ADDR, 0x00);
    if(MT9V034_DEFAULT_VERSION != id)
    {
        return false;
    }
    
    MT9V034_Reset(MT9V034_I2C_ADDR);
    
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x2C, 0x0000);
    id = MT9V034_ReadReg(MT9V034_I2C_ADDR, 0x2C);
    
    MT9V034_SetReservedReg(MT9V034_I2C_ADDR);
    MT9V034_SetFrameResolution(MT9V034_I2C_ADDR, MT9V034_W, MT9V034_H);
    
    MT9V034_SetAutoExposure(MT9V034_I2C_ADDR,true);
    
   MT9V034_WriteReg(MT9V034_I2C_ADDR, MT9V034_ANALOG_CTRL, MT9V034_ANTI_ECLIPSE_ENABLE);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0F, 0x0001);

    //100dB HDR:
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x08, 0x03D4);
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x09, 0x03E7);
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0A, 0x0064);
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0B, 0x03E8);
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0F, 0x0103);
    //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x35, 0x8010);
    
    //80dB HDR
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x08, 0x03CA);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x09, 0x03DE);
     MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0A, 0x0064);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0B, 0x03E8);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x0F, 0x0103);
    MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x35, 0x8010);

  //MT9V034_WriteReg(MT9V034_I2C_ADDR, 0x2C, 0x0001);
  //MT9V034_WriteReg(MT9V034_I2C_ADDR,MT9V034_COARSE_SHUTTER_WIDTH_TOTAL_A,0x00A0);
  //MT9V034_WriteReg(MT9V034_I2C_ADDR,MT9V034_TOTAL_SHUTTER_WIDTH,0x03A8);
  //MT9V034_WriteReg(MT9V034_I2C_ADDR,MT9V034_COARSE_SHUTTER_WIDTH_MIN,0x0010);
  //MT9V034_WriteReg(MT9V034_I2C_ADDR,MT9V034_COARSE_SHUTTER_WIDTH_MIN,0x0200);
  //MT9V034_WriteReg(MT9V034_I2C_ADDR,0xA5,0x0010);
    
   // MT9V034_WriteReg(MT9V034_I2C_ADDR,0x7F,0x0000);
    
    
    return true;
}

void MT9V034_Init(void)
{  
   SCCB_Init();
   
   /* Input pin PORT configuration */
    port_pin_config_t gpio_input = 
    {
        kPORT_PullDisable,                           // 内部输入上拉
        kPORT_SlowSlewRate,                     // 低速翻转模式
        kPORT_PassiveFilterEnable,              // 无源滤波开启(信号频率f>2Mhz时就应关闭)
        kPORT_OpenDrainDisable,                 // 推挽输出
        kPORT_LowDriveStrength,                 // 低驱动能力
        kPORT_MuxAsGpio,                        // 复用成GPIO(输入)
        kPORT_UnlockRegister,                   // 0 ~ kPORT_UnLockRegister, 1 ~ kPORT_LockRegister
    };
    PORT_SetPinConfig(PORTB,  0, &gpio_input);        // PTB0 ~ D7
    PORT_SetPinConfig(PORTB,  1, &gpio_input);        // PTB1 ~ D6
    PORT_SetPinConfig(PORTB,  2, &gpio_input);        // PTB2 ~ D5
    PORT_SetPinConfig(PORTB,  3, &gpio_input);        // PTB3 ~ D4
    PORT_SetPinConfig(PORTB,  4, &gpio_input);        // PTB4 ~ D3
    PORT_SetPinConfig(PORTB,  5, &gpio_input);        // PTB5 ~ D2
    PORT_SetPinConfig(PORTB,  6, &gpio_input);        // PTB6 ~ D4
    PORT_SetPinConfig(PORTB,  7, &gpio_input);        // PTB7 ~ D0
    
    gpio_input.pullSelect = kPORT_PullDown;
    
    PORT_SetPinConfig(PORTB, 18, &gpio_input);        // PTA24 ~ PCLK
    PORT_SetPinConfig(PORTB, 19, &gpio_input);        // PTA25 ~ VSYNC
    PORT_SetPinConfig(PORTB, 23, &gpio_input);        // PTA26 ~ HREF

   gpio_init(GPIOB,0U,IN,LOW);
   gpio_init(GPIOB,1U,IN,LOW);
   gpio_init(GPIOB,2U,IN,LOW);
   gpio_init(GPIOB,3U,IN,LOW);
   gpio_init(GPIOB,4U,IN,LOW);
   gpio_init(GPIOB,5U,IN,LOW);
   gpio_init(GPIOB,6U,IN,LOW);
   gpio_init(GPIOB,7U,IN,LOW);
   gpio_init(GPIOB,18U,IN,LOW);
   gpio_init(GPIOB,19U,IN,LOW);
   gpio_init(GPIOB,23U,IN,LOW);
   
   
   edma_config_t DMA_config;
   DMA_config.enableContinuousLinkMode = false;
   DMA_config.enableDebugMode = false;
   DMA_config.enableHaltOnError = false;
   DMA_config.enableRoundRobinArbitration = false;
   EDMA_Init(DMA0, &DMA_config);
   
   DMAMUX_Init(DMAMUX);
   
   MT9V034_Reg_Init(MT9V034_SLAVE_ADDRESS);
   MT9V034_DMA_Init(MT9V034_IMGBUFF_A);
}


void MT9V034_DMA_Init(uint8_t* pMT9V032_IMG_Buff)
{
    edma_transfer_config_t DMA0_Transer_config;

    DMA0_Transer_config.srcAddr          = (uint32_t)&(GPIOB->PDIR);            // 数据源来自PORTB0
    DMA0_Transer_config.srcOffset        = 0x00U;                               // 数据源PORTB偏移量=0
    DMA0_Transer_config.destAddr         = (uint32_t)pMT9V032_IMG_Buff;         // pMT9V032_IMG_Buff
    DMA0_Transer_config.destOffset       = 0x01U;                               // 数据源指向地址每次自增1 byte
    DMA0_Transer_config.destTransferSize = kEDMA_TransferSize1Bytes;            // DMA每次传输1byte
    DMA0_Transer_config.srcTransferSize  = kEDMA_TransferSize1Bytes;            // DMA每次传输1byte
    DMA0_Transer_config.majorLoopCounts  = MT9V034_W;                      // VSYNC触发DMA一次Major loop采集CAMERA_DMA_NUM (bytes)的数据
    DMA0_Transer_config.minorLoopBytes   = 0x01U;
    
    EDMA_ResetChannel(DMA0, MT9V034_DMA_CHANNEL);                                         // 复位DMACH0
    EDMA_SetTransferConfig(DMA0, MT9V034_DMA_CHANNEL, &DMA0_Transer_config, NULL);        // nexTCD / NULL
    
    EDMA_SetBandWidth(DMA0, MT9V034_DMA_CHANNEL, kEDMA_BandwidthStallNone);             // DMA0->CSR, 每读取一次DMA引擎stall 0个周期
    EDMA_EnableAutoStopRequest(DMA0, MT9V034_DMA_CHANNEL, true);                          // DMA0->CSR  主循环结束后自动停止硬件请求
    EDMA_EnableChannelInterrupts(DMA0, MT9V034_DMA_CHANNEL, kEDMA_MajorInterruptEnable);  // DMA0->CSR  主循环结束后产生中断
    
    DMAMUX_SetSource(DMAMUX, MT9V034_DMA_CHANNEL, 50);         // 设置DMACH0触发源为PORTB {DMAMUX->CHCFG[0] = src(50)}
    DMAMUX_EnableChannel(DMAMUX, MT9V034_DMA_CHANNEL);         // 使能DMACH0传输
    
    DisableIRQ(MT9V034_DMA_CHANNEL);
    DisableIRQ(PORTB_IRQn);                  // Disable Interrupts according to PORTB
    
    EDMA_ClearChannelStatusFlags(DMA0, MT9V034_DMA_CHANNEL, kEDMA_InterruptFlag);
    
    PORT_SetPinInterruptConfig(PORTB, 18U, kPORT_DMARisingEdge);          // PTB18 ~ PCLK.  信号下降沿触发DMA传输
    PORT_SetPinInterruptConfig(PORTB, 23U, kPORT_InterruptRisingEdge);     // PTAB23 ~ VSYNC. 信号上升沿触发CPU中断
    PORT_SetPinInterruptConfig(PORTB, 19U, kPORT_InterruptRisingEdge);     // PTB19 ~ HREF.  信号上升沿触发CPU中断
    
    //PORTB->PCR[18U] = (PORTB->PCR[18U] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptOrDMADisabled);
    EnableIRQ(MT9V034_DMA_CHANNEL);
    EnableIRQ(PORTB_IRQn);
}

__ramfunc void PORTB_IRQHandler(void)
{
  MT9V034_FrameValid_Callback(PORTB->ISFR);
}

__ramfunc void DMA0_DMA16_IRQHandler(void)
{
  MT9V034_DMA_Callback();
}

__ramfunc void MT9V034_FrameValid_Callback(uint32_t ISFR_FLAG)
{
    static uint16_t line = 0;
    

    if(ISFR_FLAG&(1U<<23U))
    {
        PORTB->ISFR |= (1U<<23U);        
        MT9V034_CaptureAccomplished = false;
        return;
    }
   
    if(ISFR_FLAG&(1U<<19U)&&!MT9V034_CaptureAccomplished)
    {
        //PORTB->PCR[18U] = (PORTB->PCR[18U] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_DMAFallingEdge);
        
        PORTB->ISFR |= (1U<<19U);
        MT9V034_LineValid_Callback(line++,IMG_NOW);
        if(line == MT9V034_H-1)
        {
            line = 0;
            if(Using_Flag==Using_A)
              IMG_NOW = (uint8_t*)MT9V034_IMGBUFF_B;
            else if(Using_Flag==Using_B)
              IMG_NOW = (uint8_t*)MT9V034_IMGBUFF_A;
            MT9V034_CaptureAccomplished = true;
        }
    }
}

__ramfunc void MT9V034_LineValid_Callback(uint16_t line,uint8_t* IMG)
{
    DMA0->TCD[0].DADDR = (uint32_t)&IMG[line*MT9V034_W];
    DMA0->SERQ = DMA_SERQ_SERQ(MT9V034_DMA_CHANNEL);
}

__ramfunc void MT9V034_DMA_Callback(void)
{
    DMA0->INT |= DMA_INT_INT0(1);
}
void Camera_ajust()
{
  static uint8_t row=0;
  static uint8_t col=0;

  if(READ_LEFT)
  {  
    delay_ms(20);
    if(READ_LEFT)
        row+=1;
    
    if(row>93)
      row=0;
  }
  if(READ_RIGHT)
  {
    delay_ms(20);
    if(READ_RIGHT)
        col+=1;
    if(col>59)
     col=0;
  }
  for(int i=0;i<60;i++)
    PutPixel(row,i,RED);
  for(int i=0;i<94;i++)
    PutPixel(i,col,RED);
  fullfill(0,80,90,127,YELLOW);
  Display_Number(0,5,row,YELLOW,RED);
  Display_Number(0,6,col,YELLOW,RED);
}
