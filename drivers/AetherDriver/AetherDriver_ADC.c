#include "include.h"


//void ADC_Init()
//{
//	
//
//    hsadc_config_t HSADC0_config;
//    hsadc_converter_config_t  HSADC0_Converter_config;
//    
//    HSADC_GetDefaultConfig(&HSADC0_config);
//    // HSADC1_config.dualConverterScanMode = kHSADC_DualConverterWorkAsTriggeredSequential;             // HSADC工作在单序列采集模式(非并发)
//    HSADC0_config.enableSimultaneousMode = false;                                              // 关闭并行采集模式
//    // HSADC1_config.idleWorkMode = kHSADC_IdleKeepNormal;                                         // 空闲时不挂起，保持正常工作状态
//    // HSADC1_config.resolution = kHSADC_Resolution12Bit;                                          // 转换精度12bit
//    
//    HSADC0_Converter_config.clockDivisor = 5U;                                                  // 输入时钟(System Clock)分频系数=5，HSADC输入时钟应小于80Mhz
//    HSADC0_Converter_config.samplingTimeCount = 0U;
//    HSADC0_Converter_config.powerUpCalibrationModeMask = kHSADC_CalibrationModeSingleEnded;     // 自校准时采用单端转换模式
//    
//    HSADC_Init(HSADC0, &HSADC0_config);
//    HSADC_SetConverterConfig(HSADC0, kHSADC_ConverterA|kHSADC_ConverterB, &HSADC0_Converter_config);
//
//    HSADC_EnableConverterPower (HSADC0, kHSADC_ConverterA|kHSADC_ConverterB, true);              // 打开HSADC模块电源
//    HSADC_EnableConverter (HSADC0, kHSADC_ConverterA|kHSADC_ConverterB, true);                   // 使能HSADC(打开时钟门控)
//    // HSADC_EnableConverterSyncInput(HSADC1, kHSADC_ConverterB, false);          // 禁用外同步触发HSADC转化
//    
//    hsadc_sample_config_t HSADC0_Left;                              // PTC8 ~ HSADC1B_11
//    hsadc_sample_config_t HSADC0_Right;                             // PTC9 ~ HSADC1B_12
//    
//    HSADC0_Left.enableDifferentialPair = false;                    // 禁用差分对输入，使用单端采集模式
//    HSADC0_Left.channelNumber = 6U;                            // 由HSADC内部结构：
//	HSADC0_Left.channel67MuxNumber = 2;
//    HSADC0_Left.zeroCrossingMode = kHSADC_ZeroCorssingDisabled;
//    HSADC0_Left.enableWaitSync = false;
//    
//    HSADC0_Right.enableDifferentialPair = false;                    // 禁用差分对输入，使用单端采集模式
//    HSADC0_Right.channelNumber = 7U;                            // 由HSADC内部结构：
//	HSADC0_Right.channel67MuxNumber = 2;
//    HSADC0_Right.zeroCrossingMode = kHSADC_ZeroCorssingDisabled;
//    HSADC0_Right.enableWaitSync = false;
//    
//    HSADC_SetSampleConfig(HSADC0, 0U, &HSADC0_Left);                // 放置HSADC1_B_Ch11信号在slot 8中.(slot 0~7仅限HSADCx_A通道的0~7连接， slot 8~15仅限HSADCx_B的通道0~7连接)
//    HSADC_SetSampleConfig(HSADC0, 1U, &HSADC0_Right);               // 放置HSADC1_B_Ch12信号在slot 9中.(slot 0~7仅限HSADCx_A通道的0~7连接， slot 8~15仅限HSADCx_B的通道0~7连接)
//    
//    HSADC_EnableSample(HSADC0, HSADC_SAMPLE_MASK(0U)|HSADC_SAMPLE_MASK(1U), true);                      // 注册slot8(PTC8~ch11)和slot9(PTC9~ch12)
//    HSADC_EnableSample(HSADC0, (uint16_t)(~(HSADC_SAMPLE_MASK(0U)|HSADC_SAMPLE_MASK(1U))), false);      // 关闭其他的slots
//    
//    HSADC_DoAutoCalibration(HSADC0, kHSADC_ConverterA, kHSADC_CalibrationModeSingleEnded);
//    // while ((kHSADC_ConverterBEndOfScanFlag|kHSADC_ConverterBEndOfCalibrationFlag) != ((kHSADC_ConverterBEndOfScanFlag|kHSADC_ConverterBEndOfCalibrationFlag)&HSADC_GetStatusFlags(HSADC1)));
//    while (kHSADC_ConverterAEndOfCalibrationFlag!=kHSADC_ConverterAEndOfCalibrationFlag & HSADC_GetStatusFlags(HSADC0));
//    
//    // HSADC_ClearStatusFlags(HSADC1, kHSADC_ConverterAEndOfScanFlag|kHSADC_ConverterAEndOfCalibrationFlag|kHSADC_ConverterBEndOfScanFlag|kHSADC_ConverterBEndOfCalibrationFlag);
//    HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfCalibrationFlag);
//    
//    //-------------------------------------------------------------------------//
//}

