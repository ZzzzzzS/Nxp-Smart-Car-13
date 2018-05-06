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
    //UART4_Init();               //初始化UART4(蓝牙)
    //Display_ASCII8X16(0,0,"UART",BLACK,WHITE);
    SteerInit();
    Display_ASCII8X16(0,0,"STEER",BLACK,WHITE);
    Button_Init();
    Display_ASCII8X16(0,0,"BUTT",BLACK,WHITE);
    
	FiveKey_Init();
	KeyBoard_Init();

    Display_ASCII8X16(0,0,"FIVE",BLACK,WHITE);
    Beep_Init();
    Display_ASCII8X16(0,0,"BEEP",BLACK,WHITE);
    RGB_Init();
    Display_ASCII8X16(0,0,"RGB",BLACK,WHITE);
    MotorInit();
    Display_ASCII8X16(0,0,"MOTO",BLACK,WHITE);
    Speed_Init();
    Display_ASCII8X16(0,0,"SPEED",BLACK,WHITE);
    PIT0_Init(20);
    Display_ASCII8X16(0,0,"PIT",BLACK,WHITE);
    //PIT1_Init(20);
    ADC_Init();
    Display_ASCII8X16(0,0,"ADC",BLACK,WHITE);
    
    PIDInit(&GV_speedControlT.Pid[0],0.8,0,0);
    PIDInit(&GV_speedControlT.Pid[1],0.8,0,0);
    GV_speedControlT.Pid[0].AimSpeed = 50;
    GV_speedControlT.Pid[1].AimSpeed = 50;
    //iic_init();   
    //MPU6050_Inital();
    result = Flash_init();
    Display_ASCII8X16(0,0,"FLASH",BLACK,WHITE);
    
    MT9V034_Init();
    Display_ASCII8X16(0,0,"CAMERA",BLACK,WHITE);
    
    NVIC_SetPriorityGrouping((uint32_t)0x03U);
    NVIC_SetPriority(DMA0_DMA16_IRQn, 0x00U);
    NVIC_SetPriority(PORTB_IRQn, 0x01);
    //NVIC_SetPriority(PIT1_IRQn, 0x02U);
    NVIC_SetPriority(PIT0_IRQn, 0x02U);
  
    PIT_StartTimer(PIT, kPIT_Chnl_0);

	record = DisableGlobalIRQ();
        delay_ms(500);
	AD_Get_side();
    display_menu();
	EnableGlobalIRQ(record);

    
}
