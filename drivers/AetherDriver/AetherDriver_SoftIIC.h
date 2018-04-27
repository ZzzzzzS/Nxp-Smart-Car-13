#ifndef __AETHER_SOFTIIC__
#define __AETHER_SOFTIIC__

#define byte        unsigned char


#define SCL_set(x)  gpio_write(GPIOC,10U,x)
#define SDA_set(x)  gpio_write(GPIOC,11,x)

#define SCL_dir_out  GPIOC->PDDR |= (1U<<10U)
#define SCL_dir_in   GPIOC->PDDR &= ~(1U<<10U)
#define SDA_dir_out  GPIOC->PDDR |= (1U<<11U)
#define SDA_dir_in   GPIOC->PDDR &= ~(1U<<11U)
#define SCL_read    gpio_read(GPIOC,10U)
#define SDA_read    gpio_read(GPIOC,11U)


extern void I2C_WriteByte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
extern unsigned char I2C_ReadByte(unsigned char SlaveAddress,unsigned char REG_Address);
extern signed char I2Creceive(void);
extern void I2Csend(byte data);
extern void I2Csendack(char ack);
extern void I2Crecack();
extern void I2Cstop(void);
extern void I2Cstart(void);
extern void iic_init(void);
extern void somenop();

#endif