void ADC_Init()
{
	
    hsadc_config_t hsadcConfigStruct;
    hsadc_converter_config_t hsadcConverterConfigStruct;
    hsadc_sample_config_t hsadcSampleConfigStruct;
	uint16_t sampleMask;

    HSADC_GetDefaultConfig(&hsadcConfigStruct);
	hsadcConfigStruct.enableSimultaneousMode = false;
    HSADC_Init(HSADC0, &hsadcConfigStruct);
	
    HSADC_GetDefaultConverterConfig(&hsadcConverterConfigStruct);
    hsadcConverterConfigStruct.powerUpCalibrationModeMask =
        (kHSADC_CalibrationModeSingleEnded | kHSADC_CalibrationModeDifferential);
    HSADC_SetConverterConfig(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, &hsadcConverterConfigStruct);
    /* Enable the power for each converter. */
    HSADC_EnableConverterPower(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, true);
    while (
        (kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) ==
        ((kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) & HSADC_GetStatusFlags(HSADC0)))
    {
    }
	while ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) !=
           ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) &
            HSADC_GetStatusFlags(HSADC0)))
    {
    }

    HSADC_ClearStatusFlags(HSADC0,
                           (kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag));
    HSADC_EnableConverter(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, true);


    HSADC_GetDefaultSampleConfig(&hsadcSampleConfigStruct);
    //hsadcSampleConfigStruct.highLimitValue=0x0000;
	
	hsadcSampleConfigStruct.channelNumber =6U;
    hsadcSampleConfigStruct.channel67MuxNumber =2U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 0U, &hsadcSampleConfigStruct);

    hsadcSampleConfigStruct.channelNumber =7U;
    hsadcSampleConfigStruct.channel67MuxNumber =2U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 1U, &hsadcSampleConfigStruct);

    hsadcSampleConfigStruct.channelNumber =3U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 2U, &hsadcSampleConfigStruct);

	sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                 | HSADC_SAMPLE_MASK(1U)
                 |HSADC_SAMPLE_MASK(2U);  /* For converter A. */
     
    HSADC_EnableSample(HSADC0, sampleMask, true);
    HSADC_EnableSample(HSADC0, (uint16_t)(~sampleMask), false); /* Disable other sample slots. */
}


void GetADCVal(int16_t* vals)
{

    int16_t temp[MAX_POSITION] = {0};
    uint16_t sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                        | HSADC_SAMPLE_MASK(1U)
                        | HSADC_SAMPLE_MASK(2U);  /* For converter A. */
    // static adc16_channel_config_t ADC1_SExb_config;
    // ADC1_SExb_config.channelNumber = MOTORn;                                  // 4 ~ ADC1 SE4a(b), 4 ~ ADC1 SE5a(b)
    // ADC1_SExb_config.enableDifferentialConversion = false;                    // 不使能差分转换模式
    // ADC1_SExb_config.enableInterruptOnConversionCompleted = false;            // 转换完成不触发中断
    // 
    // ADC16_SetChannelConfig(ADC1, 0, &ADC1_SExb_config);                        // 软件触发采集
    // while(kADC16_ChannelConversionDoneFlag != ADC16_GetChannelStatusFlags(ADC1, 0));      
    // return ADC16_GetChannelConversionValue(ADC1, 0);               // 获取上行触发的采集结果
    for(int i = 0; i < 5; i++)
    {
        HSADC_DoSoftwareTriggerConverter(HSADC0, kHSADC_ConverterA);
        while (kHSADC_ConverterAEndOfScanFlag !=
               (kHSADC_ConverterAEndOfScanFlag & HSADC_GetStatusFlags(HSADC0)))
        {
        }

        if (sampleMask == (sampleMask & HSADC_GetSampleReadyStatusFlags(HSADC0))){
        temp[0] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 0U)>>2;
        temp[1] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 1U)>>2;
        temp[2] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 2U)>>2;
		}
        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
    }
    
    for(int i=0;i<MAX_POSITION;i++) //完成归一化操作
    {
        temp[i] = temp[i] / 5;
        vals[i] = (float)((float)(temp[i] - ADside[i].min) / (float)(ADside[i].max - ADside[i].min))*1000;
    }

}


void GetADCValWithoutUniformization(int16_t* vals)
{
        int16_t temp[MAX_POSITION] = {0};
	uint16_t sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                        | HSADC_SAMPLE_MASK(1U)
                        |HSADC_SAMPLE_MASK(2U);  /* For converter A. */
    // static adc16_channel_config_t ADC1_SExb_config;
    // ADC1_SExb_config.channelNumber = MOTORn;                                  // 4 ~ ADC1 SE4a(b), 4 ~ ADC1 SE5a(b)
    // ADC1_SExb_config.enableDifferentialConversion = false;                    // 不使能差分转换模式
    // ADC1_SExb_config.enableInterruptOnConversionCompleted = false;            // 转换完成不触发中断
    // 
    // ADC16_SetChannelConfig(ADC1, 0, &ADC1_SExb_config);                        // 软件触发采集
    // while(kADC16_ChannelConversionDoneFlag != ADC16_GetChannelStatusFlags(ADC1, 0));      
    // return ADC16_GetChannelConversionValue(ADC1, 0);               // 获取上行触发的采集结果
    for(int i = 0; i < 5; i++)
    {
        HSADC_DoSoftwareTriggerConverter(HSADC0, kHSADC_ConverterA);
        while (kHSADC_ConverterAEndOfScanFlag !=
               (kHSADC_ConverterAEndOfScanFlag & HSADC_GetStatusFlags(HSADC0)))
        {
        }

        if (sampleMask == (sampleMask & HSADC_GetSampleReadyStatusFlags(HSADC0))){
        temp[0] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 0U)>>2;
        temp[1] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 1U)>>2;
        temp[2] += (int16_t)HSADC_GetSampleResultValue(HSADC0, 2U)>>2;
		}
        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
    }
    
    for(int i=0;i<MAX_POSITION;i++)
    {
        vals[i] = temp[i] / 5;
    }
}