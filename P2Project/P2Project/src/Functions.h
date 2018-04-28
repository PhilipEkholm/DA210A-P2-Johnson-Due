/*
 * Functions.h
 *
 * Created: 2018-04-16 10:01:33
 *  Author: Ali Hassan and Philip Ekholm
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define pi 3.141592654
double calculate_bow(int distance, int angel);
double calculate_beta (int Impuls,int totalImpulsPerCycle, double distance );
double get_euclid_distance(double x, double y);
double get_correction_angle(double alpha, double beta);
double calculate_alpha(int x, int x2, int y, int y2);
double get_correction_curvature(int distance, int diamter, double angel);

#endif /* FUNCTIONS_H_ */