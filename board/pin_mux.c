/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKV58F1M0xxx24
package_id: MKV58F1M0VLQ24
mcu_data: ksdk2_0
processor_version: 2.0.0
pin_labels:
- {pin_num: '111', pin_signal: CMP2_IN4/CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/XB_IN3/UART0_RX/XB_OUT6/I2C0_SCL/FB_AD9, label: '高速串口(接到DAP上?)'}
- {pin_num: '112', pin_signal: CMP3_IN4/CMP0_IN1/PTC7/SPI0_SIN/XB_IN4/UART0_TX/XB_OUT7/I2C0_SDA/FB_AD8, label: '高速串口(接到DAP上?)'}
- {pin_num: '46', pin_signal: HSADC0B_CH5/HSADC1B_CH5/PTE25/LLWU_P21/CAN1_RX/FTM0_CH1/XB_IN3/I2C0_SDA/EWM_IN/XB_OUT5/UART4_RX, label: 串口}
- {pin_num: '45', pin_signal: HSADC0B_CH4/HSADC1B_CH4/PTE24/CAN1_TX/FTM0_CH0/XB_IN2/I2C0_SCL/EWM_OUT_b/XB_OUT4/UART4_TX, label: 串口}
- {pin_num: '113', pin_signal: HSADC1B_CH11/CMP0_IN2/PTC8/FTM3_CH4/FLEXPWM1_A2/FB_AD7, label: 电流计}
- {pin_num: '114', pin_signal: HSADC1B_CH12/CMP0_IN3/PTC9/FTM3_CH5/FLEXPWM1_B2/FB_AD6, label: 电流计}
- {pin_num: '127', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FTM0_CH0/FLEXPWM0_A0/FB_ALE/FB_CS1_b/FB_TS_b/FLEXPWM1_A0, label: L3G4200D陀螺仪(接CS)}
- {pin_num: '128', pin_signal: HSADC1A_CH11/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FTM0_CH1/FLEXPWM0_B0/FB_CS0_b/FLEXPWM1_B0, label: L3G4200D陀螺仪(接时钟脚)}
- {pin_num: '130', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FTM0_CH3/FLEXPWM0_B1/I2C0_SDA/FB_AD3/FLEXPWM1_B1, label: L3G4200D陀螺仪(MISO)}
- {pin_num: '129', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FTM0_CH2/FLEXPWM0_A1/I2C0_SCL/FB_AD4/FLEXPWM1_A1, label: L3G4200D陀螺仪(MOSI)}
- {pin_num: '91', pin_signal: HSADC0B_CH6/PTB10/SPI1_PCS0/UART3_RX/ENET0_1588_TMR3/FTM0_FLT1/FB_AD19, label: NRF24l01(CS片选信号)}
- {pin_num: '92', pin_signal: HSADC0B_CH7/PTB11/SPI1_SCK/UART3_TX/FTM0_FLT2/FB_AD18, label: NRF24l01(时钟)}
- {pin_num: '96', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/CAN0_RX/EWM_OUT_b/FB_AD16, label: NRF24l01(输入)}
- {pin_num: '95', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN2/CAN0_TX/EWM_IN/XB_IN5/FB_AD17, label: NRF24l01(输出)}
- {pin_num: '64', pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/FTM1_QD_PHA/I2C0_SCL, label: 正交解码L}
- {pin_num: '65', pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/FTM1_QD_PHB/I2C1_SDA, label: 正交解码L}
- {pin_num: '62', pin_signal: PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TRACE_D0, label: 正交解码R}
- {pin_num: '63', pin_signal: PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/FTM2_QD_PHB/I2C0_SDA, label: 正交解码R}
- {pin_num: '104', pin_signal: HSADC0B_CH9/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FLEXPWM0_A3/XB_IN11/FB_AD13, label: 电机L}
- {pin_num: '105', pin_signal: HSADC1B_CH10/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FLEXPWM0_B3/XB_IN6/FB_AD12, label: 电机L}
- {pin_num: '106', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/FTM3_FLT0, label: 电机R}
- {pin_num: '109', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/CMP1_OUT/FB_AD11, label: 电机R}
- {pin_num: '118', pin_signal: PTC13/CAN2_RX/FTM_CLKIN1/FLEXPWM1_B1/FB_AD26/UART4_CTS_b, label: 独立按键}
- {pin_num: '97', pin_signal: PTB18/CAN0_TX/FTM2_CH0/FTM3_CH2/FLEXPWM1_A1/FTM2_QD_PHA/FB_AD15, label: 舵机}
- {pin_num: '144', pin_signal: PTD15/SPI2_PCS1/FLEXPWM0_B0/FB_A23, label: 显示屏(DC)}
- {pin_num: '143', pin_signal: PTD14/SPI2_SIN/XB_IN11/XB_OUT11/FLEXPWM0_A0/FB_A22, label: 显示屏(RES)}
- {pin_num: '142', pin_signal: PTD13/SPI2_SOUT/XB_IN7/XB_OUT7/FLEXPWM0_B1/FB_A21, label: 显示屏(SDA)}
- {pin_num: '141', pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/XB_IN5/XB_OUT5/FLEXPWM0_A1/FB_A20, label: 显示屏(SCL)}
- {pin_num: '140', pin_signal: PTD11/LLWU_P25/SPI2_PCS0/UART5_CTS_b/FLEXPWM0_B2/FB_A19, label: 显示屏(CS)}
- {pin_num: '119', pin_signal: PTC14/I2C1_SCL/I2C0_SCL/FLEXPWM1_A0/FB_AD25/UART4_RX, label: 蜂鸣器}
- {pin_num: '120', pin_signal: PTC15/I2C1_SDA/I2C0_SDA/FLEXPWM1_B0/FB_AD24/UART4_TX, label: 按键}
- {pin_num: '123', pin_signal: PTC16/CAN1_RX/UART3_RX/ENET0_1588_TMR0/FLEXPWM1_A2/FB_CS5_b/FB_TSIZ1/FB_BE23_16_b, label: 按键}
- {pin_num: '124', pin_signal: PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FLEXPWM1_B2/FB_CS4_b/FB_TSIZ0/FB_BE31_24_b, label: 按键}
- {pin_num: '125', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FLEXPWM1_A3/FB_TBST_b/FB_CS2_b/FB_BE15_8_b, label: 按键}
- {pin_num: '126', pin_signal: PTC19/UART3_CTS_b/ENET0_1588_TMR3/FLEXPWM1_B3/FB_CS3_b/FB_BE7_0_b/FB_TA_b, label: 按键}
- {pin_num: '72', pin_signal: EXTAL0/PTA18/XB_IN7/FTM0_FLT2/FTM_CLKIN0/XB_OUT8/FTM3_CH2, label: 拨码开关}
- {pin_num: '73', pin_signal: XTAL0/PTA19/XB_IN8/FTM1_FLT0/FTM_CLKIN1/XB_OUT9/LPTMR0_ALT1, label: 拨码开关}
- {pin_num: '75', pin_signal: PTA24/XB_IN4/MII0_TXD2/FB_A29, label: 拨码开关}
- {pin_num: '76', pin_signal: PTA25/XB_IN5/MII0_TXCLK/FB_A28, label: 拨码开关}
- {pin_num: '77', pin_signal: PTA26/MII0_TXD3/FB_A27, label: 拨码开关}
- {pin_num: '78', pin_signal: PTA27/MII0_CRS/FB_A26, label: 拨码开关}
- {pin_num: '79', pin_signal: PTA28/MII0_TXER/FB_A25, label: 拨码开关}
- {pin_num: '80', pin_signal: PTA29/MII0_COL/FB_A24, label: 拨码开关}
- {pin_num: '54', pin_signal: PTA4/LLWU_P3/FTM0_CH1/XB_IN10/FTM0_FLT3/FLEXPWM0_B0/NMI_b, label: NMI外部上拉}
- {pin_num: '47', pin_signal: PTE26/ENET_1588_CLKIN/FTM0_CH4/UART4_CTS_b, label: 摄像头同步信号(PIX)}
- {pin_num: '48', pin_signal: PTE27/CAN2_TX/UART4_RTS_b, label: 摄像头同步信号(LINE)}
- {pin_num: '49', pin_signal: PTE28/CAN2_RX, label: 摄像头同步信号(FRM)}
- {pin_num: '21', pin_signal: HSADC0B_CH1/ADC0_SE6a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL/CMP3_OUT, label: 摄像头sccb总线(SCL)}
- {pin_num: '20', pin_signal: HSADC0B_CH0/ADC0_SE5a/PTE18/LLWU_P20/SPI0_SOUT/UART2_CTS_b/I2C0_SDA, label: 摄像头sccb总线(SDA)}
- {pin_num: '81', pin_signal: HSADC0B_CH2/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX/RMII0_MDIO/MII0_MDIO, label: 摄像头数据采集(D0)}
- {pin_num: '82', pin_signal: HSADC0B_CH3/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX/RMII0_MDC/MII0_MDC, label: 摄像头数据采集(D1)}
- {pin_num: '83', pin_signal: HSADC0A_CH14/CMP2_IN2/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/ENET0_1588_TMR0/FTM0_FLT3, label: 摄像头数据采集(D2)}
- {pin_num: '84', pin_signal: HSADC0B_CH15/CMP3_IN5/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/FTM0_FLT0, label: 摄像头数据采集(D3)}
- {pin_num: '85', pin_signal: ADC0_SE6b/PTB4/FLEXPWM1_X0/ENET0_1588_TMR2/FTM1_FLT0, label: 摄像头数据采集(D4)}
- {pin_num: '86', pin_signal: ADC0_SE7b/PTB5/FLEXPWM1_X1/ENET0_1588_TMR3/FTM2_FLT0, label: 摄像头数据采集(D5)}
- {pin_num: '87', pin_signal: HSADC1A_CH12/PTB6/CAN2_TX/FLEXPWM1_X2/FB_AD23, label: 摄像头数据采集(D6)}
- {pin_num: '88', pin_signal: HSADC1A_CH13/PTB7/CAN2_RX/FLEXPWM1_X3/FB_AD22, label: 摄像头数据采集(D7)}
- {pin_num: '89', pin_signal: PTB8/UART3_RTS_b/FB_AD21, label: 摄像头数据采集(D8)}
- {pin_num: '90', pin_signal: PTB9/SPI1_PCS1/UART3_CTS_b/ENET0_1588_TMR2/FB_AD20, label: 摄像头数据采集(D9)}
- {pin_num: '7', pin_signal: HSADC1A_CH4/ADC0_SE2/ADC0_DP2/PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/TRACE_D0, label: 电感}
- {pin_num: '8', pin_signal: HSADC1A_CH5/ADC0_SE10/ADC0_DM2/PTE5/SPI1_PCS2/UART3_RX/FLEXPWM1_A0/FTM3_CH0, label: 电感}
- {pin_num: '14', pin_signal: HSADC1A_CH6/ADC0_SE3/ADC0_DP3/PTE11/UART5_RTS_b/FLEXPWM1_A3/FTM3_CH6, label: 电感}
- {pin_num: '26', pin_signal: HSADC0A_CH9/HSADC1A_CH7/PTE21/XB_IN9/FTM1_CH1/UART0_RX/FTM1_QD_PHB, label: 电感}
- {pin_num: '132', pin_signal: HSADC1A_CH8/PTD5/SPI0_PCS2/UART0_CTS_b/UART0_COL_b/FTM0_CH5/FLEXPWM0_B2/EWM_OUT_b/SPI1_SCK/FB_AD1, label: 电感}
- {pin_num: '133', pin_signal: HSADC1A_CH9/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FTM1_CH0/FTM0_FLT0/SPI1_SOUT/FB_AD0, label: 电感}
- {pin_num: '139', pin_signal: PTD10/UART5_RTS_b/FLEXPWM0_A2/FB_A18, label: 显示屏(BL)}
- {pin_num: '68', pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0, label: 超声波模块(D0)}
- {pin_num: '69', pin_signal: HSADC0A_CH15/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1, label: 超声波模块(D1)}
- {pin_num: '137', pin_signal: PTD8/LLWU_P24/I2C1_SCL/UART5_RX/FLEXPWM0_A3/FB_A16, label: mpu6050}
- {pin_num: '138', pin_signal: PTD9/I2C1_SDA/UART5_TX/FLEXPWM0_B3/FB_A17, label: mpu6050}
- {pin_num: '117', pin_signal: PTC12/CAN2_TX/FTM_CLKIN0/FLEXPWM1_A1/FTM3_FLT0/SPI2_PCS1/FB_AD27/UART4_RTS_b, label: 独立按键}
- {pin_num: '11', pin_signal: PTE8/UART5_TX/FLEXPWM1_B1/FTM3_CH3, label: 三色灯R}
- {pin_num: '12', pin_signal: PTE9/LLWU_P17/UART5_RX/FLEXPWM1_A2/FTM3_CH4, label: 三色灯G}
- {pin_num: '13', pin_signal: PTE10/LLWU_P18/UART5_CTS_b/FLEXPWM1_B2/FTM3_CH5, label: 三色灯B}
- {pin_num: '116', pin_signal: HSADC1B_CH14/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FLEXPWM1_B3/FB_RW_b, label: LED}
- {pin_num: '115', pin_signal: HSADC1B_CH13/PTC10/I2C1_SCL/FTM3_CH6/FLEXPWM1_A3/FB_AD5, label: LED}
- {pin_num: '1', pin_signal: HSADC0B_CH16/HSADC1A_CH0/PTE0/SPI1_PCS1/UART1_TX/XB_OUT10/XB_IN11/I2C1_SDA/TRACE_CLKOUT, label: NRF24l01}
- {pin_num: '9', pin_signal: HSADC1B_CH7/ADC0_SE4a/PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/FLEXPWM1_B0/FTM3_CH1, label: NRF24l01}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    HIDPinsInit();
    CamraPinsInit();
    MotorPinsInit();
    InductancePinsInit();
    CommunicationPinsInit();
    OtherSensorPinsInit();
    BoardPinsInit();
}

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */
#define PIN28_IDX                       28u   /*!< Pin number for pin 28 in a port */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define SOPT8_FTM3OCH3SRC_FTM         0x00u   /*!< FTM3 channel 3 output source: FTM3_CH3 pin is output of FTM3 channel 3 output */
#define SOPT8_FTM3OCH4SRC_FTM         0x00u   /*!< FTM3 channel 4 output source: FTM3_CH4 pin is output of FTM3 channel 4 output */
#define SOPT8_FTM3OCH5SRC_FTM         0x00u   /*!< FTM3 channel 5 output source: FTM3_CH5 pin is output of FTM3 channel 5 output */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
HIDPinsInit:
- options: {callFromInitBoot: 'true', prefix: HIDPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '140', peripheral: SPI2, signal: PCS0_SS, pin_signal: PTD11/LLWU_P25/SPI2_PCS0/UART5_CTS_b/FLEXPWM0_B2/FB_A19}
  - {pin_num: '144', peripheral: SPI2, signal: PCS1, pin_signal: PTD15/SPI2_PCS1/FLEXPWM0_B0/FB_A23}
  - {pin_num: '141', peripheral: SPI2, signal: SCK, pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/XB_IN5/XB_OUT5/FLEXPWM0_A1/FB_A20}
  - {pin_num: '143', peripheral: SPI2, signal: SIN, pin_signal: PTD14/SPI2_SIN/XB_IN11/XB_OUT11/FLEXPWM0_A0/FB_A22}
  - {pin_num: '142', peripheral: SPI2, signal: SOUT, pin_signal: PTD13/SPI2_SOUT/XB_IN7/XB_OUT7/FLEXPWM0_B1/FB_A21}
  - {pin_num: '120', peripheral: GPIOC, signal: 'GPIO, 15', pin_signal: PTC15/I2C1_SDA/I2C0_SDA/FLEXPWM1_B0/FB_AD24/UART4_TX}
  - {pin_num: '123', peripheral: GPIOC, signal: 'GPIO, 16', pin_signal: PTC16/CAN1_RX/UART3_RX/ENET0_1588_TMR0/FLEXPWM1_A2/FB_CS5_b/FB_TSIZ1/FB_BE23_16_b}
  - {pin_num: '124', peripheral: GPIOC, signal: 'GPIO, 17', pin_signal: PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FLEXPWM1_B2/FB_CS4_b/FB_TSIZ0/FB_BE31_24_b}
  - {pin_num: '125', peripheral: GPIOC, signal: 'GPIO, 18', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FLEXPWM1_A3/FB_TBST_b/FB_CS2_b/FB_BE15_8_b}
  - {pin_num: '126', peripheral: GPIOC, signal: 'GPIO, 19', pin_signal: PTC19/UART3_CTS_b/ENET0_1588_TMR3/FLEXPWM1_B3/FB_CS3_b/FB_BE7_0_b/FB_TA_b}
  - {pin_num: '80', peripheral: GPIOA, signal: 'GPIO, 29', pin_signal: PTA29/MII0_COL/FB_A24}
  - {pin_num: '79', peripheral: GPIOA, signal: 'GPIO, 28', pin_signal: PTA28/MII0_TXER/FB_A25}
  - {pin_num: '78', peripheral: GPIOA, signal: 'GPIO, 27', pin_signal: PTA27/MII0_CRS/FB_A26}
  - {pin_num: '77', peripheral: GPIOA, signal: 'GPIO, 26', pin_signal: PTA26/MII0_TXD3/FB_A27}
  - {pin_num: '76', peripheral: GPIOA, signal: 'GPIO, 25', pin_signal: PTA25/XB_IN5/MII0_TXCLK/FB_A28}
  - {pin_num: '75', peripheral: GPIOA, signal: 'GPIO, 24', pin_signal: PTA24/XB_IN4/MII0_TXD2/FB_A29}
  - {pin_num: '73', peripheral: GPIOA, signal: 'GPIO, 19', pin_signal: XTAL0/PTA19/XB_IN8/FTM1_FLT0/FTM_CLKIN1/XB_OUT9/LPTMR0_ALT1}
  - {pin_num: '72', peripheral: GPIOA, signal: 'GPIO, 18', pin_signal: EXTAL0/PTA18/XB_IN7/FTM0_FLT2/FTM_CLKIN0/XB_OUT8/FTM3_CH2}
  - {pin_num: '139', peripheral: GPIOD, signal: 'GPIO, 10', pin_signal: PTD10/UART5_RTS_b/FLEXPWM0_A2/FB_A18}
  - {pin_num: '118', peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/CAN2_RX/FTM_CLKIN1/FLEXPWM1_B1/FB_AD26/UART4_CTS_b}
  - {pin_num: '117', peripheral: GPIOC, signal: 'GPIO, 12', pin_signal: PTC12/CAN2_TX/FTM_CLKIN0/FLEXPWM1_A1/FTM3_FLT0/SPI2_PCS1/FB_AD27/UART4_RTS_b}
  - {pin_num: '11', peripheral: FTM3, signal: 'CH, 3', pin_signal: PTE8/UART5_TX/FLEXPWM1_B1/FTM3_CH3, direction: OUTPUT}
  - {pin_num: '12', peripheral: FTM3, signal: 'CH, 4', pin_signal: PTE9/LLWU_P17/UART5_RX/FLEXPWM1_A2/FTM3_CH4, direction: OUTPUT}
  - {pin_num: '13', peripheral: FTM3, signal: 'CH, 5', pin_signal: PTE10/LLWU_P18/UART5_CTS_b/FLEXPWM1_B2/FTM3_CH5, direction: OUTPUT}
  - {pin_num: '116', peripheral: GPIOC, signal: 'GPIO, 11', pin_signal: HSADC1B_CH14/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FLEXPWM1_B3/FB_RW_b}
  - {pin_num: '115', peripheral: GPIOC, signal: 'GPIO, 10', pin_signal: HSADC1B_CH13/PTC10/I2C1_SCL/FTM3_CH6/FLEXPWM1_A3/FB_AD5}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : HIDPinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void HIDPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN18_IDX, kPORT_MuxAsGpio);         /* PORTA18 (pin 72) is configured as PTA18 */
  PORT_SetPinMux(PORTA, PIN19_IDX, kPORT_MuxAsGpio);         /* PORTA19 (pin 73) is configured as PTA19 */
  PORT_SetPinMux(PORTA, PIN24_IDX, kPORT_MuxAsGpio);         /* PORTA24 (pin 75) is configured as PTA24 */
  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_MuxAsGpio);         /* PORTA25 (pin 76) is configured as PTA25 */
  PORT_SetPinMux(PORTA, PIN26_IDX, kPORT_MuxAsGpio);         /* PORTA26 (pin 77) is configured as PTA26 */
  PORT_SetPinMux(PORTA, PIN27_IDX, kPORT_MuxAsGpio);         /* PORTA27 (pin 78) is configured as PTA27 */
  PORT_SetPinMux(PORTA, PIN28_IDX, kPORT_MuxAsGpio);         /* PORTA28 (pin 79) is configured as PTA28 */
  PORT_SetPinMux(PORTA, PIN29_IDX, kPORT_MuxAsGpio);         /* PORTA29 (pin 80) is configured as PTA29 */
  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAsGpio);         /* PORTC10 (pin 115) is configured as PTC10 */
  PORT_SetPinMux(PORTC, PIN11_IDX, kPORT_MuxAsGpio);         /* PORTC11 (pin 116) is configured as PTC11 */
  PORT_SetPinMux(PORTC, PIN12_IDX, kPORT_MuxAsGpio);         /* PORTC12 (pin 117) is configured as PTC12 */
  PORT_SetPinMux(PORTC, PIN13_IDX, kPORT_MuxAsGpio);         /* PORTC13 (pin 118) is configured as PTC13 */
  PORT_SetPinMux(PORTC, PIN15_IDX, kPORT_MuxAsGpio);         /* PORTC15 (pin 120) is configured as PTC15 */
  PORT_SetPinMux(PORTC, PIN16_IDX, kPORT_MuxAsGpio);         /* PORTC16 (pin 123) is configured as PTC16 */
  PORT_SetPinMux(PORTC, PIN17_IDX, kPORT_MuxAsGpio);         /* PORTC17 (pin 124) is configured as PTC17 */
  PORT_SetPinMux(PORTC, PIN18_IDX, kPORT_MuxAsGpio);         /* PORTC18 (pin 125) is configured as PTC18 */
  PORT_SetPinMux(PORTC, PIN19_IDX, kPORT_MuxAsGpio);         /* PORTC19 (pin 126) is configured as PTC19 */
  PORT_SetPinMux(PORTD, PIN10_IDX, kPORT_MuxAsGpio);         /* PORTD10 (pin 139) is configured as PTD10 */
  PORT_SetPinMux(PORTD, PIN11_IDX, kPORT_MuxAlt2);           /* PORTD11 (pin 140) is configured as SPI2_PCS0 */
  PORT_SetPinMux(PORTD, PIN12_IDX, kPORT_MuxAlt2);           /* PORTD12 (pin 141) is configured as SPI2_SCK */
  PORT_SetPinMux(PORTD, PIN13_IDX, kPORT_MuxAlt2);           /* PORTD13 (pin 142) is configured as SPI2_SOUT */
  PORT_SetPinMux(PORTD, PIN14_IDX, kPORT_MuxAlt2);           /* PORTD14 (pin 143) is configured as SPI2_SIN */
  PORT_SetPinMux(PORTD, PIN15_IDX, kPORT_MuxAlt2);           /* PORTD15 (pin 144) is configured as SPI2_PCS1 */
  PORT_SetPinMux(PORTE, PIN10_IDX, kPORT_MuxAlt6);           /* PORTE10 (pin 13) is configured as FTM3_CH5 */
  PORT_SetPinMux(PORTE, PIN8_IDX, kPORT_MuxAlt6);            /* PORTE8 (pin 11) is configured as FTM3_CH3 */
  PORT_SetPinMux(PORTE, PIN9_IDX, kPORT_MuxAlt6);            /* PORTE9 (pin 12) is configured as FTM3_CH4 */
  SIM->SOPT8 = ((SIM->SOPT8 &
    (~(SIM_SOPT8_FTM3OCH3SRC_MASK | SIM_SOPT8_FTM3OCH4SRC_MASK | SIM_SOPT8_FTM3OCH5SRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT8_FTM3OCH3SRC(SOPT8_FTM3OCH3SRC_FTM)         /* FTM3 channel 3 output source: FTM3_CH3 pin is output of FTM3 channel 3 output */
      | SIM_SOPT8_FTM3OCH4SRC(SOPT8_FTM3OCH4SRC_FTM)         /* FTM3 channel 4 output source: FTM3_CH4 pin is output of FTM3 channel 4 output */
      | SIM_SOPT8_FTM3OCH5SRC(SOPT8_FTM3OCH5SRC_FTM)         /* FTM3 channel 5 output source: FTM3_CH5 pin is output of FTM3 channel 5 output */
    );
}


#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port */

#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port */

#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port */

#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */

#define PIN28_IDX                       28u   /*!< Pin number for pin 28 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
CamraPinsInit:
- options: {callFromInitBoot: 'true', prefix: CAMRAPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '21', peripheral: I2C0, signal: SCL, pin_signal: HSADC0B_CH1/ADC0_SE6a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL/CMP3_OUT, pull_select: no_init}
  - {pin_num: '20', peripheral: I2C0, signal: SDA, pin_signal: HSADC0B_CH0/ADC0_SE5a/PTE18/LLWU_P20/SPI0_SOUT/UART2_CTS_b/I2C0_SDA, pull_select: no_init}
  - {pin_num: '47', peripheral: GPIOE, signal: 'GPIO, 26', pin_signal: PTE26/ENET_1588_CLKIN/FTM0_CH4/UART4_CTS_b, direction: INPUT}
  - {pin_num: '48', peripheral: GPIOE, signal: 'GPIO, 27', pin_signal: PTE27/CAN2_TX/UART4_RTS_b, direction: INPUT}
  - {pin_num: '49', peripheral: GPIOE, signal: 'GPIO, 28', pin_signal: PTE28/CAN2_RX, direction: INPUT}
  - {pin_num: '81', peripheral: GPIOB, signal: 'GPIO, 0', pin_signal: HSADC0B_CH2/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX/RMII0_MDIO/MII0_MDIO, direction: INPUT}
  - {pin_num: '82', peripheral: GPIOB, signal: 'GPIO, 1', pin_signal: HSADC0B_CH3/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX/RMII0_MDC/MII0_MDC,
    direction: INPUT}
  - {pin_num: '83', peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: HSADC0A_CH14/CMP2_IN2/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/ENET0_1588_TMR0/FTM0_FLT3, direction: INPUT}
  - {pin_num: '84', peripheral: GPIOB, signal: 'GPIO, 3', pin_signal: HSADC0B_CH15/CMP3_IN5/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/FTM0_FLT0, direction: INPUT}
  - {pin_num: '85', peripheral: GPIOB, signal: 'GPIO, 4', pin_signal: ADC0_SE6b/PTB4/FLEXPWM1_X0/ENET0_1588_TMR2/FTM1_FLT0, direction: INPUT}
  - {pin_num: '86', peripheral: GPIOB, signal: 'GPIO, 5', pin_signal: ADC0_SE7b/PTB5/FLEXPWM1_X1/ENET0_1588_TMR3/FTM2_FLT0, direction: INPUT}
  - {pin_num: '87', peripheral: GPIOB, signal: 'GPIO, 6', pin_signal: HSADC1A_CH12/PTB6/CAN2_TX/FLEXPWM1_X2/FB_AD23, direction: INPUT}
  - {pin_num: '88', peripheral: GPIOB, signal: 'GPIO, 7', pin_signal: HSADC1A_CH13/PTB7/CAN2_RX/FLEXPWM1_X3/FB_AD22, direction: INPUT}
  - {pin_num: '89', peripheral: GPIOB, signal: 'GPIO, 8', pin_signal: PTB8/UART3_RTS_b/FB_AD21, direction: INPUT}
  - {pin_num: '90', peripheral: GPIOB, signal: 'GPIO, 9', pin_signal: PTB9/SPI1_PCS1/UART3_CTS_b/ENET0_1588_TMR2/FB_AD20, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : CamraPinsInit
 * Description   : 
 *
 *END**************************************************************************/
void CamraPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAsGpio);          /* PORTB0 (pin 81) is configured as PTB0 */
  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAsGpio);          /* PORTB1 (pin 82) is configured as PTB1 */
  PORT_SetPinMux(PORTB, PIN2_IDX, kPORT_MuxAsGpio);          /* PORTB2 (pin 83) is configured as PTB2 */
  PORT_SetPinMux(PORTB, PIN3_IDX, kPORT_MuxAsGpio);          /* PORTB3 (pin 84) is configured as PTB3 */
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAsGpio);          /* PORTB4 (pin 85) is configured as PTB4 */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAsGpio);          /* PORTB5 (pin 86) is configured as PTB5 */
  PORT_SetPinMux(PORTB, PIN6_IDX, kPORT_MuxAsGpio);          /* PORTB6 (pin 87) is configured as PTB6 */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAsGpio);          /* PORTB7 (pin 88) is configured as PTB7 */
  PORT_SetPinMux(PORTB, PIN8_IDX, kPORT_MuxAsGpio);          /* PORTB8 (pin 89) is configured as PTB8 */
  PORT_SetPinMux(PORTB, PIN9_IDX, kPORT_MuxAsGpio);          /* PORTB9 (pin 90) is configured as PTB9 */
  PORT_SetPinMux(PORTE, PIN18_IDX, kPORT_MuxAlt4);           /* PORTE18 (pin 20) is configured as I2C0_SDA */
  PORT_SetPinMux(PORTE, PIN19_IDX, kPORT_MuxAlt4);           /* PORTE19 (pin 21) is configured as I2C0_SCL */
  PORT_SetPinMux(PORTE, PIN26_IDX, kPORT_MuxAsGpio);         /* PORTE26 (pin 47) is configured as PTE26 */
  PORT_SetPinMux(PORTE, PIN27_IDX, kPORT_MuxAsGpio);         /* PORTE27 (pin 48) is configured as PTE27 */
  PORT_SetPinMux(PORTE, PIN28_IDX, kPORT_MuxAsGpio);         /* PORTE28 (pin 49) is configured as PTE28 */
}



