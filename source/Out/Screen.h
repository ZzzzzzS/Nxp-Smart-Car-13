#ifndef __AETHER_SCREEN__
#define __AETHER_SCREEN__

#define MENU_ITEM_COUNT 32

typedef struct{
	char item_name[10];
	float item_value;
}menu_item;

extern menu_item menu_list[MENU_ITEM_COUNT];
extern uint8_t const ASCII_8x16[1536];


extern void display_menu();
extern void Lcd_WriteIndex(uint8_t Data);
extern void Lcd_WriteData(uint8_t Data);
extern void LCD_WriteData_16Bit(uint16_t Data);
extern void Reset();
extern void lcd_initial();
extern void LCD_Dir(uint8_t option);
extern void LCD_DrawPicture(uint8_t* img);
extern void LCD_DrawPicture_Small(uint8_t* img);
extern void Lcd_SetRegion(uint8_t x_start,uint8_t y_start,uint8_t x_end,uint8_t y_end);
extern void PutPixel(uint8_t x_start,uint8_t y_start,uint16_t color);
extern void fullfill(uint8_t startx,uint8_t starty,uint8_t endx,uint8_t endy,uint16_t color);
extern void Display_ASCII8X16(uint8_t x0,uint8_t y0,uint8_t *s,uint16_t bg,uint16_t fc);
extern void Display_Number(uint8_t x,uint8_t y,uint32_t num,uint16_t bg,uint16_t fc);
extern void Display_Float(uint8_t x,uint8_t y,float num,uint16_t bg,uint16_t fc);
extern int16_t windows(int16_t num,uint16_t bg,uint16_t fc);

#endif
