#include "stm32f0xx.h"                  // Device header
#include "defines.h"
#include "delay.h"
#include "i2c.h"

#define I2C_ADDRESS 0x20

void i2c_start(void)
{
        I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);
        delay_us(TimeX);
        I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);
        while(!(I2C_SDA_PORT->IDR & (1<<I2C_SDA_PIN)))
        {
        I2C_SCL_PORT->BRR  = (1<<I2C_SCL_PIN);
        delay_us(TimeX);
        I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);
        }
        I2C_SDA_PORT->BRR = (1<<I2C_SDA_PIN);
        delay_us(TimeX);
        I2C_SCL_PORT->BRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);
}
void i2c_stop(void)
{
        I2C_SDA_PORT->BRR = (1<<I2C_SDA_PIN);
        delay_us(TimeX);
        I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);
        I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);
        delay_us(TimeX);
}

uint8_t i2c_wbyte(uint8_t data)
{
       uint8_t i;
       uint8_t ACK;
       for(i=0;i<8;i++)
       {
       if(data & 0x80)
       {
       I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);
       }
       else
       {
       I2C_SDA_PORT->BRR = (1<<I2C_SDA_PIN);
       }
       delay_us(TimeX);
       I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
       delay_us(TimeX);        
       I2C_SCL_PORT->BRR = (1<<I2C_SCL_PIN);
       data=data<<1;    
       }
       delay_us(TimeX); 
       I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);       
       I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
       delay_us(TimeX);        
			 GPIOA_MODER |= GPIO_MODER_12_IN;
       ACK = !(I2C_SDA_PORT->IDR & (1<<I2C_SDA_PIN));
			 GPIOA_MODER |=  GPIO_MODER_12_OUT;
       I2C_SCL_PORT->BRR = (1<<I2C_SCL_PIN);
       I2C_SDA_PORT->BRR = (1<<I2C_SDA_PIN);
       return ACK;
}

uint8_t i2c_rbyte(uint8_t ACK)
{
        uint8_t i;
        uint8_t data;
        
        I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);
      	GPIOA_MODER |= GPIO_MODER_12_IN;
      for(i=0;i<8;i++)
        {
        delay_us(TimeX);
        I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);       
        data<<=1;
      if(I2C_SDA_PORT->IDR & (1<<I2C_SDA_PIN))
        data++; 
        I2C_SCL_PORT->BRR = (1<<I2C_SCL_PIN);
        }
				GPIOA_MODER |= GPIO_MODER_12_OUT;
      if (ACK)
        I2C_SDA_PORT->BRR = (1<<I2C_SDA_PIN);
        delay_us(TimeX);       
        I2C_SCL_PORT->BSRR = (1<<I2C_SCL_PIN);
        delay_us(TimeX);       
        I2C_SCL_PORT->BRR = (1<<I2C_SCL_PIN);
        I2C_SDA_PORT->BSRR = (1<<I2C_SDA_PIN);
        return data;
}

void ee_wblock(uint8_t address_h, uint8_t address_l, uint8_t* buf, uint8_t lenght)
{
	uint8_t i;
	i2c_start();
	i2c_wbyte(I2C_ADDRESS);
	i2c_wbyte(address_h);
	i2c_wbyte(address_l);
	for(i = 0; i < lenght; i++)
	{
		i2c_wbyte(buf[i]);
	}
	i2c_stop();
	delay_ms(4);
}

void ee_rblock(uint8_t address_h, uint8_t address_l, uint8_t* buf, uint8_t lenght)
{
	uint8_t i;
	i2c_start();
	i2c_wbyte(I2C_ADDRESS);
	i2c_wbyte(address_h);
	i2c_wbyte(address_l);
	i2c_start();
	i2c_wbyte(I2C_ADDRESS | (1<<0));
	for(i = 0; i < lenght; i++)
	{
		buf[i] = i2c_rbyte(1);
	}
	i2c_stop();
}

