/*
 * encoder.c
 *
 * Created: 4/24/2018 7:35:52 AM
 *  Author: Philip Ekholm
 */ 

#include <asf.h>
#include <sam3x8e.h>

#include "encoder.h"

static volatile int counter = 0;

int get_counter(void) {
	return counter;
}

void pio_interrupt(void) {
	counter++;
}

/* 
* Enable interrupt to be triggered on high edge on any input pin
*/

void encoder_init_pin_interrupt(void) {
	/* Enable Clock for PIOB - needed for sampling falling edge */
	pmc_enable_periph_clk(ID_PIOB);
	/* Set specific pin to use as input */
	pio_set_input(PIOB, PIO_PB26, PIO_PULLUP);

	/* Enable Glitch/Debouncing filter */
	PIOB->PIO_IFER = PIO_PB26;

	/* Select Debouncing filter */
	PIOB->PIO_DIFSR = PIO_PB26;

	/* Set Debouncing clock divider */
	PIOB->PIO_SCDR = 0x4FF;

	/* Add an interrupt callback of our own choice and trigger on rising edge */
	pio_handler_set(PIOB, ID_PIOB, PIO_PB26, PIO_IT_RISE_EDGE, pio_interrupt);

	/* Enable Interrupt Handling in NVIC and in PIO */
	pio_enable_interrupt(PIOB, PIO_PB26);
	NVIC_EnableIRQ(PIOB_IRQn);
}

