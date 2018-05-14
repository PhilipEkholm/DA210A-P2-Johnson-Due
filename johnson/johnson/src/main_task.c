/*
 * nav_task.c
 *
 * Created: 4/23/2018 11:35:40 AM
 *  Author: Philip Ekholm
 */ 
#include <asf.h>

#include "main_task.h"
#include "pin_mapper.h"
#include "drivers/encoder.h"

void main_task(void *pvParameters) {
	while(1){
		/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "getters.h"
#include "consoleFunctions.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */


	
}