#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */

#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */

#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */

#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */

#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port */

#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port */
#define SOPT8_FTM0OCH0SRC_FTM         0x00u   /*!< FTM0 channel 0 output source: FTM0_CH0 pin is output of FTM0 channel 0 output */
#define SOPT8_FTM0OCH1SRC_FTM         0x00u   /*!< FTM0 channel 1 output source: FTM0_CH1 pin is output of FTM0 channel 1 output */
#define SOPT8_FTM0OCH2SRC_FTM         0x00u   /*!< FTM0 channel 2 output source: FTM0_CH2 pin is output of FTM0 channel 2 output */
#define SOPT8_FTM0OCH3SRC_FTM         0x00u   /*!< FTM0 channel 3 output source: FTM0_CH3 pin is output of FTM0 channel 3 output */
#define SOPT8_FTM3OCH2SRC_FTM         0x00u   /*!< FTM3 channel 2 output source: FTM3_CH2 pin is output of FTM3 channel 2 output */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MotorPinsInit:
- options: {callFromInitBoot: 'true', prefix: MOTORPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '64', peripheral: FTM1, signal: 'QD_PH, A', pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/FTM1_QD_PHA/I2C0_SCL}
  - {pin_num: '65', peripheral: FTM1, signal: 'QD_PH, B', pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/FTM1_QD_PHB/I2C1_SDA}
  - {pin_num: '62', peripheral: FTM2, signal: 'QD_PH, A', pin_signal: PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TRACE_D0}
  - {pin_num: '63', peripheral: FTM2, signal: 'QD_PH, B', pin_signal: PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/FTM2_QD_PHB/I2C0_SDA}
  - {pin_num: '104', peripheral: FTM0, signal: 'CH, 0', pin_signal: HSADC0B_CH9/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FLEXPWM0_A3/XB_IN11/FB_AD13, direction: OUTPUT}
  - {pin_num: '105', peripheral: FTM0, signal: 'CH, 1', pin_signal: HSADC1B_CH10/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FLEXPWM0_B3/XB_IN6/FB_AD12, direction: OUTPUT}
  - {pin_num: '106', peripheral: FTM0, signal: 'CH, 2', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/FTM3_FLT0, direction: OUTPUT}
  - {pin_num: '109', peripheral: FTM0, signal: 'CH, 3', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/CMP1_OUT/FB_AD11, direction: OUTPUT}
  - {pin_num: '97', peripheral: FTM3, signal: 'CH, 2', pin_signal: PTB18/CAN0_TX/FTM2_CH0/FTM3_CH2/FLEXPWM1_A1/FTM2_QD_PHA/FB_AD15, direction: OUTPUT}
  - {pin_num: '113', peripheral: HSADC1, signal: 'ADCB, CH11', pin_signal: HSADC1B_CH11/CMP0_IN2/PTC8/FTM3_CH4/FLEXPWM1_A2/FB_AD7}
  - {pin_num: '114', peripheral: HSADC1, signal: 'ADCB, CH12', pin_signal: HSADC1B_CH12/CMP0_IN3/PTC9/FTM3_CH5/FLEXPWM1_B2/FB_AD6}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : MotorPinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void MotorPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN10_IDX, kPORT_MuxAlt6);           /* PORTA10 (pin 62) is configured as FTM2_QD_PHA */
  PORT_SetPinMux(PORTA, PIN11_IDX, kPORT_MuxAlt6);           /* PORTA11 (pin 63) is configured as FTM2_QD_PHB */
  PORT_SetPinMux(PORTA, PIN12_IDX, kPORT_MuxAlt7);           /* PORTA12 (pin 64) is configured as FTM1_QD_PHA */
  PORT_SetPinMux(PORTA, PIN13_IDX, kPORT_MuxAlt7);           /* PORTA13 (pin 65) is configured as FTM1_QD_PHB */
  PORT_SetPinMux(PORTB, PIN18_IDX, kPORT_MuxAlt4);           /* PORTB18 (pin 97) is configured as FTM3_CH2 */
  PORT_SetPinMux(PORTC, PIN1_IDX, kPORT_MuxAlt4);            /* PORTC1 (pin 104) is configured as FTM0_CH0 */
  PORT_SetPinMux(PORTC, PIN2_IDX, kPORT_MuxAlt4);            /* PORTC2 (pin 105) is configured as FTM0_CH1 */
  PORT_SetPinMux(PORTC, PIN3_IDX, kPORT_MuxAlt4);            /* PORTC3 (pin 106) is configured as FTM0_CH2 */
  PORT_SetPinMux(PORTC, PIN4_IDX, kPORT_MuxAlt4);            /* PORTC4 (pin 109) is configured as FTM0_CH3 */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_PinDisabledOrAnalog); /* PORTC8 (pin 113) is configured as HSADC1B_CH11 */
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_PinDisabledOrAnalog); /* PORTC9 (pin 114) is configured as HSADC1B_CH12 */
  SIM->SOPT8 = ((SIM->SOPT8 &
    (~(SIM_SOPT8_FTM0OCH0SRC_MASK | SIM_SOPT8_FTM0OCH1SRC_MASK | SIM_SOPT8_FTM0OCH2SRC_MASK | SIM_SOPT8_FTM0OCH3SRC_MASK | SIM_SOPT8_FTM3OCH2SRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT8_FTM0OCH0SRC(SOPT8_FTM0OCH0SRC_FTM)         /* FTM0 channel 0 output source: FTM0_CH0 pin is output of FTM0 channel 0 output */
      | SIM_SOPT8_FTM0OCH1SRC(SOPT8_FTM0OCH1SRC_FTM)         /* FTM0 channel 1 output source: FTM0_CH1 pin is output of FTM0 channel 1 output */
      | SIM_SOPT8_FTM0OCH2SRC(SOPT8_FTM0OCH2SRC_FTM)         /* FTM0 channel 2 output source: FTM0_CH2 pin is output of FTM0 channel 2 output */
      | SIM_SOPT8_FTM0OCH3SRC(SOPT8_FTM0OCH3SRC_FTM)         /* FTM0 channel 3 output source: FTM0_CH3 pin is output of FTM0 channel 3 output */
      | SIM_SOPT8_FTM3OCH2SRC(SOPT8_FTM3OCH2SRC_FTM)         /* FTM3 channel 2 output source: FTM3_CH2 pin is output of FTM3 channel 2 output */
    );
}



#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */

#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */

#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */

#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */
#define PIN21_IDX                       21u   /*!< Pin number for pin 21 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
InductancePinsInit:
- options: {callFromInitBoot: 'true', prefix: INDUCTANCEPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '7', peripheral: HSADC1, signal: 'ADCA, CH4', pin_signal: HSADC1A_CH4/ADC0_SE2/ADC0_DP2/PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/TRACE_D0}
  - {pin_num: '8', peripheral: HSADC1, signal: 'ADCA, CH5', pin_signal: HSADC1A_CH5/ADC0_SE10/ADC0_DM2/PTE5/SPI1_PCS2/UART3_RX/FLEXPWM1_A0/FTM3_CH0}
  - {pin_num: '14', peripheral: HSADC1, signal: 'ADCA, CH6', pin_signal: HSADC1A_CH6/ADC0_SE3/ADC0_DP3/PTE11/UART5_RTS_b/FLEXPWM1_A3/FTM3_CH6}
  - {pin_num: '26', peripheral: HSADC1, signal: 'ADCA, CH7', pin_signal: HSADC0A_CH9/HSADC1A_CH7/PTE21/XB_IN9/FTM1_CH1/UART0_RX/FTM1_QD_PHB}
  - {pin_num: '132', peripheral: HSADC1, signal: 'ADCA, CH8', pin_signal: HSADC1A_CH8/PTD5/SPI0_PCS2/UART0_CTS_b/UART0_COL_b/FTM0_CH5/FLEXPWM0_B2/EWM_OUT_b/SPI1_SCK/FB_AD1}
  - {pin_num: '133', peripheral: HSADC1, signal: 'ADCA, CH9', pin_signal: HSADC1A_CH9/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FTM1_CH0/FTM0_FLT0/SPI1_SOUT/FB_AD0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : InductancePinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void InductancePinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTD, PIN5_IDX, kPORT_PinDisabledOrAnalog); /* PORTD5 (pin 132) is configured as HSADC1A_CH8 */
  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_PinDisabledOrAnalog); /* PORTD6 (pin 133) is configured as HSADC1A_CH9 */
  PORT_SetPinMux(PORTE, PIN11_IDX, kPORT_PinDisabledOrAnalog); /* PORTE11 (pin 14) is configured as HSADC1A_CH6 */
  PORT_SetPinMux(PORTE, PIN21_IDX, kPORT_PinDisabledOrAnalog); /* PORTE21 (pin 26) is configured as HSADC1A_CH7 */
  PORT_SetPinMux(PORTE, PIN4_IDX, kPORT_PinDisabledOrAnalog); /* PORTE4 (pin 7) is configured as HSADC1A_CH4 */
  PORT_SetPinMux(PORTE, PIN5_IDX, kPORT_PinDisabledOrAnalog); /* PORTE5 (pin 8) is configured as HSADC1A_CH5 */
}



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */

