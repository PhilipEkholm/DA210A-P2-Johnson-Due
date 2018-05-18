/*
 * pos_nav_task.h
 *
 * Created: 2018-04-18 14:50:50
 *  Author: xisth
 */ 


#ifndef POS_NAV_TASK_H_
#define POS_NAV_TASK_H_

#define POS_NAV_TASK_STACK_SIZE (2048 / sizeof(portSTACK_TYPE))
#define POS_NAV_TASK_PRIORITY   (2)

extern xSemaphoreHandle pos_nav_task;

void Task_pos_nav(void *pvParameters);

#endif /* POS_NAV_TASK_H_ */