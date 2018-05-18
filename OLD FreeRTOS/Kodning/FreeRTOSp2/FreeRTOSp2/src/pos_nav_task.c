/*
 * pos_nav_task.c
 *
 * Created: 2018-04-18 14:50:35
 *  Author: xisth
 */ 

#include <asf.h>
#include "delay.h"

void Task_pos_nav(void *pvParameters)
{
	while(1) {
		volatile j = 0;

		for (int i=0; i < 100; i++)
		{
			j++;
			ioport_set_pin_level(PIO_PB26_IDX, 1);
		}
		ioport_set_pin_level(PIO_PB26_IDX, 0);
		vTaskDelay(1);
	}
}
