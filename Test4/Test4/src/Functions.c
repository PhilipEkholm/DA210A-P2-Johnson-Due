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
// ber�kanr avst�ndet till objektet.
int get_euclid_distance(int x, int y) {
	return sqrt((x*x) + (y*y));
}
// ber�knade ny vinkel alpha
int calculate_alpha(int x, int y){
	return atan(abs(y)/abs(x));
}
// (verkligen) orientering vinkel
// param: antal impulsar fr�n pulsgivare
//param totalImpulsPerCycle: totala antal impuls per cykel
int calculate_beta (int Impuls,int totalImpulsPerCycle, int distance ){
	int wheelDiameter =2;			// diamtern p� hjulen
	return (Impuls*pi*wheelDiameter)/(distance*totalImpulsPerCycle);
}

//Ber�knar Korrigerings vinkel ?
// param alpha: den genom omnavigering ber�knade ny vinkel
// param beta:  den momentana (verkligen) orientering
int get_correction_angle(int alpha, int beta) {
	return (alpha - beta);
}
/*
* ber�knar kr�kningsradie
*param distance: avst�ndet till objektet
*param diameter : avst�nd mellan hjulen
* param angen : Korrigerings vinkel ?
*/
int get_correction_curvature(int distance, int diamter, int angel){
	return((2*diamter*sin(angel)/distance) +1);
	
}
