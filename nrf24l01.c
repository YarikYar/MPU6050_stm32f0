#include "stm32f0xx.h" 
#include "defines.h"
#include "spi.h"
#include "nrf24l01.h"

// LOW-LEVEL FUNCTION DEFINITIONS //

void nrf_writereg(uint8_t addr, uint8_t data)
{
	GPIOA_BSRR |= GPIO_BSRR_3_R;
	spi_send_recv(addr | W_REGISTER);
	spi_send_recv(data);
	while(SPI1->SR & SPI_SR_BSY);
	GPIOA_BSRR |= GPIO_BSRR_3_S;
}

uint8_t nrf_readreg(uint8_t addr)
{
	uint8_t data;
	GPIOA_BSRR |= GPIO_BSRR_3_R;
	spi_send_recv(addr | R_REGISTER);
	data = spi_send_recv(NOP);
	while(SPI1->SR & SPI_SR_BSY);
	GPIOA_BSRR |= GPIO_BSRR_3_S;
	return data;
}

void nrf_writebuf(uint8_t addr, uint8_t *buf, uint8_t count)
{
	GPIOA_BSRR |= GPIO_BSRR_3_R;
	spi_send_recv(addr);
	for(uint8_t i = 0; i < count; i++)
	{
		(void)spi_send_recv(buf[i]);
	}
	while(SPI1->SR & SPI_SR_BSY);
	GPIOA_BSRR |= GPIO_BSRR_3_S;
}

void nrf_readbuf(uint8_t addr, uint8_t *buf, uint8_t count)
{
	GPIOA_BSRR |= GPIO_BSRR_3_R;
	spi_send_recv(addr);
	for(uint8_t i = 0; i < count; i++)
	{
		buf[i] = spi_send_recv(0xFF);
	}
	while(SPI1->SR & SPI_SR_BSY);
	GPIOA_BSRR |= GPIO_BSRR_3_S;
}

// ------------------------------- //




