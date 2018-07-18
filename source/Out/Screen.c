#include "include.h"
#define USE_LANDSCAPE

menu_item menu_list[MENU_ITEM_COUNT];
uint8_t MENU_LAST=15;

//向液晶屏写一个8位指令
void  Lcd_WriteIndex(uint8_t Data)
{
		
		CS(LOW);
		DC(LOW);
		SPI_WriteData(Data); 		
		CS(HIGH);
}

//向液晶屏写一个8位数据
void  Lcd_WriteData(uint8_t Data)
{	
		CS(LOW);
		DC(HIGH);
		SPI_WriteData(Data); 	
		CS(HIGH);
}

void  LCD_WriteData_16Bit(uint16_t Data)
{
	CS(LOW);
	DC(HIGH);
	SPI_WriteData(Data>>8); 	//写入高8位数据
	SPI_WriteData(Data); 			//写入低8位数据
	CS(HIGH);
}

void Reset()
{
    RST(LOW);
    delay_ms(100);
    RST(HIGH);
    delay_ms(100);
}

void lcd_initial()
{
    PORT_SetPinMux(PORTD,12,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD,13,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD,14,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD,15,kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD,11,kPORT_MuxAsGpio);
    
    gpio_init(GPIOD,12,OUT,LOW);
    gpio_init(GPIOD,13,OUT,LOW);
    gpio_init(GPIOD,14,OUT,LOW);
    gpio_init(GPIOD,15,OUT,LOW);
    gpio_init(GPIOD,11,OUT,LOW);

    Reset();//Reset before LCD Init.
		
	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
#ifdef USE_LANDSCAPE

#ifdef CAR_NEW
	Lcd_WriteData(0xA8);
#else 	
	Lcd_WriteData(0x68); //竖屏C8 横屏08 A8
#endif 

#else
	Lcd_WriteData(0xC8); //竖屏C8 横屏08 A8
#endif		
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+3);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on

}

void LCD_Dir(uint8_t option)
{
    //st7735r_dir = option;
    switch(option)
    {
        case 0:
            Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
            Lcd_WriteData(0xc8);//0xc8  0xA8 0x08 0x68
    
            Lcd_WriteIndex(0x2a);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x00);
            Lcd_WriteData(128);
    
            Lcd_WriteIndex(0x2B);
            Lcd_WriteData(0x00);
            Lcd_WriteData(50);
            Lcd_WriteData(0x00);
            Lcd_WriteData(128+50);
    
            // st7735r_h   = ST7735R_H;
            // st7735r_w   = ST7735R_W;
            break;
        case 1:
            Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
            Lcd_WriteData(0xA8);//0xc8  0xA8 0x08 0x68
    
            Lcd_WriteIndex(0x2a);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x03);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x82);
    
            Lcd_WriteIndex(0x2B);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x02);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x81);
    
            // st7735r_h   = ST7735R_W;
            // st7735r_w   = ST7735R_H;
            break;
        case 2:
            Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
            Lcd_WriteData(0x08);//0xc8  0xA8 0x08 0x68
    
            Lcd_WriteIndex(0x2a);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x02);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x81);
    
            Lcd_WriteIndex(0x2B);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x03);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x82);
    
            // st7735r_h   = ST7735R_H;
            // st7735r_w   = ST7735R_W;
            break;
        case 3:
            Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
            Lcd_WriteData(0x68);//0xc8  0xA8 0x08 0x68
    
            Lcd_WriteIndex(0x2a);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x03);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x82);
    
            Lcd_WriteIndex(0x2B);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x00);
            Lcd_WriteData(0x00);
            Lcd_WriteData(128);
    
            // st7735r_h   = ST7735R_W;
            // st7735r_w   = ST7735R_H;
            break;
        default:
            break;
    }

}

/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(uint8_t x_start,uint8_t y_start,uint8_t x_end,uint8_t y_end)
{	

#ifdef  USE_LANDSCAPE               //使用横屏模式
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+3);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+1);

