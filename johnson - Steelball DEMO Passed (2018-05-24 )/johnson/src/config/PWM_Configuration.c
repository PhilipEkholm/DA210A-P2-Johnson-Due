/*
 * PWM_Configuration.c
 *
 * Created: 2018-05-02 12:10:04
 *  Author: Charif Ramadan
 */ 
 #include "asf.h"
 #include "PWM_Configuration.h"
 #include "pin_mapper.h"
 
 pwm_channel_t PWM_pin_6;      // adressen till pin6
 pwm_channel_t  PWM_pin_7;     // adressen till pin7
  
   void pwm_setup(void){
	   pmc_enable_periph_clk(ID_PWM);
	   pwm_channel_disable(PWM,PWM_CHANNEL_7);
	   pwm_channel_disable(PWM,PWM_CHANNEL_6);

	   pwm_clock_t  clock_setting = {
		   .ul_clka = 1000000,
		   .ul_clkb = 0,
		   .ul_mck = sysclk_get_cpu_hz()
	   };
	   
	   pwm_init(PWM, &clock_setting);
	   initPin6();
	   initPin7();

   }
   
   void initPin6 (void){
	   pio_configure_pin(PIN_24, PIO_TYPE_PIO_PERIPH_B);
	   PWM_pin_6.channel = PWM_CHANNEL_7;
	   PWM_pin_6.alignment = PWM_ALIGN_LEFT;
	   PWM_pin_6.polarity = PWM_LOW;
	   PWM_pin_6.ul_prescaler = PWM_CMR_CPRE_CLKA;
	   PWM_pin_6.ul_period = 6000;
	   PWM_pin_6.ul_duty = 0;	   
	   pwm_channel_init(PWM, &PWM_pin_6);
	   pwm_channel_enable(PWM, PWM_CHANNEL_7);

   }
   void initPin7 (void){
	   pio_configure_pin(PIN_23, PIO_TYPE_PIO_PERIPH_B);
	   PWM_pin_7.alignment = PWM_ALIGN_LEFT;
	   PWM_pin_7.polarity = PWM_LOW;
	   PWM_pin_7.ul_prescaler = PWM_CMR_CPRE_CLKA;
	   PWM_pin_7.ul_period = 6000;
	   PWM_pin_7.ul_duty = 0;
	   PWM_pin_7.channel = PWM_CHANNEL_6 ;
	   pwm_channel_init(PWM, &PWM_pin_7);
	   pwm_channel_enable(PWM, PWM_CHANNEL_6);
   }
   
   
   // metod för duty cykle för pwm 6 
   void pwm_pin_6(uint32_t speed1){	   
    pwm_channel_update_duty(PWM, &PWM_pin_6, speed1); 
}

 // metod för duty cykle för pwm 7  
  void pwm_pin_7(uint32_t speed2){
	pwm_channel_update_duty(PWM, & PWM_pin_7, speed2 );
}