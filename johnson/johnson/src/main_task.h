/*
 * nav_task.h
 *
 * Created: 4/23/2018 11:38:23 AM
 *  Author: Philip Ekholm
 */ 

#pragma once

#define TASK_MAIN_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_MAIN_PRIORITY   (2)

#define TASK_DEBUG_MAIN_PIN  (52)

void main_task(void *pvParameters);
