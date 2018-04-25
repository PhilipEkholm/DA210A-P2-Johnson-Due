/*
 * Functions.h
 *
 * Created: 2018-04-16 10:01:33
 *  Author: Ali Hassan and Philip Ekholm
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define pi 3.141592654
int calculate_bow(int distance, int angel);
int calculate_beta (int Impuls,int totalImpulsPerCycle, int distance );
int get_euclid_distance(int x, int y);
int get_correction_angle(int alpha, int beta);
int calculate_alpha(int x, int y);
int get_correction_curvature(int distance, int diamter, int angel);

#endif /* FUNCTIONS_H_ */