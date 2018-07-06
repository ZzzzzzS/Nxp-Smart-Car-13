#include "include.h"


/*!
 *  @brief      山外多功能调试助手上位机，虚拟示波器显示函数
 *  @param      wareaddr    波形数组起始地址
 *  @param      waresize    波形数组占用空间的大小
 *  @since      v5.0
*  Sample usage:
             具体用法参考这帖子:
            【山外资料】陀螺仪和加速度 上位机显示例程 - 智能车资料区
             http://vcan123.com/forum.php?mod=viewthread&tid=6253&ctid=27
 */
void SendAdValue(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    UART_WriteBlocking(UART4,cmdf,sizeof(cmdf));       //发送数据
    UART_WriteBlocking(UART4,wareaddr,waresize);       //发送数据
    UART_WriteBlocking(UART4,cmdr,sizeof(cmdr));       //发送数据

}

void SendAdValueUsingAetherUper(void *wareaddr, uint32_t waresize)
{
    uint8_t cmdf[2] = {0xaa, 0x10};    //串口调试 使用的前命令
    uint8_t cmdr[1] = {0xfc};    //串口调试 使用的后命令

    uint8_t* dataToSend;
    dataToSend=wareaddr; //数组越界后可能出现乱码

    UART_WriteBlocking(UART4,cmdf,sizeof(cmdf));       //发送数据
    UART_WriteBlocking(UART4,dataToSend,sizeof(24));       //发送数据
    UART_WriteBlocking(UART4,cmdr,sizeof(cmdr));       //发送数据

}