#ifndef _I2C_H_
#define _I2C_H_

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read

void i2c_write(unsigned char data);
void i2c_start(void);
void i2c_stop();
void i2c_init(void);
unsigned char i2c_read(unsigned char isLast);

#endif