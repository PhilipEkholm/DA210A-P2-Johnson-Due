/*
 * arm_task.h
 *
 * Created: 4/23/2018 2:58:25 PM
 *  Author: Philip Ekholm
 */ 

#pragma once

void arm_task(void *pvParameters);

#define TASK_ARM_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_ARM_PRIORITY   (1)

#define TASK_DEBUG_ARM_PIN  (51)