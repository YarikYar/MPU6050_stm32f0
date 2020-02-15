#include "stm32f0xx.h"
#include "defines.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssdfont.h"
#include "math.h"
#include "i2c.h"


void ssd1306_cmd(uint8_t cmd)
{
	#ifdef HARD_SPI
	I2C1->CR2 = (2 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (0<<6);
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = cmd;
	#endif
	#ifndef HARD_SPI
	i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte((0<<6));
	i2c_wbyte(cmd);
	i2c_stop();
	#endif
	
}

void ssd1306_dat(uint8_t dat)
{
	#ifdef HARD_SPI
	I2C1->CR2 = (2 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = 0x40;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = dat;
	#endif
	#ifndef HARD_SPI
	i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte(0x40);
	i2c_wbyte(dat);
	i2c_stop();
	#endif
}

void ssd1306_cmd_arg(uint8_t cmd, uint8_t arg)
{
	#ifdef HARD_SPI
	I2C1->CR2 = (3 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (0<<6);
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = cmd;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = arg; 
	#endif
	#ifndef HARD_SPI
	i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte((0<<6));
	i2c_wbyte(cmd);
	i2c_wbyte(arg);
	i2c_stop();
	#endif
}

void ssd1306_setContrast(uint8_t contrast)
{
	ssd1306_cmd_arg(SSD1306_CMD_SetContrast, contrast);
}

void ssd1306_setXY(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1)
{
	#ifdef HARD_SPI
	I2C1->CR2 = (4 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (0<<6);
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = 0x21;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = x;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = x1;
	
	I2C1->CR2 = (4 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (0<<6);
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = 0x22;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = y;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = y1; 
	#endif
	#ifndef HARD_SPI
	i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte((0<<6));
	i2c_wbyte(0x21);
	i2c_wbyte(x);
	i2c_wbyte(x1);
	i2c_stop();
	
		i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte((0<<6));
	i2c_wbyte(0x22);
	i2c_wbyte(y);
	i2c_wbyte(y1);
	i2c_stop();
	#endif
}

void ssd1306_flood(uint8_t color)
{
	ssd1306_setXY(0,0,127,63);
	#ifdef HARD_SPI
	for(int i =0; i < 4; i++)
	{
	I2C1->CR2 = (255 << 16)| 0x78 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (0<<6);
		for(int y = 0; y < 255; y++)
		{
			while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = color;
		}
	}
	#endif
	#ifndef HARD_SPI
	i2c_start();
	i2c_wbyte(0x78);
	i2c_wbyte(0x40);
	for(int i = 0; i < 1024; i++) i2c_wbyte(color);
	i2c_stop();
	#endif
}

void ssd1306_char(char to_print)
{
	uint8_t i;
	if(to_print > 128) to_print -= 64;
	for (i = 0; i < 5; i++ )
		{
			ssd1306_dat((font[to_print-32][i]));
		}
		ssd1306_dat(0x00);
	}

	void ssd1306_string(uint8_t x, uint8_t y, char* to_print)
{
	ssd1306_setXY(x,y,127,64);
	while(*to_print)
	{
		ssd1306_char(*to_print++);
	}
}

void ssd1306_num(uint8_t x, uint8_t y, long num)
{
	char buf[25];
	char _buf[25];
	int i = 0;
	uint8_t is_neg = 0;
	int c = 0;
	if(num == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		ssd1306_string(x,y,buf);
		return;
	}
	else if(num < 0)
	{
		is_neg = 1;
		num = -num;
	}
	while (num>0)
			{
				buf[c]=48+(num % 10);
				c++;
				num=(num-(num % 10))/10;
			}
		buf[c] = 0;
			if(is_neg) 
			{
				ssd1306_string(x,y,"-");
				x +=6;
			}
			for (i=0; i<c; i++)
			{
				_buf[i]=buf[c-i-1];
			}
			_buf[c] = 0;
			ssd1306_string(x,y,_buf);
}

void ssd1306_float(uint8_t x, uint8_t y, float num, uint8_t num_dig)
{
	volatile uint32_t integer, fractional;
	float fract;
	uint16_t mul = 1, digits = 1, int1 = 0;
	integer = (uint32_t)(num);
	int1=integer;
	while((int1/10))
	{
		digits++;
		int1/=10;
	}
	fract = num - integer;
	mul = pow(10, num_dig);
	fractional =  fract*mul;
	ssd1306_num(x,y,integer);
	ssd1306_char('.');
	ssd1306_num(x+(digits*6)+6, y, fractional);
}

void ssd1306_img(const char img[])
{
	ssd1306_setXY(0,0,127,8);
	for(uint16_t i = 0; i < 128; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,9,127,9);
	for(uint16_t i = 128; i <256; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,18,127,18);
	for(uint16_t i = 256; i <384; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,27,127,27);
	for(uint16_t i = 256; i <512; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,36,127,36);
	for(uint16_t i = 512; i <640; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,45,127,45);
	for(uint16_t i = 640; i <768; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,54,127,54);
	for(uint16_t i = 768; i <896; i++) ssd1306_dat(img[i]);
	ssd1306_setXY(0,63,127,63);
	for(uint16_t i = 896; i <1024; i++) ssd1306_dat(img[i]);
}

void ssd1306_clr(void)
{
	ssd1306_flood(0x00);
}

void ssd1306_hex(uint8_t x, uint8_t y, uint8_t hexdig)
{
	ssd1306_string(x,y,"0x");
  ssd1306_char((hexdig >> 4) + (((hexdig >> 4) >= 10) ? ('A' - 10) : '0'));
  ssd1306_char((hexdig & 0x0F) + (((hexdig & 0x0F) >= 10) ? ('A' - 10) : '0'));
}


void ssd1306_init(void)
{
	ssd1306_cmd(SSD1306_CMD_Sleep);
	ssd1306_cmd_arg(SSD1306_CMD_SetMultiplexRatio, 0x3F);
	ssd1306_cmd_arg(SSD1306_CMD_SetDisplayOffset,0);
	ssd1306_cmd_arg(SSD1306_CMD_SetDisplayStartLine, 0);
	ssd1306_cmd(0xA1);
	ssd1306_cmd(0xC8);
	ssd1306_cmd_arg(SSD1306_CMD_SetMemAdressingMode,0);
	ssd1306_cmd(0x21);
	ssd1306_cmd(0x00);
	ssd1306_cmd(0x7F);
	ssd1306_cmd(0x22);
	ssd1306_cmd(0x00);
	ssd1306_cmd(0x07);
	ssd1306_cmd_arg(SSD1306_CMD_SetVCOMHDeselectLevel, 0x00);
	ssd1306_cmd_arg(SSD1306_CMD_SetDisplayClockDivider,0x80);
	ssd1306_cmd_arg(0x8D,0x14);
	ssd1306_cmd(SSD1306_CMD_AllPixRAM);
	ssd1306_cmd(SSD1306_CMD_Wake);
}