#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */

#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */

#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */

#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */

#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */

#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */

#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */
#define SOPT5_UART0RXSRC_UART_RX      0x00u   /*!< UART 0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART 0 transmit data source select: UART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
CommunicationPinsInit:
- options: {callFromInitBoot: 'true', prefix: COMMUNICATIONPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '111', peripheral: UART0, signal: RX, pin_signal: CMP2_IN4/CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/XB_IN3/UART0_RX/XB_OUT6/I2C0_SCL/FB_AD9}
  - {pin_num: '112', peripheral: UART0, signal: TX, pin_signal: CMP3_IN4/CMP0_IN1/PTC7/SPI0_SIN/XB_IN4/UART0_TX/XB_OUT7/I2C0_SDA/FB_AD8}
  - {pin_num: '46', peripheral: UART4, signal: RX, pin_signal: HSADC0B_CH5/HSADC1B_CH5/PTE25/LLWU_P21/CAN1_RX/FTM0_CH1/XB_IN3/I2C0_SDA/EWM_IN/XB_OUT5/UART4_RX}
  - {pin_num: '45', peripheral: UART4, signal: TX, pin_signal: HSADC0B_CH4/HSADC1B_CH4/PTE24/CAN1_TX/FTM0_CH0/XB_IN2/I2C0_SCL/EWM_OUT_b/XB_OUT4/UART4_TX}
  - {pin_num: '91', peripheral: SPI1, signal: PCS0_SS, pin_signal: HSADC0B_CH6/PTB10/SPI1_PCS0/UART3_RX/ENET0_1588_TMR3/FTM0_FLT1/FB_AD19}
  - {pin_num: '92', peripheral: SPI1, signal: SCK, pin_signal: HSADC0B_CH7/PTB11/SPI1_SCK/UART3_TX/FTM0_FLT2/FB_AD18}
  - {pin_num: '96', peripheral: SPI1, signal: SIN, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/CAN0_RX/EWM_OUT_b/FB_AD16}
  - {pin_num: '95', peripheral: SPI1, signal: SOUT, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN2/CAN0_TX/EWM_IN/XB_IN5/FB_AD17}
  - {pin_num: '1', peripheral: SPI1, signal: PCS1, pin_signal: HSADC0B_CH16/HSADC1A_CH0/PTE0/SPI1_PCS1/UART1_TX/XB_OUT10/XB_IN11/I2C1_SDA/TRACE_CLKOUT}
  - {pin_num: '9', peripheral: SPI1, signal: PCS3, pin_signal: HSADC1B_CH7/ADC0_SE4a/PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/FLEXPWM1_B0/FTM3_CH1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : CommunicationPinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void CommunicationPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN10_IDX, kPORT_MuxAlt2);           /* PORTB10 (pin 91) is configured as SPI1_PCS0 */
  PORT_SetPinMux(PORTB, PIN11_IDX, kPORT_MuxAlt2);           /* PORTB11 (pin 92) is configured as SPI1_SCK */
  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt2);           /* PORTB16 (pin 95) is configured as SPI1_SOUT */
  PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt2);           /* PORTB17 (pin 96) is configured as SPI1_SIN */
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_MuxAlt5);            /* PORTC6 (pin 111) is configured as UART0_RX */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt5);            /* PORTC7 (pin 112) is configured as UART0_TX */
  PORT_SetPinMux(PORTE, PIN0_IDX, kPORT_MuxAlt2);            /* PORTE0 (pin 1) is configured as SPI1_PCS1 */
  PORT_SetPinMux(PORTE, PIN24_IDX, kPORT_MuxAlt8);           /* PORTE24 (pin 45) is configured as UART4_TX */
  PORT_SetPinMux(PORTE, PIN25_IDX, kPORT_MuxAlt8);           /* PORTE25 (pin 46) is configured as UART4_RX */
  PORT_SetPinMux(PORTE, PIN6_IDX, kPORT_MuxAlt2);            /* PORTE6 (pin 9) is configured as SPI1_PCS3 */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)       /* UART 0 transmit data source select: UART0_TX pin */
      | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX)       /* UART 0 receive data source select: UART0_RX pin */
    );
}



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */

