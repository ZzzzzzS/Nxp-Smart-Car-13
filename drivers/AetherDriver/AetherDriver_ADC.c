#include "include.h"


void ADC_Init()
{
    PORT_SetPinMux(PORTE, 20U, kPORT_PinDisabledOrAnalog);
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

    hsadcSampleConfigStruct.channelNumber =2U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 3U, &hsadcSampleConfigStruct);

    hsadcSampleConfigStruct.channelNumber =8U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 4U, &hsadcSampleConfigStruct);

	sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                 | HSADC_SAMPLE_MASK(1U)
                 | HSADC_SAMPLE_MASK(2U)  /* For converter A. */
                 | HSADC_SAMPLE_MASK(3U)
                 | HSADC_SAMPLE_MASK(4U);
     
    HSADC_EnableSample(HSADC0, sampleMask, true);
    HSADC_EnableSample(HSADC0, (uint16_t)(~sampleMask), false); /* Disable other sample slots. */
}


void GetADCVal(int16_t* vals)
{

    uint16_t temp[MAX_POSITION] = {0};
    uint16_t sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                        | HSADC_SAMPLE_MASK(1U)
                        | HSADC_SAMPLE_MASK(2U)  /* For converter A. */
                        | HSADC_SAMPLE_MASK(3U)
                        | HSADC_SAMPLE_MASK(4U);
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
        temp[0] += (HSADC_GetSampleResultValue(HSADC0, 0U)>>2);
        temp[1] += (HSADC_GetSampleResultValue(HSADC0, 1U)>>2);
        temp[2] += (HSADC_GetSampleResultValue(HSADC0, 2U)>>2);
        temp[3] += (HSADC_GetSampleResultValue(HSADC0, 3U)>>2);
        temp[4] += (HSADC_GetSampleResultValue(HSADC0, 4U)>>2);
		}
        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
    }
    
    for(int i=0;i<MAX_POSITION;i++) //完成归一化操作
    {
        temp[i] = temp[i] / 5;
        if(temp[i]<20)
          temp[i]=20;
        
        vals[i] = (float)((float)(temp[i] - ADside[i].min) / (float)(ADside[i].max - ADside[i].min))*1000;
    
    }

}


void GetADCValWithoutUniformization(int16_t* vals)
{
        uint16_t temp[MAX_POSITION] = {0};
	uint16_t sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                        | HSADC_SAMPLE_MASK(1U)
                        | HSADC_SAMPLE_MASK(2U)  /* For converter A. */
                        | HSADC_SAMPLE_MASK(3U)
                        | HSADC_SAMPLE_MASK(4U);
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
        temp[0] += (HSADC_GetSampleResultValue(HSADC0, 0U)>>2);
        temp[1] += (HSADC_GetSampleResultValue(HSADC0, 1U)>>2);
        temp[2] += (HSADC_GetSampleResultValue(HSADC0, 2U)>>2);
        temp[3] += (HSADC_GetSampleResultValue(HSADC0, 3U)>>2);
        temp[4] += (HSADC_GetSampleResultValue(HSADC0, 4U)>>2);
		}
        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
    }
    
    for(int i=0;i<MAX_POSITION;i++)
    {
        vals[i] = temp[i] / 5;
    }
}