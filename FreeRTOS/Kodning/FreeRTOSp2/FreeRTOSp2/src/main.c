/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "delay.h"
#include "uart_driver.h"
#include "pins.h"
#include "pos_nav_task.h"
#include "regulatory_task.h"
#include "arm_task.h"

xSemaphoreHandle pos_nav_task = NULL;
xSemaphoreHandle regulatory_task = NULL;
xSemaphoreHandle arm_task = NULL;

int main (void)
{
	sysclk_init();
	board_init();
	delay_init();
	uart0_init();
	pins_init();

	ioport_init();
	ioport_enable_pin(PIO_PB27_IDX);
	ioport_enable_pin(PIO_PB26_IDX);

	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
	
	//char string [16];
	//while(1){
		//sprintf(string, "counter: %d\n", get_counter());
		//uart0_write_str(string);
		//delay_ms(50);
	//}
	
	vSemaphoreCreateBinary(pos_nav_task);
	vSemaphoreCreateBinary(regulatory_task);
	
	xTaskCreate(Task_pos_nav, (const signed char * const) "pos_nav", POS_NAV_TASK_STACK_SIZE, NULL, POS_NAV_TASK_PRIORITY, NULL);
	xTaskCreate(Task_regulatory, (const signed char * const) "regulatory", REGULATORY_TASK_STACK_SIZE, NULL, REGULATORY_TASK_PRIORITY, NULL);
	
	
	// Not testing arm task at the current state
	//vSemaphoreCreateBinary(arm_task);
	//xTaskCreate(arm_task, (const signed char * const) "arm", ARM_TASK_STACK_SIZE, NULL, ARM_TASK_PRIORITY, NULL);
	
	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();
}
