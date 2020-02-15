#include "stm32f0xx.h"                  // Device header
#include "defines.h"
#include "spi.h"
#include "delay.h"

void spi_init(uint16_t mode, uint16_t prescaler, uint16_t direction)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	delay_ms(1);
	GPIOA_MODER |= GPIO_MODER_5_AF | GPIO_MODER_6_AF | GPIO_MODER_7_AF;
	GPIOA_AFRL |= GPIO_AFRL_5_A0 | GPIO_AFRL_6_A0 | GPIO_AFRL_7_A0;
	
	SPI1_CR1 |= direction | SPI_CR1_MOD_MS | mode | SPI_CR1_NSS_S | prescaler;
	SPI1_CR2 |= SPI_CR2_DS_8B | SPI_CR2_FRXTH;
	SPI1_CR1 |= SPI_CR1_SPE;
	
	
}
void spi_send(uint8_t data)
{
	while(!(SPI1->SR & SPI_SR_TXE));
	SPI1_DR8 = data;
}
uint8_t spi_recv(void)
{
	#ifdef SEND_BYTE_BEFORE_RECV
	  while(!(SPI1->SR & SPI_SR_TXE));
	  spi_send(BYTE_BEFORE_RECV);
	#endif
	
	while(!(SPI1->SR & SPI_SR_RXNE));
	return (uint8_t)SPI1->DR;
	
}
uint8_t spi_send_recv(uint8_t data)
{
	while(!(SPI1->SR & SPI_SR_TXE));
	SPI1_DR8 = data;
	while(!(SPI1->SR & SPI_SR_RXNE));
	return (uint8_t)SPI1->DR;
}
