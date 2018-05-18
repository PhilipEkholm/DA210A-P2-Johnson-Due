/*
 * task1.h
 *
 * Created: 2018-04-17 10:23:53
 *  Author: Emil
 */ 


#ifndef REGULATORY_TASK_H_
#define REGULATORY_TASK_H_

#define REGULATORY_TASK_STACK_SIZE (2048 / sizeof(portSTACK_TYPE))
#define REGULATORY_TASK_PRIORITY   (2)

extern xSemaphoreHandle regulatory_task;

void Task_regulatory(void *pvParameters);

#endif /* TASK1_H_ */