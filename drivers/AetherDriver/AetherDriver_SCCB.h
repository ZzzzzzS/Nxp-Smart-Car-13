#ifndef __AETHER_SCCB__
#define __AETHER_SCCB__

#define SCCB_BASE       GPIOE
#define SCCB_PORT_BASE  PORTE
#define SCCB_SCL        19U
#define SCCB_SDA        18U

#define SCL_H()         gpio_write(SCCB_BASE,SCCB_SCL,HIGH);
#define SCL_L()         gpio_write(SCCB_BASE,SCCB_SCL,LOW);
                                    
#define SDA_H()         SCCB_BASE->PSOR = 1U << SCCB_SDA;
#define SDA_L()         SCCB_BASE->PCOR = 1U << SCCB_SDA;
#define SDA_IN()        ((SCCB_BASE->PDIR&(1U<<SCCB_SDA))>>SCCB_SDA)
#define SDA_DDR_OUT()   SCCB_BASE->PDDR |= (1U<<SCCB_SDA)
#define SDA_DDR_IN()    SCCB_BASE->PDDR &= ~(1U<<SCCB_SDA)

#define SCCB_DELAY()    CPU_Delay(200);




extern void CPU_Delay(volatile uint32_t cnt);
extern int16_t SCCB_WriteByte_soft(uint8_t SlaveAddress, uint8_t REG_Address, uint16_t REG_data);
extern int16_t SCCB_ReadByte_soft(uint8_t SlaveAddress, uint8_t REG_Address);
extern void SCCB_SendByte(uint8_t SendByte);
extern void SCCB_Stop(void);
extern int SCCB_WaitAck(void);
extern void SCCB_Start(void);
extern int SCCB_ReceiveByte(void);
extern void SCCB_Init();
#endif