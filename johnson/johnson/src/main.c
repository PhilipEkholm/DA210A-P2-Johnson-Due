/*
 * P2 Johnson Due
 *
 * Created: 2015-06-17 14:32:55
 *  Author: Philip Ekholm, 
 */ 

#include <asf.h>

#include "motor_task.h"
#include "nav_task.h"
#include "arm_task.h"

#include "drivers/console_driver.h"
#include "drivers/delay.h"
#include "drivers/encoder.h"
#include "pin_mapper.h"

int main (void)
{
	sysclk_init();
	board_init();

	delay_init();
	ioport_init();
	console_init();
	encoder_init_pin_interrupt();
	
	ioport_enable_pin(pin_mapper(TASK_DEBUG_ARM_PIN));
	ioport_enable_pin(pin_mapper(TASK_DEBUG_MOTOR_PIN));
	ioport_enable_pin(pin_mapper(TASK_DEBUG_NAV_PIN));
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_ARM_PIN), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_MOTOR_PIN), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_NAV_PIN), IOPORT_DIR_OUTPUT);
	
	/* Create our tasks for the program */
	xTaskCreate(motor_task, (const signed char * const) "motor_task", TASK_MOTOR_STACK_SIZE, NULL, TASK_MOTOR_PRIORITY, NULL);
	xTaskCreate(nav_task, (const signed char * const) "navigation_task", TASK_NAV_STACK_SIZE, NULL, TASK_NAV_PRIORITY, NULL);
	xTaskCreate(arm_task, (const signed char * const) "arm_task", TASK_ARM_STACK_SIZE, NULL, TASK_ARM_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}
