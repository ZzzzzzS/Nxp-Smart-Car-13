#include "include.h"

void Init()
{
    status_t result;
    uint32_t record;
    BOARD_InitBootClocks();
    CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */
    lcd_initial();//初始化LCD
    fullfill(0,0,128,128,BLACK);
    UART4_Init();               //初始化UART4(蓝牙)
    SteerInit();
    Button_Init();
    FiveKey_Init();
    Beep_Init();
    RGB_Init();
    MotorInit();
    Speed_Init();
    PIT0_Init(20);
    //PIT1_Init(20);
    PIDInit(&GV_speedControlT.Pid[0],0.8,0,0);
    PIDInit(&GV_speedControlT.Pid[1],0.8,0,0);
    GV_speedControlT.Pid[0].AimSpeed = 50;
    GV_speedControlT.Pid[1].AimSpeed = 50;
    //iic_init();   
    //MPU6050_Inital();
    result = Flash_init();
    
    MT9V034_Init();             //初始化摄像头
    
    NVIC_SetPriorityGrouping((uint32_t)0x03U);
    NVIC_SetPriority(DMA0_DMA16_IRQn, 0x00U);
    NVIC_SetPriority(PORTB_IRQn, 0x01);
    //NVIC_SetPriority(PIT1_IRQn, 0x02U);
    NVIC_SetPriority(PIT0_IRQn, 0x02U);
  
    PIT_StartTimer(PIT, kPIT_Chnl_0);

    record = DisableGlobalIRQ();
    display_menu();
    EnableGlobalIRQ(record);
}