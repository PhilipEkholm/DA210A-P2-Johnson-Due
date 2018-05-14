#include <asf.h>

#include "motor_task.h"
#include "pin_mapper.h"
#include "MotorControll.h"
#include "math_functions.h"
#include "drivers/encoder.h"

#define MOTOR_TASK_PERIODICITY 4 /* The number on the macro will decide the periodicity of the task */

void motor_task(void *pvParameters) {
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = MOTOR_TASK_PERIODICITY;
	int rotation = math_get_angle_deg(math_atan2(200,324,0,0))/3.809;
	int counter = 1;
	uint16_t avstand = distance(get_euclid_distance(200,324,0,0));
	
	while(1){
		/* Get current tick count */
		xLastWakeTime = xTaskGetTickCount();
		
		
		
		/* The task is now done, go to sleep until it's time again */
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}

}