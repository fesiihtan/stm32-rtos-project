/*
 * sensor_task.h
 *
 *  Created on: Jun 8, 2026
 *      Author: Fesih TAN
 *      @brief: Declares the necessary functions, data structures, and enumerations required by the sensor task
 */


#ifndef INC_SENSOR_TASK_H_
#define INC_SENSOR_TASK_H_

#include "error.h"
#include "FreeRTOSTasks.h"

/**
 * Sensors data structure to be populated by the sensor task
 */
typedef struct
{
  uint16_t voc_index;
  uint16_t amb_temp;
  uint16_t hum;
} sensor_task_data_t;

/**
 * Sensors task message IDs enum
 */
typedef enum
{
  SAMPLING_INTERVAL_UPDATE
} sensor_msg_e;

/**
 * Sensor task message queue structure
 */
typedef struct
{
  sensor_msg_e msg_id;
  uint16_t sampling_interval;
} sensors_msg_t;

/**
 * Enqueues a message for the Sensor Task
 * @param msg_id : Message ID from the sensors_msg_e enum indicating the type of update.
 * @param sampling_interval: The sampling interval of the sensor task.
 * @return ERR_OK if the message was succsessfully sent to the queue, otherwise ERR_FAIL.
 *         ERR FAIL indicates that the queue is full, and the message cannot be enqueued at this time.
 */
error_t sensor_task_send_msg(sensor_msg_e msg_id, uint16_t sampling_interval);

/**
 * Starts the Sensor Task
 */
void sensors_task_start(void);

#endif /* INC_SENSOR_TASK_H_ */
