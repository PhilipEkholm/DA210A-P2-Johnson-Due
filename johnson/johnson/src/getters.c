/*
 * getters.c
 *
 * Created: 2018-05-09 09:26:19
 *  Author: Joel Skogsberg
 */ 
#include <asf.h>
#include "getters.h"
//Array simulerar datapaket vi får skickat till oss 
int array[10] = {1,2,3,4,5,6,7,8,9,10};

//Get-metoder som returnerar X och Y pos till de nämda objekten. 
struct point get_origin(){
	
	struct point coordinates;
	
 coordinates.x = array[8]*2;
 coordinates.y = array[9]*2; 
 return coordinates; 
};


struct point get_box(){
	
	struct point coordinates;
	
	 coordinates.x = array[1]*2;
	 coordinates.y = array[2]*2;
	  return coordinates; 
};

struct point get_ball(){
	struct point coordinates;
		
	coordinates.x = array[5]*2;
	coordinates.y = array[6]*2;
	return coordinates;
};

struct point get_cube(){
		
	struct point coordinates;
		
	coordinates.x = array[3]*2;
	coordinates.y = array[4]*2;
	return coordinates;
};

struct point get_pos(){
		struct point coordinates;
		
		coordinates.x = array[8]*2;
		coordinates.y = array[9]*2;
		return coordinates;
};

	

