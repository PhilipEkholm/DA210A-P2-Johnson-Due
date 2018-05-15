#include <asf.h>

#include "motor_task.h"
#include "pin_mapper.h"
#include "MotorControll.h"
#include "math_functions.h"
#include "drivers/encoder.h"
#include "TWI.h"

#define MOTOR_TASK_PERIODICITY 4 /* The number on the macro will decide the periodicity of the task */

void motor_task(void *pvParameters) {
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = MOTOR_TASK_PERIODICITY;
	uint16_t newAngle = math_get_angle_deg(math_atan2(200,400,0,0))/3.809;
	uint16_t newDistance = distance(get_euclid_distance(200,400,0,0));
	uint16_t oldAngle = 0;
	uint16_t oldDistance = 0;
	uint8_t flagg = 0;
	
	while(1){
		/* Get current tick count */
		xLastWakeTime = xTaskGetTickCount();
		
		//drive(1753,1793);
		if(get_counterA() < newAngle + newDistance -30 && get_counterB() < newAngle + newDistance -30){
			if(get_counterA() < (newAngle - oldAngle) && get_counterB() < (newAngle - oldAngle) && flagg == 0){
				printf("1");
				printf("NEWangel: %d\n", newAngle);
				printf("OLDangel: %d\n", oldAngle);
				driveVinkel(1);
//				oldAngle = oldAngle - 1;
			}else if(get_counterA() > (newAngle - oldAngle) && get_counterB() > (newAngle - oldAngle) && flagg == 0){
				printf("2");
				printf("NEWangel: %d\n", newAngle);
				printf("OLDangel: %d\n", oldAngle);
				driveVinkel(-1);
//				oldAngle = oldAngle + 1;
			}else{
				printf("");
				printf("NEWangel: %d\n", newAngle);
				printf("OLDangel: %d\n", oldAngle);
				drive(1753,1793);
				flagg = 1;
				for(int i = 0;i < 100;i++);
			}
		}else{
			drive(1500,1500);
// 			v1 = atan([gammalposx],[gammalposy],[nyposx],[nyposy]));
// 			v2 = atan([nyposx],[nyposy],[objektposx],[objektposy]));
// 			oldAngle = newAngle;
// 			newAngle = v1-v2;
			for(int i = 0;i < 100;i++);
		}
	
		
		/* The task is now done, go to sleep until it's time again */
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}

}