#ifndef __AETHER_SPI__
#define __AETHER_SPI__


#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define GRAY_2_RGB565(gray)             ((uint16_t)((((uint8_t)(gray)>>3)<<11)|(((uint8_t)(gray)>>2)<<5)|((uint8_t)(gray)>>3)))

// Color definitions
#define RED  		0xf800
#define GREEN		0x07e0
#define BLUE 		0x001f
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   
#define GRAY1   0x8410      	
#define GRAY2   0x4208

#define SPI_BASE GPIOD
#define SPI_SCL_PIN     12U
#define SPI_SDA_PIN     13U
#define SPI_RST_PIN     14U
#define SPI_DC_PIN      15U
#define SPI_CS_PIN      11U

#define SCL(x)  if(x){SPI_BASE->PDOR |= (1U<<SPI_SCL_PIN);}else{SPI_BASE->PDOR &= ~(1U<<SPI_SCL_PIN);}        //gpio_write(GPIOD,12,x)
#define SDA(x)  if(x){SPI_BASE->PDOR |= (1U<<SPI_SDA_PIN);}else{SPI_BASE->PDOR &= ~(1U<<SPI_SDA_PIN);}        //gpio_write(GPIOD,13,x)
#define RST(x)  if(x){SPI_BASE->PDOR |= (1U<<SPI_RST_PIN);}else{SPI_BASE->PDOR &= ~(1U<<SPI_RST_PIN);}        //gpio_write(GPIOD,14,x)
#define DC(x)   if(x){SPI_BASE->PDOR |= (1U<<SPI_DC_PIN);}else{SPI_BASE->PDOR &= ~(1U<<SPI_DC_PIN);}  //gpio_write(GPIOD,15,x)
#define CS(x)   if(x){SPI_BASE->PDOR |= (1U<<SPI_CS_PIN);}else{SPI_BASE->PDOR &= ~(1U<<SPI_CS_PIN);}  //gpio_write(GPIOD,11,x)


extern void  SPI_WriteData(uint8_t Data);


#endif