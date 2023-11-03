/*
 * ReadPageI2C.c
 *
 * Created: 9/13/2021 5:19:11 PM
 * Author : Amer Qouneh
 * See Logic Analyzer output image for this program. Addresses and data are visible.
 * Slave address is that of 24FC128 EEPROM used on CPE 427 board.
 * Continuously reads one multiple bytes of data from EEPROM.
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL

#define EEPROM1_WR 0b10100010	// write EEPROM 1 SLA_W address, lsb = 0 for write
#define EEPROM1_RD 0b10100011	// read EEPROM 1 SLA_R address, lsb = 1 for read

		

void i2c_init(void)
{
  TWSR=0x00;			
  TWBR=0x47;			
  TWCR=0x04;		
}
//**********************************************************
void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}
//**********************************************************
void i2c_write(unsigned char data)
{
  TWDR = data ;
  TWCR = (1<< TWINT)|(1<<TWEN);
  while ((TWCR & (1 <<TWINT)) == 0);
}
//**********************************************************
unsigned char i2c_read(unsigned char isLast)
{
  if (isLast == 0)		
    TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWEA);   // if want to read more than 1 byte
  else				
    TWCR = (1<< TWINT)|(1<<TWEN);   // if want to read only 1 byte
  while ((TWCR & (1 <<TWINT)) == 0);
  return TWDR  ;
}
//**********************************************************
void i2c_stop()
{
  TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWSTO);
}
//**********************************************************
int main (void) {
  unsigned char buffer[64];
  unsigned char i;
  
  i2c_init();
  while(1){
	i2c_start();
	i2c_write(EEPROM1_WR);   // Slave address EEPROM 1, Write
	i2c_write(0x00);   // high-byte of memory address	
	i2c_write(0x00);   // high-byte of memory address
	
	i2c_start();
	i2c_write(EEPROM1_RD);
	for (i=0; i<63; ++i) {
		buffer[i] = i2c_read(0);
	}
	buffer[i] = i2c_read(1);
	i2c_stop();
  }
}



