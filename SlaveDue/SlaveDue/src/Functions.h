/*
 * Functions.h
 *
 * Created: 2018-04-27 14:14:29
 *  Author: Ali Hassan
 */ 
#include <asf.h>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define SlaveAddress (0b00001000)
void Slave_init(int8_t ul_device_addr);
void slave_write(int8_t data);

#endif /* FUNCTIONS_H_ */