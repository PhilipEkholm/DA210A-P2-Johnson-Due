/*
 * motor_task.c
 *
 * Created: 4/23/2018 11:43:13 AM
 * Author: Mohamed & Charif
 * Updated: Philip -> Added Queue Logic
 */ 

#include <asf.h>

#include "motor_task.h"
#include "pin_mapper.h"
#include "MotorControll.h"
#include "math_functions.h"
#include "drivers/encoder.h"
#include "drivers/TWI.h"
#include "main_task.h"

#define MOTOR_TASK_PERIODICITY 4 /* The number on the macro will decide the periodicity of the task */

/************************************************************************/
/* Delay that is used to make the the robot stop for a second			*/
/************************************************************************/
static void forDelay(){
	for(int i = 0;i < 200000;i++){
		drive(1500,1500);
	}
}
/************************************************************************/
/* Logic for the steering of the robot, converts distance to pulses and	*/
/* rotates the robot depending on what the navigation sends				*/
/************************************************************************/
void motor_task(void *pvParameters) {
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = MOTOR_TASK_PERIODICITY;
 	int16_t angle = 0;
 	int16_t distance = 0;
	uint8_t distanceFlag = 0;
	uint8_t angleFlag = 0;
	uint8_t flaggu = 0;
	uint8_t accelerate = 200;
	
	struct motor_task_instruction current_instruction;
	
	while(1){
		/* Get current tick count */
		xLastWakeTime = xTaskGetTickCount();
		
		while(!xQueuePeek(motor_task_instruction_handle, &current_instruction, 10));
		
		/*Converts distance and angle to pulses for the robot to use*/
		angle = (int16_t)current_instruction.angle/3.809;
		distance = convertDistance(current_instruction.distance);
		
		/* If statement that checks if the angle is nagative or positive, to determine if it should *
		* rotate to the right or left */
		if(angle<0){
			angle = angle * -1;
			angleFlag = 3;
		}else{
			angleFlag = 0;
		}
		/*If statement that checks if the distance is negative or positive, to determine if it *
		* should go forward or backwards */
		if(distance<0){
			distance = -distance;	
			distanceFlag = 1;
		}
		/*Adds the pulses if angle and distance, checks the encoder if it has reached the destination*/
		if(get_counterA() < angle + distance && get_counterB() < angle + distance){
			
			/* Rotates to the right if angle is above 0 and left if it is under 0 then drives forward *
			* until all pulses are used */
			if(get_counterA() < (angle) && get_counterB() < (angle) && angleFlag == 0){
				driveVinkel(1);
			}else if(get_counterA() < (angle) && get_counterB() < (angle) && angleFlag == 3){
				driveVinkel(-1);
			}else{
				if(flaggu != 1){
					forDelay();
					flaggu = 1;
				}
				if(distanceFlag == 1){
					drive(1363, 1393);
				}
				else{
					drive(1753 - accelerate,1793 - accelerate);
					/* This statement makes the robot accelerate smoother to not damage the sensor */
					if(accelerate > 0){
						accelerate = accelerate - 1;
						if (accelerate < 0){
							accelerate = 0;
						}
					}
				}
			}
		}
		/* After the robot is done it stops and resets the variables */
		else{
			forDelay();
			angleFlag = 1;
			distanceFlag = 0;
			flaggu = 0;
			accelerate = 200;
			/* Finished driving the distance, empty queue for new instruction */
			xQueueReceive(motor_task_instruction_handle, &current_instruction, 10);
			resetCounterA();
			resetCounterB();
		}
	
		/* The task is now done, go to sleep until it's time again */
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

