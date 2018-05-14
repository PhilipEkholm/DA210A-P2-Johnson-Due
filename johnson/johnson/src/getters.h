/*
 * getters.h
 *
 * Created: 2018-05-09 09:26:39
 *  Author: joels
 */ 

#include <asf.h>
#ifndef GETTERS_H_
#define GETTERS_H_
struct point {
	uint16_t x;
	uint16_t y;
};


struct point get_origin();
struct point get_box();
struct point get_ball();
struct point get_cube();
struct point get_pos();


#endif /* GETTERS_H_ */