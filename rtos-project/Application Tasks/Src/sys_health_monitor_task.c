/*
 * sys_health_monitor_task.c
 *
 *  Created on: Jun 3, 2026
 *      Author: Fesih TAN
 *  @brief: Implements the System Health Monitor Task, responisble for:
 *          1: Monitoring the MCU's internal temperature and notifying the Error Handler if thresholds are exceeded
 *          2: Regularly checking the status of critical tasks and resetting the watchdog timer if they are operational
 */

#include "sys_health_monitor_task.h"
#include "error_handler_task.h"
#include "gpio.h"
// To do: include adc.h/ iwdg.h/ tim.h

// Global health flags
volatile bool g_sensors_task_ok = false;
// ... Add more flags for other critical tasks if needed

// MCU temperature health flag
static volatile bool mcu_temp_ok = true;

// Optional: flag & variable used for demonstating obtaining the updated MCU temperature
static volatile uint8_t ADC1_CONVERSION_COMPLETE = 0;
static volatile uint16_t adc_temp_val = 0;

// Todo: define temp_to_adc() conversion function
// Todo: define get_temp() function

/**
 * System Health Monitor Task which monitors the MCU temperature and,
 * if critical tasks are operational, periodically kicks the Independent Watchdog
 */
static void sys_health_monitor_task(void *param)
{
  float internal_temp;

  // Todo: Convert the temperature high/low threshold to ADC values using temp_to_adc()

  // Todo: Initialize the analog watchdog based on the thresholds using adc_awd_init()

  // Initialize the IWDG here if not in debug mode
  if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 0)
  {
    // Debugger not connected, safe to enable IWDG
    // Todo: call iwdg_init()
  }

  // Variable used to check the system health
  bool system_healthy;

  // Specify the frequency of task execution and,
  // Initialize the xLastWakeTime variable with the current time
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1)
  {
    // Wait for the next cycle
    xTaskDelayUntil(&xLastWakeTime, xFrequency);

    // Optional: Get the temperature for demonstaration purposes
    if(ADC1_CONVERSION_COMPLETE)
    {
      // Todo update 'internal_temp' using 'get_temperature(adc_temp_val)
    }
  }

}
