/*
 * nav_task.c
 *
 * Created: 4/23/2018 11:35:40 AM
 *  Author: Philip Ekholm
 * updated: Ali Hassan
 */ 
#include <asf.h>

#include "main_task.h"
#include "motor_task.h"
#include "pin_mapper.h"
#include "drivers/encoder.h"
#include "math_functions.h"
#include "positions.h"

#define MAIN_TASK_PERIODICITY 10

static struct point current_pos;
static struct point earlier_pos;
static struct point box;
static struct point object;

struct point mock_positions[4] = {
	{ 50, 100 },
	{ 120, 50 },
	{ 140, 150 },
	{ 280, 260 },
};

void main_task(void *pvParameters) {
	uint16_t distance, minimum_distance_to_object; /* In cm */
	double alpha, beta, correction_angle, minimum_angle = 1; /* In degrees */
	uint8_t mock_pos_index = 0;
	
	/* Read first time package and set static coordinates */
	update_positions();
	current_pos = get_pos();
	box = get_box();
	
	if (ioport_get_pin_level(pin_mapper(SWITCH_CURIE_NOETHER_PIN))) {
		/* Marie Curie */
		object = get_cube();
		minimum_distance_to_object = 30;
		printf("Curie");
	}
	else{
		/* Emmy Noether */
		object = get_ball();
		minimum_distance_to_object = 30;
		printf("Noether");
	}
		
	update_positions();
	current_pos = get_pos();

	/* Drive only half the distance */
	distance = get_euclid_distance(object.x, object.y, current_pos.x, current_pos.y) / 2;
	alpha = math_get_angle_deg(math_atan2(object.x, object.y, current_pos.x, current_pos.y));
		
	struct motor_task_instruction inst = {
		.distance = distance,
		.angle = alpha
	};
		
	xQueueSend(motor_task_instruction_handle, &inst, 10);
	earlier_pos = current_pos;
	
	printf("First run, angle: %d, d: %d", (int16_t)alpha, distance);

	while(distance > minimum_distance_to_object) {
		/* Wait for motor task to complete */
		while(xQueuePeek(motor_task_instruction_handle, &inst, 2));

		//I2C_master_read(TWI1, &packet_pos);
		//PSEUDO: Get robot's new position and update current_pos
		current_pos = mock_positions[mock_pos_index];
		printf("Current pos: (%d, %d)\n", current_pos.x, current_pos.y);
		printf("Earlier pos: (%d, %d)\n", earlier_pos.x, earlier_pos.y);
		
		distance = get_euclid_distance(object.x, object.y, current_pos.x, current_pos.y) / 2;
		/* Calculate the actual angle that was driven */
		beta = math_get_angle_deg(math_atan2(current_pos.x, current_pos.y, earlier_pos.x, earlier_pos.y));
		alpha = math_get_angle_deg(math_atan2(object.x, object.y, current_pos.x, current_pos.y));
		correction_angle = beta - alpha;
		
		printf("correction: %d, d: %d\n", (int16_t)correction_angle, distance);
		printf("Object: (%d, %d)\n", object.x, object.y);

		if (abs(correction_angle) < minimum_angle){
			correction_angle = 0;
		}
			
		inst.distance = distance;
		inst.angle = correction_angle;

		if (xQueueSend(motor_task_instruction_handle, &inst, 5)) {
			/* Instruction successfully sent to motor task */
			earlier_pos = current_pos;
			mock_pos_index++;
		}
	}
	
	/* Find the object and pick it up */
	

	/* P2 is now over. */
	while(1);
}

