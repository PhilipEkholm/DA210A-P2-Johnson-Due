/*
 * nav_task.c
 *
 * Created: 4/23/2018 11:35:40 AM
 *  Author: Philip Ekholm
 */ 
#include <asf.h>

#include "nav_task.h"
#include "pin_mapper.h"
#include "drivers/encoder.h"

void nav_task(void *pvParameters) {
	while(1){
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_NAV_PIN), 1);
		
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_NAV_PIN), 0);
	}
}

