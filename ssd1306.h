#ifndef SSD1306_H
#define SSD1306_H

//#define HARD_SPI

#define SSD1306_CMD_SetContrast                 0x81
#define SSD1306_CMD_AllPixRAM                   0xA4
#define SSD1306_CMD_AllPixOn                    0xA5
#define SSD1306_CMD_SetInverseOff               0xA6
#define SSD1306_CMD_SetInverseOn                0xA7
#define SSD1306_CMD_Sleep                       0xAE
#define SSD1306_CMD_Wake                        0xAF

//  оманды из раздела Scrolling
#define SSD1306_CMD_DeactivateScroll            0x2E

//  оманды из раздела Addressing Setting
//  оманда выбора режима автосдвига указател€ в пам€ти кадра
#define SSD1306_CMD_SetMemAdressingMode         0x20    
//  оманды выбора диапазона изменени€ страницы и колонки при автосдвиге указател€ в пам€ти кадра
// ѕримен€етс€ дл€ режимов автосдвига SSD1306_Adressing_Horizontal и SSD1306_Adressing_Vertical
#define SSD1306_CMD_SetColumnAddr               0x21
#define SSD1306_CMD_SetPageAddr                 0x22
//  оманды выбора страницы и диапазона изменени€ колонки при автосдвиге указател€ в пам€ти кадра
// ѕримен€етс€ дл€ режима автосдвига SSD1306_Adressing_Page
#define SSD1306_CMD_PageAddrMode_SetPage        0xB0
#define SSD1306_CMD_PageAddrMode_StartColumnLo  0x00
#define SSD1306_CMD_PageAddrMode_StartColumnHi  0x10

//  оманды из раздела Hardware Configuration
#define SSD1306_CMD_SetDisplayStartLine         0x40
#define SSD1306_CMD_SetSegmentRemap             0xA0
#define SSD1306_CMD_SetMultiplexRatio           0xA8
#define SSD1306_CMD_SetCOMoutScanDirection      0xC0 
#define SSD1306_CMD_SetDisplayOffset            0xD3
#define SSD1306_CMD_SetCOMPinsConfig            0xDA
  
//  оманды из раздела Timing & Driving Scheme Setting
#define SSD1306_CMD_SetDisplayClockDivider      0xD5
#define SSD1306_CMD_SetPrechargePeriod          0xD9
#define SSD1306_CMD_SetVCOMHDeselectLevel       0xDB

//  оманды из раздела Charge Pump
#define SSD1306_CMD_ChargePumpSetting           0x8D

void ssd1306_cmd(uint8_t cmd);
void ssd1306_dat(uint8_t dat);
void ssd1306_cmd_arg(uint8_t cmd, uint8_t arg);
void ssd1306_setContrast(uint8_t contrast);
void ssd1306_setXY(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1);
void ssd1306_flood(uint8_t color);
void ssd1306_char(char to_print);
	void ssd1306_string(uint8_t x, uint8_t y, char* to_print);
	void ssd1306_num(uint8_t x, uint8_t y, long num);
	void ssd1306_float(uint8_t x, uint8_t y, float num, uint8_t num_dig);
	void ssd1306_img(const char img[]);
	void ssd1306_clr(void);
	void ssd1306_hex(uint8_t x, uint8_t y, uint8_t hexdig);
	void ssd1306_init(void);



	
#endif