#else//竖屏模式	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);	
#endif
	Lcd_WriteIndex(0x2c);
}


void PutPixel(uint8_t x_start,uint8_t y_start,uint16_t color)
{
	Lcd_SetRegion(x_start,y_start,x_start+1,x_start+1);
	LCD_WriteData_16Bit(color);
}

void LCD_DrawPicture(uint8_t* img)
{
        uint8_t i,j;
        uint16_t imgtemp;
 	    for (i=0;i<120;i++){
          for (j=0;j<120;j++){
              imgtemp=GRAY_2_RGB565(img[i*188+j]);
              PutPixel(j,i,imgtemp);
          }
        }
}

void LCD_DrawPicture_Small(uint8_t* img)
{
        uint8_t i,j;
        uint16_t imgtemp;
 	    for (i=0;i<60;i++){
          for (j=0;j<94;j++){
              imgtemp=GRAY_2_RGB565(img[i*94+j]);
              PutPixel(j,i,imgtemp);
          }
        }
}

void fullfill(uint8_t startx,uint8_t starty,uint8_t endx,uint8_t endy,uint16_t color)
{
 	uint8_t i,j;
	Lcd_SetRegion(startx,starty,endx,endy);
 	for (i=starty;i<endy;i++)
    	for (j=startx;j<endx;j++)
        	PutPixel(j,i,color);
}

void Display_ASCII8X16(uint8_t x0,uint8_t y0,uint8_t *s,uint16_t bg,uint16_t fc) //x0的范围是0-15,y0的范围是0-7
{
	uint32_t length = strlen(s);
    uint8_t temp;
    if(length+x0 > 16)
        length = 16-x0;
    if(x0<16&&y0<8)
    {
        //fullfill(x0*8,y0*16,(x0+length)*8,(y0+1)*16,bg);
        for(int i = 0;i<length;i++)
        {
            Lcd_SetRegion((x0+i)*8,y0*16,(x0+i+1)*8-1,(y0+1)*16-1);

            for (int pos = 0; pos < 16; pos++)
            {
                temp = ASCII_8x16[((s[i]-0x20)*16)+pos];

                for(int t = 0; t < 8; t++)
                {

                    if(temp & 0x80)
                    {
                        LCD_WriteData_16Bit(fc);
                    }
                    else
                    {
                        LCD_WriteData_16Bit(bg);
                    }
                    temp <<= 1;
                }
            }
        }
    }
}


void Display_Number(uint8_t x,uint8_t y,uint32_t num,uint16_t bg,uint16_t fc)
{
    uint8_t buffer[10];
    sprintf(buffer,"%04d",num);
    Display_ASCII8X16(x,y,buffer,bg,fc);
}

void Display_Float(uint8_t x,uint8_t y,float num,uint16_t bg,uint16_t fc)
{
    uint8_t buffer[10];
    sprintf(buffer,"%f",num);
    Display_ASCII8X16(x,y,buffer,bg,fc);
}


int16_t windows(int16_t num,uint16_t bg,uint16_t fc)
{
    fullfill(16,48,112,80,bg);
    Display_Number(1,3,num,bg,fc);
    return 0;
}



void menu(uint8_t start,uint8_t end,uint8_t selected)
{
	uint8_t buffer[17];
	for(int i=start;i<=end;i++)
	{
		sprintf(buffer,"%s   %2d.%d",menu_list[i].item_name,(int)(menu_list[i].item_value),((int)(menu_list[i].item_value*10.0))%10);
		if(i==selected)
		{
			Display_ASCII8X16(0,i-start,buffer,RED,GREEN);
		}else{
			Display_ASCII8X16(0,i-start,buffer,BLACK,WHITE);
		}
	}
}

void menu_from_flash()
{
  float values[16] ={0};
  flash_read(1,sizeof(values),(uint8_t*)&values);
  for(int i=0;i<16;i++)
  {
    menu_list[i].item_value = values[i];
  }
}

