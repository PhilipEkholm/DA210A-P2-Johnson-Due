/*
 * Functions.c
 *
 * Created: 2018-04-27 14:13:04
 *  Author: Ali Hassan
 */ 
/* Low level time limit of I2C Fast Mode. */
#include <asf.h>
#define LOW_LEVEL_TIME_LIMIT 384000
#define I2C_FAST_MODE_SPEED  400000

void Slave_init(int8_t ul_device_addr){
		pmc_enable_periph_clk(ID_TWI0); /* power the clock for the TWI with pmc */
		PIOA->PIO_PDR|= (PIO_PB17)|(PIO_PB18);	/* Enable TWI pios */
	/* Disable TWI interrupts */
	TWI0->TWI_IDR = ~0UL;
	TWI0->TWI_SR;
	/* Set SWRST bit to reset TWI peripheral */
	TWI0->TWI_CR = TWI_CR_SWRST;
	TWI0->TWI_RHR;
	/* Set slave address in slave mode */
	TWI0->TWI_SMR = TWI_SMR_SADR(ul_device_addr);
	/* Set Master Disable bit and Slave Disable bit */
	TWI0->TWI_CR = TWI_CR_MSDIS;
	TWI0->TWI_CR = TWI_CR_SVDIS;

	/* Set Slave Enable bit */
	TWI0->TWI_CR = TWI_CR_SVEN;
}


void slave_write(int8_t data){		
		//write data  to THR
		TWI0->TWI_THR |= data;
		TWI0->TWI_CR |= (0x1u << 1); //Sett a STOP Condition
			//wait for Nack/ack
		while (!(TWI0->TWI_SR & TWI_SR_TXRDY)){}
		//while (!(TWI0->TWI_SR & TWI_SR_TXCOMP)){}


}