#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */

#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */

#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */

#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
OtherSensorPinsInit:
- options: {callFromInitBoot: 'true', prefix: OTHERSENSORPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '127', peripheral: SPI0, signal: PCS0_SS, pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FTM0_CH0/FLEXPWM0_A0/FB_ALE/FB_CS1_b/FB_TS_b/FLEXPWM1_A0}
  - {pin_num: '128', peripheral: SPI0, signal: SCK, pin_signal: HSADC1A_CH11/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FTM0_CH1/FLEXPWM0_B0/FB_CS0_b/FLEXPWM1_B0}
  - {pin_num: '130', peripheral: SPI0, signal: SIN, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FTM0_CH3/FLEXPWM0_B1/I2C0_SDA/FB_AD3/FLEXPWM1_B1}
  - {pin_num: '129', peripheral: SPI0, signal: SOUT, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FTM0_CH2/FLEXPWM0_A1/I2C0_SCL/FB_AD4/FLEXPWM1_A1}
  - {pin_num: '137', peripheral: I2C1, signal: SCL, pin_signal: PTD8/LLWU_P24/I2C1_SCL/UART5_RX/FLEXPWM0_A3/FB_A16}
  - {pin_num: '138', peripheral: I2C1, signal: SDA, pin_signal: PTD9/I2C1_SDA/UART5_TX/FLEXPWM0_B3/FB_A17}
  - {pin_num: '68', peripheral: GPIOA, signal: 'GPIO, 16', pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0}
  - {pin_num: '69', peripheral: GPIOA, signal: 'GPIO, 17', pin_signal: HSADC0A_CH15/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1}
  - {pin_num: '119', peripheral: GPIOC, signal: 'GPIO, 14', pin_signal: PTC14/I2C1_SCL/I2C0_SCL/FLEXPWM1_A0/FB_AD25/UART4_RX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : OtherSensorPinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void OtherSensorPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN16_IDX, kPORT_MuxAsGpio);         /* PORTA16 (pin 68) is configured as PTA16 */
  PORT_SetPinMux(PORTA, PIN17_IDX, kPORT_MuxAsGpio);         /* PORTA17 (pin 69) is configured as PTA17 */
  PORT_SetPinMux(PORTC, PIN14_IDX, kPORT_MuxAsGpio);         /* PORTC14 (pin 119) is configured as PTC14 */
  PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2);            /* PORTD0 (pin 127) is configured as SPI0_PCS0 */
  PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2);            /* PORTD1 (pin 128) is configured as SPI0_SCK */
  PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2);            /* PORTD2 (pin 129) is configured as SPI0_SOUT */
  PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAlt2);            /* PORTD3 (pin 130) is configured as SPI0_SIN */
  PORT_SetPinMux(PORTD, PIN8_IDX, kPORT_MuxAlt2);            /* PORTD8 (pin 137) is configured as I2C1_SCL */
  PORT_SetPinMux(PORTD, PIN9_IDX, kPORT_MuxAlt2);            /* PORTD9 (pin 138) is configured as I2C1_SDA */
}



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */

