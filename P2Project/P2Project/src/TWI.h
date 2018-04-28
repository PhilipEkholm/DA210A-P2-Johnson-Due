/*
 * TWI.h
 *
 * Created: 2018-04-23 10:46:36
 *  Author: Ali Hassan
 */ 

#include <asf.h>
#ifndef TWI_H_
#define TWI_H_
#define unoAddress (0b00001000)
void Twi_master_init();
void master_write(int x, int Y);
void twi_Start(Twi* pTWI, uint8_t slave_address, uint8_t R_W);
uint8_t master_read();
void master_write_byte(Twi* pTWI, uint8_t data);
void twi_Stop(Twi* pTWI);
#endif /* TWI_H_ */