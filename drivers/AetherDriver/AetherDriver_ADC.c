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
    //Init HSADC0
    HSADC_Init(HSADC0, &hsadcConfigStruct);
	//Init HSADC1
    HSADC_Init(HSADC1, &hsadcConfigStruct);

    HSADC_GetDefaultConverterConfig(&hsadcConverterConfigStruct);
    hsadcConverterConfigStruct.powerUpCalibrationModeMask =
        (kHSADC_CalibrationModeSingleEnded | kHSADC_CalibrationModeDifferential);

    HSADC_SetConverterConfig(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, &hsadcConverterConfigStruct);
    HSADC_SetConverterConfig(HSADC1, kHSADC_ConverterA | kHSADC_ConverterB, &hsadcConverterConfigStruct);
    /* Enable the power for each converter. */
    HSADC_EnableConverterPower(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, true);
    HSADC_EnableConverterPower(HSADC1, kHSADC_ConverterA | kHSADC_ConverterB, true);
    while (
        (kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) ==
        ((kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) & HSADC_GetStatusFlags(HSADC0)))
    {
    }

    while (
        (kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) ==
        ((kHSADC_ConverterAPowerDownFlag | kHSADC_ConverterBPowerDownFlag) & HSADC_GetStatusFlags(HSADC1)))
    {
    }

	while ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) !=
           ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) &
            HSADC_GetStatusFlags(HSADC0)))
    {
    }

    while ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) !=
           ((kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag) &
            HSADC_GetStatusFlags(HSADC1)))
    {
    }

    HSADC_ClearStatusFlags(HSADC0,
                           (kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag));
    HSADC_EnableConverter(HSADC0, kHSADC_ConverterA | kHSADC_ConverterB, true);

    HSADC_ClearStatusFlags(HSADC1,
                           (kHSADC_ConverterAEndOfCalibrationFlag | kHSADC_ConverterBEndOfCalibrationFlag));
    HSADC_EnableConverter(HSADC1, kHSADC_ConverterA | kHSADC_ConverterB, true);

    HSADC_GetDefaultSampleConfig(&hsadcSampleConfigStruct);
    //hsadcSampleConfigStruct.highLimitValue=0x0000;
	
    //HSADC1B CH2
	hsadcSampleConfigStruct.channelNumber =10U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC1, 8U, &hsadcSampleConfigStruct);

    //HSADC0A CH11
    hsadcSampleConfigStruct.channelNumber =7U;
    hsadcSampleConfigStruct.channel67MuxNumber =2U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 1U, &hsadcSampleConfigStruct);

    //HSADC0A CH3
    hsadcSampleConfigStruct.channelNumber =3U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 2U, &hsadcSampleConfigStruct);

    //HSADC0A CH2
    hsadcSampleConfigStruct.channelNumber =2U;
    hsadcSampleConfigStruct.channel67MuxNumber =0U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 3U, &hsadcSampleConfigStruct);

    //HSADC0A CH8
    hsadcSampleConfigStruct.channelNumber =6U;
    hsadcSampleConfigStruct.channel67MuxNumber =1U;
    hsadcSampleConfigStruct.enableDifferentialPair =false;
    HSADC_SetSampleConfig(HSADC0, 0U, &hsadcSampleConfigStruct);

	sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                 | HSADC_SAMPLE_MASK(1U)
                 | HSADC_SAMPLE_MASK(2U)  /* For converter A. */
                 | HSADC_SAMPLE_MASK(3U);
     
    HSADC_EnableSample(HSADC0, sampleMask, true);
    HSADC_EnableSample(HSADC0, (uint16_t)(~sampleMask), false); /* Disable other sample slots. */

    sampleMask = HSADC_SAMPLE_MASK(8);
    HSADC_EnableSample(HSADC1, sampleMask, true);
    HSADC_EnableSample(HSADC1, (uint16_t)(~sampleMask), false); /* Disable other sample slots. */
    
}


void GetADCVal(int16_t* vals)
{

    uint16_t temp[MAX_POSITION] = {0};
    uint16_t sampleMask = HSADC_SAMPLE_MASK(0U)    /* For converter A. */
                        | HSADC_SAMPLE_MASK(1U)
                        | HSADC_SAMPLE_MASK(2U)  /* For converter A. */
                        | HSADC_SAMPLE_MASK(3U);
    uint16_t sampleMask1 = HSADC_SAMPLE_MASK(8);
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
        HSADC_DoSoftwareTriggerConverter(HSADC1, kHSADC_ConverterB);
        while (kHSADC_ConverterAEndOfScanFlag !=
               (kHSADC_ConverterAEndOfScanFlag & HSADC_GetStatusFlags(HSADC0)))
        {
        }
        while (kHSADC_ConverterBEndOfScanFlag !=
               (kHSADC_ConverterBEndOfScanFlag & HSADC_GetStatusFlags(HSADC1)))
        {
        }

        if (sampleMask == (sampleMask & HSADC_GetSampleReadyStatusFlags(HSADC0))){
        temp[0] += (HSADC_GetSampleResultValue(HSADC0, 0U)>>2);
        temp[1] += (HSADC_GetSampleResultValue(HSADC0, 1U)>>2);
        temp[2] += (HSADC_GetSampleResultValue(HSADC0, 2U)>>2);
        temp[3] += (HSADC_GetSampleResultValue(HSADC0, 3U)>>2);
		}
        if (sampleMask1 == (sampleMask1 & HSADC_GetSampleReadyStatusFlags(HSADC1))){
        temp[4] += (HSADC_GetSampleResultValue(HSADC1, 8U)>>2);
		}

        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
        HSADC_ClearStatusFlags(HSADC1, kHSADC_ConverterBEndOfScanFlag);

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
                        | HSADC_SAMPLE_MASK(3U);
    uint16_t sampleMask1 = HSADC_SAMPLE_MASK(8);
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
        HSADC_DoSoftwareTriggerConverter(HSADC1, kHSADC_ConverterB);
        while (kHSADC_ConverterAEndOfScanFlag !=
               (kHSADC_ConverterAEndOfScanFlag & HSADC_GetStatusFlags(HSADC0)))
        {
        }
        while (kHSADC_ConverterBEndOfScanFlag !=
               (kHSADC_ConverterBEndOfScanFlag & HSADC_GetStatusFlags(HSADC1)))
        {
        }

        if (sampleMask == (sampleMask & HSADC_GetSampleReadyStatusFlags(HSADC0))){
        temp[0] += (HSADC_GetSampleResultValue(HSADC0, 0U)>>2);
        temp[1] += (HSADC_GetSampleResultValue(HSADC0, 1U)>>2);
        temp[2] += (HSADC_GetSampleResultValue(HSADC0, 2U)>>2);
        temp[3] += (HSADC_GetSampleResultValue(HSADC0, 3U)>>2);
		}
        if (sampleMask1 == (sampleMask1 & HSADC_GetSampleReadyStatusFlags(HSADC1))){
        temp[4] += (HSADC_GetSampleResultValue(HSADC1, 8U)>>2);
		}

        HSADC_ClearStatusFlags(HSADC0, kHSADC_ConverterAEndOfScanFlag);
        HSADC_ClearStatusFlags(HSADC1, kHSADC_ConverterBEndOfScanFlag);

    }
    
    for(int i=0;i<MAX_POSITION;i++)
    {
        vals[i] = temp[i] / 5;
    }
}