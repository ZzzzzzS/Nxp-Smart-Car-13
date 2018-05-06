#ifndef __AETHER_CAMERA__
#define __AETHER_CAMERA__

#define MT9V034_SLAVE_ADDRESS                   (0x5C)
#define MT9V034_MAX_HEIGHT                      (480)
#define MT9V034_MAX_WIDTH                       (752)
#define MT9V034_CHIP_VERSION                    (0x00)
#define     MT9V034_DEFAULT_VERSION                     (0x1324)
#define MT9V034_COL_START                       (0x01)
#define     MT9V034_COL_START_MIN                       (1)
#define     MT9V034_COL_START_MAX                       (752)
#define MT9V034_ROW_START                       (0x02)
#define     MT9V034_ROW_START_MIN                       (4)
#define     MT9V034_ROW_START_MAX                       (482)
#define MT9V034_WINDOW_HEIGHT                   (0x03)
#define     MT9V034_WINDOW_HEIGHT_MIN                   (1)
#define     MT9V034_WINDOW_HEIGHT_MAX                   (480)
#define MT9V034_WINDOW_WIDTH                    (0x04)
#define     MT9V034_WINDOW_WIDTH_MIN                    (1)
#define     MT9V034_WINDOW_WIDTH_MAX                    (752)
#define MT9V034_HORIZONTAL_BLANKING             (0x05)
#define     MT9V034_HORIZONTAL_BLANKING_MIN             (43)
#define     MT9V034_HORIZONTAL_BLANKING_MAX             (1023)
#define MT9V034_VERTICAL_BLANKING               (0x06)
#define     MT9V034_VERTICAL_BLANKING_MIN               (4)
#define     MT9V034_VERTICAL_BLANKING_MAX               (3000)
#define MT9V034_CHIP_CONTROL                    (0x07)
#define     MT9V034_CHIP_CONTROL_MASTER_MODE            (1<<3)
#define     MT9V034_CHIP_CONTROL_DOUT_ENABLE            (1<<7)
#define     MT9V034_CHIP_CONTROL_SEQUENTIAL             (1<<8)
#define MT9V034_SHUTTER_WIDTH1                  (0x08)
#define MT9V034_SHUTTER_WIDTH2                  (0x09)
#define MT9V034_SHUTTER_WIDTH_CONTROL           (0x0A)
#define MT9V034_TOTAL_SHUTTER_WIDTH             (0x0B)
#define     MT9V034_TOTAL_SHUTTER_WIDTH_MIN             (1)
#define     MT9V034_TOTAL_SHUTTER_WIDTH_MAX             (32767)
#define MT9V034_RESET                           (0x0C)
#define MT9V034_READ_MODE                       (0x0D)
#define     MT9V034_READ_MODE_ROW_BIN_2                 (1<<0)
#define     MT9V034_READ_MODE_ROW_BIN_4                 (1<<1)
#define     MT9V034_READ_MODE_COL_BIN_2                 (1<<2)
#define     MT9V034_READ_MODE_COL_BIN_4                 (1<<3)
#define     MT9V034_READ_MODE_ROW_FLIP                  (1<<4)
#define     MT9V034_READ_MODE_COL_FLIP                  (1<<5)
#define     MT9V034_READ_MODE_DARK_COLS                 (1<<6)
#define     MT9V034_READ_MODE_DARK_ROWS                 (1<<7)
#define MT9V034_PIXEL_OPERATION_MODE            (0x0F)
#define     MT9V034_PIXEL_OPERATION_MODE_COLOR          (1<<2)
#define     MT9V034_PIXEL_OPERATION_MODE_HDR            (1<<6)
#define MT9V034_ANALOG_GAIN                     (0x35)
#define     MT9V034_ANALOG_GAIN_MIN                     (16)
#define     MT9V034_ANALOG_GAIN_MAX                     (64)
#define MT9V034_MAX_ANALOG_GAIN                 (0x36)
#define     MT9V034_MAX_ANALOG_GAIN_MAX                 (127)
#define MT9V034_FRAME_DARK_AVERAGE              (0x42)
#define MT9V034_DARK_AVG_THRESH                 (0x46)
#define     MT9V034_DARK_AVG_LOW_THRESH_MASK            (255<<0)
#define     MT9V034_DARK_AVG_LOW_THRESH_SHIFT           (0)
#define     MT9V034_DARK_AVG_HIGH_THRESH_MASK           (255<<8)
#define     MT9V034_DARK_AVG_HIGH_THRESH_SHIFT          (8)
#define MT9V034_ROW_NOISE_CORR_CONTROL          (0x70)
#define     MT9V034_ROW_NOISE_CORR_ENABLE               (1<<5)
#define     MT9V034_ROW_NOISE_CORR_USE_BLK_AVG          (1<<7)
#define MT9V034_PIXEL_CLOCK                     (0x72)
#define     MT9V034_PIXEL_CLOCK_INV_LINE                (1<<0)
#define     MT9V034_PIXEL_CLOCK_INV_FRAME               (1<<1)
#define     MT9V034_PIXEL_CLOCK_XOR_LINE                (1<<2)
#define     MT9V034_PIXEL_CLOCK_CONT_LINE               (1<<3)
#define     MT9V034_PIXEL_CLOCK_INV_PXL_CLK             (1<<4)
#define MT9V034_TEST_PATTERN                    (0x7F)
#define     MT9V034_TEST_PATTERN_DATA_MASK              (1023<<0)
#define     MT9V034_TEST_PATTERN_DATA_SHIFT             (0)
#define     MT9V034_TEST_PATTERN_USE_DATA               (1<<10)
#define     MT9V034_TEST_PATTERN_GRAY_MASK              (3<<11)
#define     MT9V034_TEST_PATTERN_GRAY_NONE              (0<<11)
#define     MT9V034_TEST_PATTERN_GRAY_VERTICAL          (1<<11)
#define     MT9V034_TEST_PATTERN_GRAY_HORIZONTAL        (2<<11)
#define     MT9V034_TEST_PATTERN_GRAY_DIAGONAL          (3<<11)
#define     MT9V034_TEST_PATTERN_ENABLE                 (1<<13)
#define     MT9V034_TEST_PATTERN_FLIP                   (1<<14)
#define MT9V034_AEC_AGC_ENABLE                  (0xAF)
#define     MT9V034_AEC_ENABLE                          (1<<0)
#define     MT9V034_AGC_ENABLE                          (1<<1)
#define MT9V034_THERMAL_INFO                    (0xC1)
#define MT9V034_ANALOG_CTRL                     (0xC2)
#define     MT9V034_ANTI_ECLIPSE_ENABLE                 (1<<7)
#define MT9V034_COARSE_SHUTTER_WIDTH_MIN        (0xAC)
#define MT9V034_COARSE_SHUTTER_WIDTH_MAX        (0xAD)
#define MT9V034_WINDOW_HEIGHT_A                 (0x03)
#define MT9V034_WINDOW_WIDTH_A                  (0x04)
#define MT9V034_HORIZONTAL_BLANKING_A           (0x05)
#define MT9V034_VERTICAL_BLANKING_A             (0x06)
#define MT9V034_COARSE_SHUTTER_WIDTH_TOTAL_A    (0x0B)
#define MT9V034_ANALOG_GAIN_CONTROL             (0x35)
#define MT9V034_MAX_GAIN                        (0xAB)
#define MT9V034_FINE_SHUTTER_WIDTH_TOTAL_A      (0xD5)

