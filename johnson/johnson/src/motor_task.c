/*
 * motor_task.c
 *
 * Task for handling reglerpart with motors
 *
 * Created: 4/23/2018 11:25:58 AM
 *  Author: Philip Ekholm
 */
#include <asf.h>

#include "motor_task.h"
#include "pin_mapper.h"

#define MOTOR_TASK_PERIODICITY 4 /* The number on the macro will decide the periodicity of the task */

void motor_task(void *pvParameters) {
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = MOTOR_TASK_PERIODICITY;
	
	while(1){
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_MOTOR_PIN), 1);
		/* Get current tick count */
		xLastWakeTime = xTaskGetTickCount();
		volatile int j = 0;
		
		for (int i = 0; i < 1000; ++i){
			j++;
			ioport_set_pin_level(pin_mapper(TASK_DEBUG_MOTOR_PIN), 1);
		}

		ioport_set_pin_level(pin_mapper(TASK_DEBUG_MOTOR_PIN), 0);

		/* The task is now done, go to sleep until it's time again */
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}
