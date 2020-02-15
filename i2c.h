#define I2C_SDA_PORT GPIOA
#define I2C_SCL_PORT GPIOA

#define I2C_SDA_PIN 1
#define I2C_SCL_PIN 0

#define TimeX 1

void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_wbyte(uint8_t data);
uint8_t i2c_rbyte(uint8_t ACK);
void ee_wblock(uint8_t address_h, uint8_t address_l, uint8_t* buf, uint8_t lenght);
void ee_rblock(uint8_t address_h, uint8_t address_l, uint8_t* buf, uint8_t lenght);
