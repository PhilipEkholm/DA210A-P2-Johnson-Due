/*
 * PWM_Configuration.h
 *
 * Created: 2018-05-02 12:10:34
 *  Author: Charif Ramadan
 */ 


#ifndef PWM_CONFIGURATION_H_
#define PWM_CONFIGURATION_H_

 // Definera pin 6 och pin 7 som en pwm pinne
 
#define PIN_24  IOPORT_CREATE_PIN(PIOC, 24)  // pinne 6
#define PIN_23  IOPORT_CREATE_PIN(PIOC, 23)  // pinne 7

void pwm_setup(void);
void initPin6(void);
void initPin7(void);
void pwm_pin_6(uint32_t duty);
void pwm_pin_7(uint32_t duty);



#endif /* PWM_CONFIGURATION_H_ */