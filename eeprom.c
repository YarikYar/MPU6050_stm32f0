#include "stm32f0xx.h"
#include "defines.h"
#include "eeprom.h"
#include "delay.h"


#define ADDR 0xA0

void ee_wbyte(uint16_t addr, uint8_t data)
{
	I2C1->CR2 = (3 << 16)| ADDR | I2C_CR2_START | I2C_CR2_AUTOEND;
		while(!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = (addr>>8);
		while(!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = (uint8_t)addr;
		while(!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = data;
	delay_ms(4);
}

uint8_t ee_rbyte(uint16_t addr)
{
	uint8_t data;
	I2C1->CR2 = (2 << 16)| ADDR | I2C_CR2_START ;
	
    while(!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = (addr>>8);
    while(!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = (uint8_t)addr;
		I2C1->CR2 = (1 << 16)| ADDR | I2C_CR2_START | (1<<10);
        while((I2C1->ISR & I2C_ISR_RXNE) != I2C_ISR_RXNE);
        data = I2C1->RXDR;
	return data;
}

void ee_clear(void)
{
	int cnt;
	for(cnt = 0; cnt < 4096; cnt++)
	{
		ee_wbyte(cnt, 0x00);
		delay_ms(5);
	}
}

