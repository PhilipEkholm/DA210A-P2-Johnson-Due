#include <asf.h>
#include <fastmath.h>
#include "consoleFunctions.h"
#include "Functions.h"
#include "TWI.h"
#include "DelayFunctions.h"
xSemaphoreHandle signal = NULL ;
int32_t arr[9];
uint8_t x = 0;
uint8_t y=0 ;
int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	configureConsole();
	delayInit();
	Twi_master_init();
	while (1)
	{
		twi_Start(TWI1,unoAddress,1);
		//master_write_byte(TWI1, x);
		y=master_read();
		printf("received: %d\n",y);
		y=0;
	}
	
// 		delayMicroseconds(400000);
// 		twi_Start(TWI1,unoAddress,0);
// 		master_write_byte(TWI1, y);
// 		printf("Turn off:%d\n",y);
// 		delayMicroseconds(4000000);
		
	
	
		
		
	
	
// 	int x=0,x2=3,y=0,y2=5;
// 	double Sx=0.0,Sy=0.0;	
// 	printf("-----TEST------\n");
// 	
// 	Sx = x2-x;
// 	Sy = y2- y;
// 	printf("Arlo befinner sig: (%d,%d)\n",x,y);
// 	printf("----------------------\n");
// 	printf("Objektet ligger: (%d,%d)\n",x2,y2);
// 	printf("----------------------\n");
// 	int distance =(int)get_euclid_distance(Sx,Sy);
// 	printf("Avståndet : %d cm\n",distance);
// 	printf("----------------------\n");
// 	printf("Alpha : %d\n",(int)calculate_alpha(x,x2,y,y2));
// 	printf("----------------------\n");
// 	x2+=8;
// 	y2+=3;
// 	Sx = x2-x;
// 	Sy = y2- y;
// 	int distance2 =(int)get_euclid_distance(Sx,Sy);
// 	printf("nya avståndet : %d cm\n",distance2);
// 	printf("----------------------\n");
// 	printf("nya Alpha : %d\n",(int)calculate_alpha(x,x2,y,y2));
// 	printf("----------------------\n");
// 	printf("Beta : %d\n",(int)calculate_beta(2, 5,distance));
// 	printf("----------------------\n");
// 	printf("Korrigeringsvinkel : %d\n",(int)get_correction_angle(calculate_alpha(x,x2,y,y2),
// 	calculate_beta(2, 5,distance)));
// 	printf("----------------------\n");
// 	vSemaphoreCreateBinary(signal);
// 	
// 	xTaskCreate(task_controller, (const signed char * const) "Task1", TASK_CONTROLLER_STACK_SIZE, NULL, TASK_CONTROLLER_PRIORITY , NULL);
// 	xTaskCreate(task2, (const signed char * const) "Task2", TASK_2_STACK_SIZE, NULL, TASK_PLAYER1_PRIORITY, NULL);
// 	vTaskEndScheduler();
// 	
}
