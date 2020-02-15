#include "stm32f0xx.h"                  // Device header
#include "defines.h"
#include "delay.h"
#include "ssd1306.h"
#include "i2c.h"

int main(void)
{
	system_clock();
	init_delay();
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	GPIOA->MODER |= GPIO_MODER_0_OUT | GPIO_MODER_1_OUT;
	GPIOA_OTYPER |= GPIO_OTYPER_0_OD | GPIO_OTYPER_1_OD;
	

	GPIOA_MODER |= GPIO_MODER_9_AF | GPIO_MODER_10_AF;
	GPIOA_OTYPER |= GPIO_OTYPER_10_OD | GPIO_OTYPER_9_OD;
	GPIOA_AFRH |= GPIO_AFRH_9_A4 | GPIO_AFRH_10_A4;
	GPIOA_OSPEEDR |= GPIO_OSPEEDR_10_FAS | GPIO_OSPEEDR_9_FAS;
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->CFGR3 |= RCC_CFGR3_I2C1SW;
	I2C1->TIMINGR = (uint32_t)0x10805E89;
	I2C1->CR1 |= I2C_CR1_PE;
	delay_ms(10);
	ssd1306_init();
	ssd1306_flood(0x00);
	ssd1306_string(0,0,"i2c scan");
	long n=0,tout=0;
	uint16_t temp_h, temp_l;
	I2C1->CR2 = (1 << 16)| 0xD0 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = 107;
	I2C1->CR2 = (1 << 16)| 0xD0 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = (1<<2)|(1<<5);
	while(1)
	{
	I2C1->CR2 = (1 << 16)| 0xD0 | I2C_CR2_START | I2C_CR2_AUTOEND;
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = 65;
	I2C1->CR2 = (2 << 16)| 0xD0 | I2C_CR2_START | I2C_CR2_AUTOEND | (1<<10);
	while(!(I2C1->ISR & I2C_ISR_RXNE));
	temp_h=I2C1->RXDR;
	while(!(I2C1->ISR & I2C_ISR_RXNE));
	temp_l=I2C1->RXDR;
	double temp = ((temp_h<<8)+temp_l)/340+36.53;
	ssd1306_float(0,9,temp,3);
		ssd1306_num(0,18,temp_h);
		delay_ms(100);
	}

	
	while(1)
	{
	}
}