#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */

#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BoardPinsInit:
- options: {callFromInitBoot: 'true', prefix: BOARDPINSINIT_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/XB_IN10/FTM0_FLT3/FLEXPWM0_B0/NMI_b}
  - {pin_num: '50', peripheral: JTAG, signal: JTAG_TCLK_SWD_CLK, pin_signal: PTA0/UART0_CTS_b/UART0_COL_b/FTM0_CH5/XB_IN4/EWM_IN/JTAG_TCLK/SWD_CLK}
  - {pin_num: '53', peripheral: JTAG, signal: JTAG_TMS_SWD_DIO, pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/XB_IN9/EWM_OUT_b/FLEXPWM0_A0/JTAG_TMS/SWD_DIO}
  - {pin_num: '51', peripheral: JTAG, signal: TDI, pin_signal: PTA1/UART0_RX/FTM0_CH6/CMP0_OUT/FTM2_QD_PHA/FTM1_CH1/JTAG_TDI}
  - {pin_num: '52', peripheral: JTAG, signal: TDO, pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO}
  - {pin_num: '55', peripheral: JTAG, signal: TRST, pin_signal: PTA5/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/JTAG_TRST_b}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BoardPinsInit
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BoardPinsInit(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN0_IDX, kPORT_MuxAlt7);            /* PORTA0 (pin 50) is configured as JTAG_TCLK */
  PORT_SetPinMux(PORTA, PIN1_IDX, kPORT_MuxAlt7);            /* PORTA1 (pin 51) is configured as JTAG_TDI */
  PORT_SetPinMux(PORTA, PIN2_IDX, kPORT_MuxAlt7);            /* PORTA2 (pin 52) is configured as JTAG_TDO */
  PORT_SetPinMux(PORTA, PIN3_IDX, kPORT_MuxAlt7);            /* PORTA3 (pin 53) is configured as JTAG_TMS */
  PORT_SetPinMux(PORTA, PIN4_IDX, kPORT_MuxAsGpio);          /* PORTA4 (pin 54) is configured as PTA4 */
  PORT_SetPinMux(PORTA, PIN5_IDX, kPORT_MuxAlt7);            /* PORTA5 (pin 55) is configured as JTAG_TRST_b */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
