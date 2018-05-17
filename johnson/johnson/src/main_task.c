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
#include "TWI.h"
#include "math_functions.h"

#define MAIN_TASK_PERIODICITY 10

struct point mock_positions[4] = {
	{ 50, 100 },
	{ 120, 50 },
	{ 140, 150 },
	{ 280, 260 },
};

uint8_t array[10]={};
twi_packet_t packet_pos ={
	.addr[0] = 0x00,	// TWI address/commands to issue to the other chip (node).
	.addr [1]=0,
	.addr_length =0,	// Length of the TWI data address segment (1-3 bytes)
	.chip = unoAddress,		// Adress to Mega kort
	.buffer = array, // where to save packet
	.length =10,	//packet length
};

static struct point current_pos;
static struct point earlier_pos;
static struct point box;
static struct point object;

struct point get_pos(void){
	
	struct point coordinates;
	
	coordinates.x = array[8]*2;
	coordinates.y = array[9]*2;
	/* Mock, replace later */
	coordinates.x = 0;
	coordinates.y = 0;
	return coordinates;
};

struct point get_box(void){
	
	struct point coordinates;
	
	coordinates.x = array[0]*2;
	coordinates.y = array[1]*2;
	/* Mock, replace later */
	coordinates.x = 50;
	coordinates.y = 50;
	return coordinates;
};

struct point get_ball(void){
	struct point coordinates;
	
	coordinates.x = array[4]*2;
	coordinates.y = array[5]*2;
	/* Mock, replace later */
	coordinates.x = 300;
	coordinates.y = 300;
	return coordinates;
};

struct point get_cube(void){
	
	struct point coordinates;
	
	coordinates.x = array[2]*2;
	coordinates.y = array[3]*2;
	/* Mock, replace later */
	coordinates.x = 300;
	coordinates.y = 300;
	return coordinates;
};

void main_task(void *pvParameters) {
	uint16_t distance, minimum_distance_to_object; /* In cm */
	double alpha, beta, correction_angle, minimum_angle = 1; /* In degrees */
	uint8_t mock_pos_index = 0;
	
	/* Read first time package and set static coordinates */
	I2C_master_read(TWI1, &packet_pos);
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
		
	I2C_master_read(TWI1, &packet_pos);
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
		else {
			/* Motor task busy, wait until stop */
		}
	}
		
	while(1);
}

