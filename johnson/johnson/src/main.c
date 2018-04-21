/*
 * P2 Johnson Due
 *
 * Created: 2015-06-17 14:32:55
 *  Author: Philip Ekholm, 
 */ 

#include <asf.h>

#include "drivers/console_driver.h"
#include "drivers/delay.h"
#include "pin_mapper.h"

int main (void)
{
	sysclk_init();
	board_init();

	delay_init();
	ioport_init();
	console_init();
	
	ioport_enable_pin(pin_mapper(13));
	ioport_set_pin_dir(pin_mapper(13), IOPORT_DIR_OUTPUT);

	while(1){
		delay_ms(200);
		ioport_set_pin_level(pin_mapper(13), 1);
		printf("Hello, World!\n");
		delay_ms(200);
		ioport_set_pin_level(pin_mapper(13), 0);
	}
}
