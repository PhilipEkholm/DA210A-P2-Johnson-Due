/**

/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <pio.h>
#include <pwm.h>
#include <adc.h>
#include <uart.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "conf_uart_serial.h"
#include <setjmp.h>
#include "pins.h"
#include "MotorControll.h"
#include "Functions.h"
#define pi 3.14159265359




//----------------------------------------------------------------------------------------------------------------------

//drive function variables
 
//''''''''''''''	
uint16_t avstand = 0;
int32_t alpha = 0;
int counter = 0;

 static void configure_console(void)
 /* Enables feedback through the USB-cable back to terminal within Atmel Studio */
 {
	const usart_serial_options_t uart_serial_options = {
		 .baudrate = CONF_UART_BAUDRATE,
		 .paritytype = CONF_UART_PARITY
	 };

	 /* Configure console UART. */
	 sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	 stdio_serial_init(CONF_UART, &uart_serial_options);
	 
	 printf("Console ready\n");
	 printf("=============\n");
}


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	configure_console();
	ioport_init();
	pins_init();
	ioport_enable_pin(motor1);
	ioport_set_pin_dir(motor1, IOPORT_DIR_OUTPUT);

	ioport_enable_pin(motor2);
	ioport_set_pin_dir(motor2, IOPORT_DIR_OUTPUT);
	
	avstand = get_euclid_distance(370,600);
	printf("Avstad = %d" , avstand);
	avstand = distance(avstand);
//	alpha = calculate_alpha(370,600) * (180/pi);
//	printf("alpha  = %d\n", alpha);
	delay_s(3);
	set_counterA(0);
	set_counterB(0);
	driveVinkel(58);
	delay_s(2);
 	set_counterA(0);
 	set_counterB(0);
	while (get_counterA() < avstand && get_counterB() < avstand){
		drive(1753,1793);
	}
	drive(1500, 1500);
	delay_s(2);
	set_counterA(0);
	set_counterB(0);
	driveVinkel(180);
	delay_s(2);
	set_counterA(0);
	set_counterB(0);
	while (get_counterA() < avstand && get_counterB() < avstand){
		drive(1753,1793);
	}
	drive(1500, 1500);
}

	
	
	

