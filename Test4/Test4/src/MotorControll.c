/*
 * MotorControll.c
 *
 * Created: 2018-04-20 11:40:38
 *  Author: Mohamed & Charif
 */ 
#include <asf.h>
#include <sam3x8e.h>
#include "MotorControll.h"
#include "pins.h"

int16_t e = 0;
int16_t u = 0;
uint16_t Uv = 0;
uint16_t Uh = 0;
uint8_t k = 4;

 void motorA(uint16_t speed1){
	 ioport_set_pin_level(motor1, 1);
	 delay_us(speed1);
	 ioport_set_pin_level(motor1, 0);
 }
 
 void motorB(uint16_t speed2){
	 ioport_set_pin_level(motor2, 1);
	 delay_us(speed2);
	 ioport_set_pin_level(motor2, 0);
 }
  
  uint16_t distance(uint16_t cm){
		return cm/1.4;
  }
  
  void drive(uint16_t U0v, uint16_t U0h){
	  e = (get_counterA() - get_counterB());
	  u = (k*e);
	  
	  Uv = U0v - u;
	  Uh = u + U0h;
	  
	  motorA(Uv);
	  motorB(Uh);
	  
	  delay_us(1);
	  printf("encoder A %d och encoder B %d\n",get_counterA(), get_counterB());
	  printf("Motor A %d och motor B %d\n",Uv,Uh);
	  printf("e = %d\n",e);
	  printf("Fram=============\n");
  }
  int hoger = 1750;
  int venster = 1250;
  
  int getHoger(){
	  return hoger;
  }
  int getVenster(){
	  return venster;
  }

  void driveVinkel(int alpha){
	  alpha = alpha/4;
	  if(alpha < 0){
		  alpha = alpha * (-1);
		  while((get_counterA() < alpha) && (get_counterB() < alpha)){
			  drive(1250, 1725);
		  }
	  }else{
		  while((get_counterA() < alpha) && (get_counterB() < alpha)){
			  drive(1725, 1250);
		  }
	  }
	  drive(1500,1500);

	  
	  delay_us(1);
	  
	  printf("encoder A %d och encoder B %d\n",get_counterA(), get_counterB());
	  printf("Motor A %d och motor B %d\n",Uv,Uh);
	  printf("e = %d\n",e);
	  printf("Fram=============\n");
  }
  