void flash_from_menu()
{
  float values[16]={0};
  for(int i=0;i<16;i++)
  {
    values[i] = menu_list[i].item_value;
  }
  
  flash_write(1,sizeof(values),(uint8_t*)&values);
}

void menu_in()
{
    memset(menu_list,0,sizeof(menu_list));
    sprintf(menu_list[0].item_name,"STEESP");
    sprintf(menu_list[1].item_name,"STEESD");
    sprintf(menu_list[2].item_name,"STEEBP");
    sprintf(menu_list[3].item_name,"STEEBD");
    sprintf(menu_list[4].item_name,"STEERP");
    sprintf(menu_list[5].item_name,"STEERD");
    sprintf(menu_list[6].item_name,"MOTOLP");
    sprintf(menu_list[7].item_name,"MOTOLI");
    sprintf(menu_list[8].item_name,"MOTOLD");
    sprintf(menu_list[9].item_name,"MOTORP");
    sprintf(menu_list[10].item_name,"MOTORI");
    sprintf(menu_list[11].item_name,"MOTORD");
    sprintf(menu_list[12].item_name,"DIV   ");
    sprintf(menu_list[13].item_name,"LEFT  ");
    sprintf(menu_list[14].item_name,"RIGHT ");
    sprintf(menu_list[15].item_name,"GSPEED");
}

void menu_out()
{
    GV_steerControlT.PD.Steer_P_Small=menu_list[0].item_value;
    GV_steerControlT.PD.Steer_D_Small=menu_list[1].item_value;
    GV_steerControlT.PD.Steer_P_Big = menu_list[2].item_value;
    GV_steerControlT.PD.Steer_D_Big = menu_list[3].item_value;
    GV_steerControlT.PD.Steer_P=menu_list[4].item_value; 
    GV_steerControlT.PD.Steer_D=menu_list[5].item_value;
    GV_speedControlT.Pid[0].PidCore.Kp=menu_list[6].item_value; 
    GV_speedControlT.Pid[0].PidCore.Ki=menu_list[7].item_value; 
    GV_speedControlT.Pid[0].PidCore.Kd=menu_list[8].item_value; 
    GV_speedControlT.Pid[1].PidCore.Kp=menu_list[9].item_value; 
    GV_speedControlT.Pid[1].PidCore.Ki=menu_list[10].item_value; 
    GV_speedControlT.Pid[1].PidCore.Kd=menu_list[11].item_value;
    STEER_MIDDLE=(uint16_t)menu_list[12].item_value;
	STEER_PWM_MAX=(uint16_t)menu_list[13].item_value;
	STEER_PWM_MIN=(uint16_t)menu_list[14].item_value;
    g_Speed = (uint16_t)menu_list[15].item_value;
}

void menu_from_code()
{
    menu_list[0].item_value = GV_steerControlT.PD.Steer_P_Small;
    menu_list[1].item_value = GV_steerControlT.PD.Steer_D_Small;
    menu_list[2].item_value = GV_steerControlT.PD.Steer_P_Big;
    menu_list[3].item_value = GV_steerControlT.PD.Steer_D_Big;
    menu_list[4].item_value = GV_steerControlT.PD.Steer_P;
    menu_list[5].item_value = GV_steerControlT.PD.Steer_D;
    menu_list[6].item_value = GV_speedControlT.Pid[0].PidCore.Kp;
    menu_list[7].item_value = GV_speedControlT.Pid[0].PidCore.Ki;
    menu_list[8].item_value = GV_speedControlT.Pid[0].PidCore.Kd;
    menu_list[9].item_value = GV_speedControlT.Pid[1].PidCore.Kp;
    menu_list[10].item_value = GV_speedControlT.Pid[1].PidCore.Ki;
    menu_list[11].item_value = GV_speedControlT.Pid[1].PidCore.Kd;
    menu_list[12].item_value = STEER_MIDDLE;
    menu_list[13].item_value =STEER_PWM_MAX;
    menu_list[14].item_value =STEER_PWM_MIN;
    menu_list[15].item_value =g_Speed;
}

