/*
 * arm_task.c
 *
 * Created: 4/23/2018 2:57:29 PM
 *  Author: Philip Ekholm
 */ 
#include <asf.h>

#include "arm_task.h"
#include "pin_mapper.h"

void arm_task(void *pvParameters) {
	while(1){
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_ARM_PIN), 1);
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_ARM_PIN), 0);
	}
}
