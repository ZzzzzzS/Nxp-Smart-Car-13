#include "include.h"

uint16_t g_Speed = 2000;

void Speed_Init()
{
    PORT_SetPinMux(LEFT_PORT_BASE,LEFT_A_PIN,kPORT_MuxAlt7);
    PORT_SetPinMux(LEFT_PORT_BASE,LEFT_B_PIN,kPORT_MuxAlt7);
    PORT_SetPinMux(RIGHT_PORT_BASE,RIGHT_A_PIN,kPORT_MuxAlt6);
    PORT_SetPinMux(RIGHT_PORT_BASE,RIGHT_B_PIN,kPORT_MuxAlt6);

    ftm_phase_params_t PhAParams, PhBParams;
    
    // FTM_GetDefaultConfig(&FTM1Info);
    
    PhAParams.enablePhaseFilter = false;
    PhAParams.phaseFilterVal = 0x00U;                      // Filter Val应小于0x0F
    PhAParams.phasePolarity = kFTM_QuadPhaseNormal;
    
    PhBParams.enablePhaseFilter = false;
    PhBParams.phaseFilterVal = 0x00U;                      // Filter Val应小于0x0F
    PhBParams.phasePolarity = kFTM_QuadPhaseNormal;
    
    // FTM_Init(FTM2, &FTM2Info);
    CLOCK_EnableClock(kCLOCK_Ftm2);
    FTM_SetupQuadDecode(FTM2, &PhAParams, &PhBParams, kFTM_QuadCountAndDir);
    FTM_ClearQuadDecoderCounterValue(FTM2);
    
    CLOCK_EnableClock(kCLOCK_Ftm1);
    FTM_SetupQuadDecode(FTM1, &PhAParams, &PhBParams, kFTM_QuadCountAndDir);
    FTM_ClearQuadDecoderCounterValue(FTM1);

    
}