void display_menu()
{
  
  int selected = 0;
  
  menu_in();
  fullfill(0,0,128,128,BLACK);
  Display_ASCII8X16(2,3,"CODE  FLASH",BLACK,WHITE);
  while(1)
  {
    
    if(READ_LEFT)
    {
    delay_ms(20);
    if(READ_LEFT){
      menu_from_code();
      Display_ASCII8X16(2,3,"CODE",RED,WHITE);
      delay_ms(500);
      break;
      }
    }
    if(READ_RIGHT)
    {  
    delay_ms(20);
    if(READ_RIGHT){
      menu_from_flash();
      Display_ASCII8X16(8,3,"FLASH",RED,WHITE);
      delay_ms(500);
      break;
      }
    }
  }
  while(1){
    if(KEY_UP){
      delay_ms(10);
      if(KEY_UP){
        delay_ms(100);
        selected -= 1;
        if(selected<0)
          selected = MENU_LAST;
      }
    }
    if(KEY_DOWN){
      delay_ms(10);
      if(KEY_DOWN){
        delay_ms(100);
        selected = (selected+1)%(MENU_LAST+1);
      }
    }
    if(KEY_LEFT)
    {
      delay_ms(10);
      if(KEY_LEFT){
        delay_ms(100);
        if(selected<=11)
          menu_list[selected].item_value -= 0.1;
        else{
          menu_list[selected].item_value -= 1;

          if(menu_list[12].item_value>menu_list[13].item_value)
              menu_list[12].item_value=menu_list[14].item_value;
            SteerSet((uint16_t)menu_list[12].item_value);
        }
      }
        
    }
    if(KEY_RIGHT)
    {
      delay_ms(10);
      if(KEY_RIGHT){
        delay_ms(100);
          if(selected<=11)
            menu_list[selected].item_value += 0.1;
          else
          {
            menu_list[selected].item_value += 1;
			
            if(menu_list[12].item_value>menu_list[13].item_value)
              menu_list[12].item_value=menu_list[14].item_value;
            SteerSet((uint16_t)menu_list[12].item_value);
          }
        }
    }

	if(READ_LEFT)
		break;
   	if(READ_RIGHT)
	{
		DISPLAY_FLAG=1;
        break;
	}	

    if(selected<=7)
      menu(0,7,selected);
    else
      menu(selected-7,selected,selected);
  } 
    
  menu_out();
  flash_from_menu();
  fullfill(0,0,128,128,BLACK);
  Display_ASCII8X16(5,3,"RUN",BLACK,WHITE);
  delay_ms(500);
}






















































uint8_t const ASCII_8x16[1536] =  // 96 X 16 = 1536
                                        // ASCII字符范围为[32,127] = 96个字符,每个字符要用16个字节来表示  所以有96X16=1536个字节
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x66, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x18, 0x7C, 0xC6, 0xC2, 0xC0, 0x7C, 0x06, 0x86, 0xC6, 0x7C, 0x18, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC2, 0xC6, 0x0C, 0x18, 0x30, 0x60, 0xC6, 0x86, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x6C, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xCE, 0xD6, 0xD6, 0xE6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x3C, 0x06, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x0E, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x60, 0xC0, 0xC0, 0xFC, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xC6, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x06, 0x0C, 0x78, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0xC2, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xDE, 0xC6, 0xC6, 0x66, 0x3A, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE6, 0x66, 0x6C, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xDE, 0x7C, 0x0C, 0x0E, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x60, 0x38, 0x0C, 0x06, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7E, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC6, 0xC6, 0x6C, 0x6C, 0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xC6, 0x86, 0x0C, 0x18, 0x30, 0x60, 0xC2, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0x60, 0x60, 0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0xDC, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x3C, 0x6C, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xCC, 0x78, 0x00,
    0x00, 0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x06, 0x00, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x00,
    0x00, 0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFE, 0xD6, 0xD6, 0xD6, 0xD6, 0xD6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x76, 0x62, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x60, 0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x38, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCC, 0x18, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00
};
