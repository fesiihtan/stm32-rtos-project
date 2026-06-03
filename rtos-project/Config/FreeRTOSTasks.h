/*
 * FreeRTOSTasks.h
 *
 *  Created on: May 26, 2026
 *      Author: fesih
 */

#ifndef FREERTOSTASKS_H_
#define FREERTOSTASKS_H_

#include "FreeRTOS.h"
#include "task.h"

#define STARTUP_TASK_STACK_SIZE         (512)
#define STARTUP_TASK_PRIORITY           (configMAX_PRIORITIES - 1)

/**
 * The handler task handles the system errors.
 * Messages are sent to this task for error handling actions, which can be expanded/customized as needed.
 * The task has a high priority due to the need for timely error detection.
 * Stack size is set at 256 for prototyping, optimize later based on usage.
 */
#define ERROR_HANDLER_TASK_STACK_SIZE   (256)
#define ERROR_HANDLER_TASK_PRIORITY     (configMAX_PRIORITIES - 2)


#endif /* FREERTOSTASKS_H_ */
