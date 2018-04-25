/*
 * Functions.c
 *
 * Created: 2018-04-16 10:01:33
 *  Author: Ali Hassan and Philip Ekholm
 */ 
#include <asf.h>
#include <fastmath.h>
#include "Functions.h"
#define pi 3.14159265359
int calculate_bow (int distance, int angel){
	return angel*(pi*(distance)/180);
}
// beräkanr avståndet till objektet.
int get_euclid_distance(int x, int y) {
	return sqrt((x*x) + (y*y));
}
// beräknade ny vinkel alpha
int calculate_alpha(int x, int y){
	return atan(abs(y)/abs(x));
}
// (verkligen) orientering vinkel
// param: antal impulsar från pulsgivare
//param totalImpulsPerCycle: totala antal impuls per cykel
int calculate_beta (int Impuls,int totalImpulsPerCycle, int distance ){
	int wheelDiameter =2;			// diamtern på hjulen
	return (Impuls*pi*wheelDiameter)/(distance*totalImpulsPerCycle);
}

//Beräknar Korrigerings vinkel ?
// param alpha: den genom omnavigering beräknade ny vinkel
// param beta:  den momentana (verkligen) orientering
int get_correction_angle(int alpha, int beta) {
	return (alpha - beta);
}
/*
* beräknar krökningsradie
*param distance: avståndet till objektet
*param diameter : avstånd mellan hjulen
* param angen : Korrigerings vinkel ?
*/
int get_correction_curvature(int distance, int diamter, int angel){
	return((2*diamter*sin(angel)/distance) +1);
	
}
