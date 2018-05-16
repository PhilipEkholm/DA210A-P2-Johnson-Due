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
static struct point ball;
static struct point cube;
static struct point box;

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
	
	coordinates.x = array[1]*2;
	coordinates.y = array[2]*2;
	/* Mock, replace later */
	coordinates.x = 50;
	coordinates.y = 50;
	return coordinates;
};

struct point get_ball(void){
	struct point coordinates;
	
	coordinates.x = array[5]*2;
	coordinates.y = array[6]*2;
	/* Mock, replace later */
	coordinates.x = 100;
	coordinates.y = 100;
	return coordinates;
};

struct point get_cube(void){
	
	struct point coordinates;
	
	coordinates.x = array[3]*2;
	coordinates.y = array[4]*2;
	/* Mock, replace later */
	coordinates.x = 250;
	coordinates.y = 250;
	return coordinates;
};

void main_task(void *pvParameters) {
	/* Read first time package and set static coordinates */
	I2C_master_read(TWI1, &packet_pos);
	current_pos = get_pos();
	ball = get_ball();
	cube = get_cube();
	box = get_box();

	uint16_t distance;
	double alpha;

	while(1){
		distance = get_euclid_distance(cube.x, cube.y, current_pos.x, current_pos.y);

		while(distance > 30) {
			I2C_master_read(TWI1, &packet_pos);
			current_pos = get_pos();

			/* Drive only half the distance */
			distance = get_euclid_distance(cube.x, cube.y, current_pos.x, current_pos.y) / 2;
			alpha = math_get_angle_deg(math_atan2(cube.x, cube.y, current_pos.x, current_pos.y));
			
			printf("Distance: %d\n", distance);
			printf("Angle: %d\n", (int16_t)alpha);
			
			struct motor_task_instruction inst = {
				.distance = distance,
				.angle = alpha
			};
			
			if (xQueueSend(motor_task_instruction_handle, &inst, 10)) {
				/* Instruction successfully sent to motor task */
				earlier_pos = current_pos;
			}
			else {
				/* Motor task busy, wait until stop */
			}
		}
	}
}

