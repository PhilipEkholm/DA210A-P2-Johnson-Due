/*
 * pins.c
 *
 * Created: 2018-04-16 21:09:56
 *  Author: Philip Ekholm
 */ 
#include <asf.h>
#include <sam3x8e.h>


#include "pins.h"

static volatile int counter = 0;

int get_counter(void) {
	return counter;
}

void pio_interrupt(void) {
	// Save all triggered interrupts
	uint32_t status = PIOB->PIO_ISR;
	
	counter++;
}

void pins_init(void) {
	// Enable Clock for PIOB - needed for sampling falling edge
	pmc_enable_periph_clk(ID_PIOB);
	
	pio_set_input(PIOB, PIO_PB26, PIO_PULLUP); 
	
	// Enable Glitch/Debouncing filter
	PIOB->PIO_IFER = PIO_PB26;
	
	// Select Debouncing filter
	PIOB->PIO_DIFSR = PIO_PB26;
	
	// Set Debouncing clock divider
	PIOB->PIO_SCDR = 0x4FF;
	
	pio_handler_set(PIOB, ID_PIOB, PIO_PB26, PIO_IT_RISE_EDGE, pio_interrupt);
	pio_enable_interrupt(PIOB, PIO_PB26);
	
	// Enable Interrupt Handling in NVIC
	NVIC_EnableIRQ(PIOB_IRQn);
}
