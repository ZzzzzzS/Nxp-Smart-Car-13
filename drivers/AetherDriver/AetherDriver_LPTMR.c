#include "MKV58F24.h"
#include "AetherDriver_LPTMR.h"

__ramfunc void delay_us(uint16_t us)
{


    if(us == 0)
    {
        return;
    }

    OSC0_CR |= OSC_CR_ERCLKEN_MASK;                              //使能 OSCERCLK


    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;                        //使能LPT模块时钟

    LPTMR0_CSR = 0x00;                                          //先关了LPT，自动清计数器的值

    LPTMR0_CMR = (us * 50 + 16) / 32;                 //设置比较值，即延时时间

    //选择时钟源
    LPTMR0_PSR  =   ( 0
                      | LPTMR_PSR_PCS(3)          //选择时钟源： 0 为 MCGIRCLK ，1为 LPO（1KHz） ，2为 ERCLK32K ，3为 OSCERCLK
                      //| LPTMR_PSR_PBYP_MASK     //旁路 预分频/干扰滤波器 ,即不用 预分频/干扰滤波器(注释了表示使用预分频/干扰滤波器)
                      | LPTMR_PSR_PRESCALE(4)     //预分频值 = 2^(n+1) ,n = 0~ 0xF
                    );

    //使能 LPT
    LPTMR0_CSR  =  (0
                    //| LPTMR_CSR_TPS(1)        // 选择输入管脚 选择
                    //| LPTMR_CSR_TMS_MASK      // 选择脉冲计数 (注释了表示时间计数模式)
                    //| ( cfg == LPT_Falling ?  LPTMR_CSR_TPP_MASK :   0  )  //脉冲计数器触发方式选择：0为高电平有效，上升沿加1
                    | LPTMR_CSR_TEN_MASK        //使能LPT(注释了表示禁用)
                    //| LPTMR_CSR_TIE_MASK      //中断使能
                    //| LPTMR_CSR_TFC_MASK      //0:计数值等于比较值就复位；1：溢出复位（注释表示0）
                   );

    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)); //等待比较值与计数值相等，即时间到了

    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;          //清除比较标志位
}

__ramfunc void delay_ms(uint16_t ms)
{
    if(ms == 0)
    {
        return;
    }

    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;    //使能LPT模块时钟

    LPTMR0_CSR = 0x00;                      //先关了LPT，自动清计数器的值

    LPTMR0_CMR = ms;                        //设置比较值，即延时时间

    //选择时钟源
    LPTMR0_PSR  =   ( 0
                      | LPTMR_PSR_PCS(1)                  //选择时钟源： 0 为 MCGIRCLK ，1为 LPO（1KHz） ，2为 ERCLK32K ，3为 OSCERCLK
                      | LPTMR_PSR_PBYP_MASK               //旁路 预分频/干扰滤波器 ,即不用 预分频/干扰滤波器(注释了表示使用预分频/干扰滤波器)
                      //| LPTMR_PSR_PRESCALE(1)           //预分频值 = 2^(n+1) ,n = 0~ 0xF
                    );

    //使能 LPT
    LPTMR0_CSR  =  (0
                    //| LPTMR_CSR_TPS(1)        // 选择输入管脚 选择
                    //| LPTMR_CSR_TMS_MASK      // 选择脉冲计数 (注释了表示时间计数模式)
                    //| ( cfg == LPT_Falling ?  LPTMR_CSR_TPP_MASK :   0  )  //脉冲计数器触发方式选择：0为高电平有效，上升沿加1
                    | LPTMR_CSR_TEN_MASK        //使能LPT(注释了表示禁用)
                    //| LPTMR_CSR_TIE_MASK      //中断使能
                    //| LPTMR_CSR_TFC_MASK      //0:计数值等于比较值就复位；1：溢出复位（注释表示0）
                   );

    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)); //等待比较值与计数值相等，即时间到了

    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;          //清除比较标志位

    return;
}

__ramfunc void delay_s(uint16_t s)
{
    if(s==0)
        return;
    int i=0;
    for(i;i<s;i++){
        delay_ms(1000);
    }
}