#define MT9V034_H                       (120)
#define MT9V034_W                       (188)
#define MT9V034_SIZE                    (MT9V034_H*MT9V034_W)
#define MT9V034_DMA_CHANNEL             (DMA0_DMA16_IRQn)

extern bool MT9V034_CaptureAccomplished;
extern volatile uint8_t MT9V034_IMGBUFF_A[MT9V034_H][MT9V034_W];
extern volatile uint8_t MT9V034_IMGBUFF_B[MT9V034_H][MT9V034_W];
extern volatile uint8_t* IMG_NOW;
extern uint16_t MT9V034_ReadReg(uint8_t SlaveAddr, uint8_t RegAddr);
extern void MT9V034_WriteReg(uint8_t SlaveAddr, uint8_t RegAddr, uint16_t RegVal);
extern void MT9V034_Reset(uint8_t MT9V034_I2C_ADDR);
extern void MT9V034_SetReservedReg(uint8_t MT9V034_I2C_ADDR);
extern void MT9V034_SetAutoExposure(uint8_t MT9V034_I2C_ADDR, bool enable);
extern void MT9V034_SetFrameResolution(uint8_t MT9V034_I2C_ADDR, uint16_t width, uint16_t height);
extern bool MT9V034_Reg_Init(uint8_t MT9V034_I2C_ADDR);
extern void MT9V034_Init(void);
extern __ramfunc void MT9V034_FrameValid_Callback(uint32_t ISFR_FLAG);
extern __ramfunc void MT9V034_LineValid_Callback(uint16_t line,uint8_t* IMG);
extern __ramfunc void MT9V034_DMA_Callback(void);
extern void MT9V034_DMA_Init(uint8_t* pMT9V032_IMG_Buff);
extern void Camera_ajust();

#endif