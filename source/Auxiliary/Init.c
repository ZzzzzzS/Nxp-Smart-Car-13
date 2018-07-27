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
     PORT_SetPinMux(PORTA, 4, kPORT_MuxAsGpio);                /* PORTA4 (pin 54) is configured as PTA4 */
    lcd_initial();//初始化LCD
    fullfill(0,0,128,128,BLACK);
    //干簧管初始化
    port_pin_config_t config = {
      kPORT_PullUp,
      kPORT_FastSlewRate,
      kPORT_PassiveFilterDisable,
      kPORT_OpenDrainDisable,
      kPORT_LowDriveStrength,
      kPORT_MuxAsGpio,
      kPORT_UnlockRegister,
	 };
 
    PORT_SetPinConfig(PORTC,11U,&config);
    gpio_init(GPIOC,11U,IN,LOW);
  	UART4_Init();               //初始化UART4(蓝牙)
    //Display_ASCII8X16(0,0,"UART",BLACK,WHITE);
    SteerInit();
    Display_ASCII8X16(0,0,"STEER",BLACK,WHITE);
    Button_Init();
    Display_ASCII8X16(0,0,"BUTT",BLACK,WHITE);
    
	FiveKey_Init();
	KeyBoard_Init();
    if(READ_KEY2)
    {
	SuperSonicInit();
    }
    Display_ASCII8X16(0,0,"FIVE",BLACK,WHITE);
    Beep_Init();
    Display_ASCII8X16(0,0,"BEEP",BLACK,WHITE);
    RGB_Init();
    Display_ASCII8X16(0,0,"RGB",BLACK,WHITE);
    MotorInit();
    Display_ASCII8X16(0,0,"MOTO",BLACK,WHITE);
    Speed_Init();
    Display_ASCII8X16(0,0,"SPEED",BLACK,WHITE);
    PIT0_Init(5);
    Display_ASCII8X16(0,0,"PIT",BLACK,WHITE);
    //PIT1_Init(20);
    ADC_Init();
    Display_ASCII8X16(0,0,"ADC",BLACK,WHITE);
 	   
    Display_ASCII8X16(0,0,"NRF",BLACK,WHITE);
    PIDInit(&GV_speedControlT.Pid[0],0.8,0,0);
    PIDInit(&GV_speedControlT.Pid[1],0.8,0,0);
    g_Speed = 30;
    //iic_init();   
    //MPU6050_Inital();
    result = Flash_init();
    Display_ASCII8X16(0,0,"FLASH",BLACK,WHITE);
    
    MT9V034_Init();
    Display_ASCII8X16(0,0,"CAMERA",BLACK,WHITE);
    
    NVIC_SetPriorityGrouping((uint32_t)0x03U);
    NVIC_SetPriority(DMA0_DMA16_IRQn, 0x00U);
    NVIC_SetPriority(PORTB_IRQn, 0x01);
    NVIC_SetPriority(PORTA_IRQn, 0x03);
    //NVIC_SetPriority(UART4_RX_TX_IRQn, 0x02U);
    NVIC_SetPriority(PIT0_IRQn, 0x02U);
    //NVIC_SetPriority(PIT2_IRQn, 0x03U);
	record = DisableGlobalIRQ();
        delay_ms(500);
    if(READ_KEY1)
	    AD_Get_side();
    else 
        flash_read(2,sizeof(ADside),(uint8_t*)&ADside);
    
    display_menu();
    delay_ms(5000);
    GV_speedControlT.Pid[0].SetSpeed = g_Speed;
    GV_speedControlT.Pid[1].SetSpeed = g_Speed;
	EnableGlobalIRQ(record);
    EnableIRQ(PORTA_IRQn);
    PIT_StartTimer(PIT, kPIT_Chnl_0);
    NRF24L01_Init();

}
