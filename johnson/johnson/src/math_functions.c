/*
 * math_functions.c
 *
 * Created: 4/27/2018 10:48:11 AM
 *  Author: Philip Ekholm
 */ 

#include <fastmath.h>

#include "math_functions.h"

#define PI 3.141592653589

/* Takes an angle in radians and converts to degrees (from 0 to 360) */
double math_get_angle_deg(double rad){
	return (rad * (180/PI));
}

/* Takes an angle in degrees and converts to radians (from 0 to 2 * PI) */
double math_get_angle_rad(double deg){
	return (deg * (PI/180));
}

/* Get euclidean distance between two points (see Pythagorean theorem) */
double get_euclid_distance(double x, double y) {
	return sqrt((x*x) + (y*y));
}

/* Return the angle in radians, see atan2 Wikipedia for reference */
double math_atan2(double x, double y) {
	if (x == 0 && y == 0){
		printf("Invalid input values!\n");
		return -1;
	}

	if (x > 0)
		return atan(y/x);
	else if (x < 0 && y >= 0)
		return (atan(y/x) + PI);
	else if(x < 0 && y < 0)
		return (atan(y/x) - PI);
	else if(x == 0 && y > 0)
		return (PI/2);
	else
		return (-PI/2);
}
