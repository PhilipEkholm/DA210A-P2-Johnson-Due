#include <asf.h>
#include <fastmath.h>
#include "TWI.h"
#include "consoleFunctions.h"
#include "DelayFunctions.h"
uint8_t x = 0;
uint32_t y=0 ;
uint8_t data_position[10]= {};	
uint8_t commando [1]= {12};
twi_packet_t packet_pos ={
	.addr[0] = 0x00,	// TWI address/commands to issue to the other chip (node).
	.addr [1]=0,
	.addr_length =0,	// Length of the TWI data address segment (1-3 bytes)
	.chip = unoAddress,		// Adress to Mega kort
	.buffer = data_position, // where to save packet
	.length =10,	//pakcket length
};

	
int main (void)
{
	board_init();
	sysclk_init();
	ioport_init();
	delayInit();
	configureConsole();
	Twi_master_init(TWI1);
	while (1)
	{
 		printf("--Arduino Due Master--\n");
 		printf("---------------------------\n");
// 		y= master_write_cmd(TWI1,12);
// 		printf("Transmitted cmd to Uno:%d\n", y)		delayMicroseconds(100000);
		I2C_master_read(TWI1,&packet_pos);
 		printf("received Packet from Mega:[");
 		for(int i = 0; i < 10; i++){
			printf("%d ", data_position[i]); 		}
		printf("]\n");	
//		delayMicroseconds(100000);
// 		x=master_read_cmd(TWI1);
// 		printf("received cmd from Uno:%d\n",x);
		printf("---------------------------\n");
		//delayMicroseconds(100000);
	}
	
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
