/*
 * arm_task.h
 *
 * Created: 2018-04-17 10:59:00
 *  Author: Emil
 */ 


#ifndef ARM_TASK_H_
#define ARM_TASK_H_

#define ARM_TASK_STACK_SIZE (2048 / sizeof(portSTACK_TYPE))
#define ARM_TASK_PRIORITY   (2)

extern xSemaphoreHandle arm_task;

#endif /* ARM_TASK_H_ */