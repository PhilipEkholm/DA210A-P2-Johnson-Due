/*
 * nav_task.h
 *
 * Created: 4/23/2018 11:38:23 AM
 *  Author: Philip Ekholm
 */ 

#pragma once

void nav_task(void *pvParameters);

#define TASK_NAV_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_NAV_PRIORITY   (1)

#define TASK_DEBUG_NAV_PIN  (52)
