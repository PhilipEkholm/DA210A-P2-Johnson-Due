/*
 * Functions.c
 *
 * Created: 2018-04-16 10:01:33
 *  Author: Ali Hassan and Philip Ekholm
 */ 
#include <asf.h>
#include <fastmath.h>
#include "Functions.h"
double calculate_bow (int distance, int angel){
	return angel*(pi*(distance)/180);
}
// beräkanr avståndet till objektet.
double get_euclid_distance(double x, double y) {
	return sqrt((x*x) + (y*y));
}
// beräknade ny vinkel alpha
double calculate_alpha(int x, int x2, int y, int y2){
	return  atan(abs(y2-y)/ abs(x2-x));
	
}
// (verkligen) orientering vinkel
// param: antal impulsar från pulsgivare
//param totalImpulsPerCycle: totala antal impuls per cykel
double calculate_beta (int Impuls,int totalImpulsPerCycle, double distance ){
	int wheelDiameter =2;			// diamtern på hjulen
	return (Impuls*pi*wheelDiameter)/(distance*totalImpulsPerCycle);
}

//Beräknar Korrigerings vinkel ?
// param alpha: den genom omnavigering beräknade ny vinkel
// param beta:  den momentana (verkligen) orientering
double get_correction_angle(double alpha, double beta) {
	return (alpha - beta);
}
/*
* beräknar krökningsradie
*param distance: avståndet till objektet
*param diameter : avstånd mellan hjulen
* param angen : Korrigerings vinkel ?
*/
double get_correction_curvature(int distance, int diamter, double angel){
	return((2*diamter*sin(angel)/distance) +1);
	
}
