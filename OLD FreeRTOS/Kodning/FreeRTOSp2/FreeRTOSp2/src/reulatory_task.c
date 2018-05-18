/*
 * task1.c
 *
 * Created: 2018-04-17 10:23:36
 *  Author: Emil
 */ 

#include <asf.h>
#include "delay.h"

void Task_regulatory(void *pvParameters)
{
	while(1) {
		volatile j = 0;

		for (int i=0; i < 100; i++) 
		{
			j++;
			ioport_set_pin_level(PIO_PB27_IDX, 1);
		}
		ioport_set_pin_level(PIO_PB27_IDX, 0);
		vTaskDelay(1);
	}
}
