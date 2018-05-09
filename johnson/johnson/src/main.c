/*
 * P2 Johnson Due
 *
 * Created: 2015-06-17 14:32:55
 *  Author: Philip Ekholm, 
 */ 

#include <asf.h>

#include "motor_task.h"
#include "main_task.h"

#include "drivers/console_driver.h"
#include "drivers/delay.h"
#include "drivers/encoder.h"
#include "pin_mapper.h"
#include "getters.h"

int main (void)
{
	sysclk_init();
	board_init();

	delay_init();
	ioport_init();
	console_init();
	encoder_init_pin_interrupt();

	ioport_enable_pin(pin_mapper(TASK_DEBUG_MOTOR_PIN));
	ioport_enable_pin(pin_mapper(TASK_DEBUG_MAIN_PIN));
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_MOTOR_PIN), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_MAIN_PIN), IOPORT_DIR_OUTPUT);
	
	/* Create our tasks for the program */
	xTaskCreate(motor_task, (const signed char * const) "motor_task", TASK_MOTOR_STACK_SIZE, NULL, TASK_MOTOR_PRIORITY, NULL);
	xTaskCreate(main_task, (const signed char * const) "main_task", TASK_MAIN_STACK_SIZE, NULL, TASK_MAIN_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}
