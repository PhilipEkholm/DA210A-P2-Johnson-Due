/*
 * TWI.c
 *
 * Created: 2018-04-23 10:45:56
 *  Author: Ali Hassan
 */ 
#include <asf.h>
#include "TWI.h"

/* Low level time limit of I2C Fast Mode. */
#define LOW_LEVEL_TIME_LIMIT 384000
#define I2C_FAST_MODE_SPEED  400000

void Twi_master_init(){
	pmc_enable_periph_clk(ID_TWI1); /* power the clock for the TWI with pmc */

	PIOA->PIO_PDR|= (PIO_PB12)|(PIO_PB13);	/* Enable TWI pios */
	TWI1->TWI_CR = (0x1u << 7);				// TWIn software reset
	TWI1->TWI_RHR;							// Flush reception buffer
	/* Set Master Disable bit and Slave Disable bit */
	TWI1->TWI_CR = TWI_CR_MSDIS;
	TWI1->TWI_CR = TWI_CR_SVDIS;
	TWI1->TWI_CR |= (0x1u << 2);			/* Set Master Enable bit */
	TWI1->TWI_MMR |= TWI_MMR_DADR(unoAddress);//device address
	TWI1->TWI_PTCR |= (0x1u << 0)|(0x1u << 8);//Receiver/transmitter Transfer Enable 
	TWI0->TWI_IDR = ~0UL;					/* Disable TWI interrupts */
	TWI1->TWI_CWGR |= I2C_FAST_MODE_SPEED;
}
void twi_Start(Twi* pTWI, uint8_t slave_address, uint8_t R_W) { //read=1, write=0
	//set slave address
	pTWI->TWI_MMR = (pTWI->TWI_MMR & ~TWI_MMR_DADR_Msk)|TWI_MMR_DADR(slave_address);
	//set read/write direction
	if (R_W == 0) { //write
		pTWI->TWI_MMR &= ~(0x1u << 12);//Master write Direction 
	}
	else if (R_W == 1) { //read
		pTWI->TWI_MMR |= (0x1u << 12); //Master Read Direction 
	}
	pTWI->TWI_CR |= (0x1u << 0);//send start condition
	while (!(pTWI->TWI_SR & TWI_SR_TXRDY));//wait for ack
}

void master_write(int x, int Y){
	TWI0->TWI_THR =x;
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY));
	TWI0->TWI_THR =Y; 	
	while (!(TWI0->TWI_SR & TWI_SR_TXRDY));
		
}
void master_write_byte(Twi* pTWI, uint8_t data){
	
	pTWI->TWI_THR =data;//write data to THR
	twi_Stop(pTWI);
 	while (!(pTWI->TWI_SR & TWI_SR_TXRDY));
  	while (!(pTWI->TWI_SR & TWI_SR_TXCOMP));
}


uint8_t master_read()
{
	uint8_t received;
 	twi_Stop(TWI1);	
	while (!(TWI1 ->TWI_SR & TWI_SR_RXRDY)){}
	received =TWI1->TWI_RHR; 
	return received;
}

/***************************   Stop    ****************************/
void twi_Stop(Twi* pTWI) {
	pTWI->TWI_CR |= (0x1u << 1); //Sett a STOP Condition 
}

