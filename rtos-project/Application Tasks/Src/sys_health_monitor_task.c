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
#include "adc.h"
#include "tim.h"
#include  "iwdg.h"

// Global health flags
volatile bool g_sensors_task_ok = false;
// ... Add more flags for other critical tasks if needed

// MCU temperature health flag
static volatile bool mcu_temp_ok = true;

// Optional: flag & variable used for demonstating obtaining the updated MCU temperature
static volatile uint8_t ADC1_CONVERSION_COMPLETE = 0;
static volatile uint16_t adc_temp_val = 0;

/**
 * Converts a temperature value in Celsius to the corresponding ADC Value
 * Currently used to set the analog watchdog thresholds
 * @param temp_celsius: Temperature in Celsius to be converted to ADC Value
 * @return The equivalent ADC value for the given temperature
 */
static uint16_t temperature_to_adc(float temp_celsius)
{
  // Constants as per the STM32 datasheet page 139 for the internal temperature sensor
  const float TEMP_SENSOR_AVG_SLOPE = 0.0025;
  const float TEMP_SENSOR_V25 = 0.76;
  const float VREF = 3.3;

  // Calculate the sensor voltage for the given temperature. This formula comes from Referance Manual
  float voltage = ((temp_celsius - 25.0) * TEMP_SENSOR_AVG_SLOPE) + TEMP_SENSOR_V25;

  // Convert the voltage to an ADC Value
  uint16_t adc_value = (voltage / VREF) * 4095.0;

  return adc_value;
}

/**
 * Computes the temperature based on sensor voltage
 * @param adc_val: ADC Value from the temperature sensor
 * @return the computed temperature to Celsius
 */
static float adc_to_temperature(uint16_t adc_val)
{
  // Constants as per the STM32 datasheet page 139 for the internal temperature sensor
  const float TEMP_SENSOR_AVG_SLOPE = 0.0025;
  const float TEMP_SENSOR_V25 = 0.76;
  const float VREF = 3.3;

  // Convert ADC value to voltage
  float voltage = (adc_val * VREF ) / 4095.0;

  // Convert the voltage to temperature
  float temp = ((voltage - TEMP_SENSOR_V25) / TEMP_SENSOR_AVG_SLOPE) + 25.0;

  return temp;
}

/**
 * System Health Monitor Task which monitors the MCU temperature and,
 * if critical tasks are operational, periodically kicks the Independent Watchdog
 */
static void sys_health_monitor_task(void *param)
{
  float internal_temp;

  // Convert the temperature high/low threshold to ADC values
  uint16_t awd_htr = temperature_to_adc(ADC1_AWD_HT_TEMP_CELSIUS);
  uint16_t awd_ltr = temperature_to_adc(ADC1_AWD_LT_TEMP_CELSIUS);

  // Initialize the analog watchdog based on the thresholds
  adc_awd_init(ADC1, ADC_CH16, awd_htr, awd_ltr);


  // Initialize the IWDG here if not in debug mode
  if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 0)
  {
    // Debugger not connected, safe to enable IWDG
    iwdg_init();
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
      // Update 'internal_temp' using 'adc_to_temperature(adc_temp_val)
      internal_temp = adc_to_temperature(adc_temp_val);
      ADC1_CONVERSION_COMPLETE = 0;
    }

    // Check if all critical tasks are running correctly
    system_healthy = g_sensors_task_ok && mcu_temp_ok; 

    if(system_healthy)
    {
      // If the system is healthy, reset the watchdog timer
      iwdg_reset();
      g_sensors_task_ok = false;
    }
    else
    {
      // If the system is not healthy, notify the Error Handler Task
    }

    // Get rid of unused variable warning
    (void)internal_temp;
  }
}

void sys_health_monitor_task_start(void)
{
  // Setup for getting MCU Temperature (TIM2 and ADC1)

  tim2_init();

  adc_init();

  configASSERT( xTaskCreate(sys_health_monitor_task, 
                            "System Health Monitor Task", 
                            SYS_HEALTH_MONITOR_TASK_STACK_SIZE, 
                            NULL, 
                            SYS_HEALTH_MONITOR_TASK_PRIORITY, 
                            NULL) == pdPASS );
}

/**
 * ISR for ADC interrupts
 * Handles Analog Watchdog alerts, EOC flag setting, and overrun flag clearing
 */
void ADC_IRQHandler(void)
{
  // Check if the Analog Watchdog flag is set
  if(ADC1->SR & ADC_SR_AWD)
  {
    // Clear the Analog Watchdog flag
    ADC1->SR &= ~ADC_SR_AWD;

    // Alert the Error Handler due to the AWD event
    error_handler_send_msg_from_isr(EVT_SYS_HEALTH_AWDG_THRESHOLD_EXCEEDED);

    // Set the temperature health flag to false
    mcu_temp_ok = false;
  }

  // check if the End of Conversion flag is set
  if(ADC1->SR & ADC_SR_EOC)
  {
    gpio_toggle_pin(USER_LED_PORT, USER_LED_PIN); 
    
    // Read the converted value
    adc_temp_val = ADC1->DR;

    // Set the conversion complete flag
    ADC1_CONVERSION_COMPLETE = 1;

    // Clear the EOC flag
    ADC1->SR &= ~ADC_SR_EOC;
  }

  // Check if the overrun flag is set using the OVR bit in the status register
  if(ADC1->SR & ADC_SR_OVR)
  {
    // Clear the overrun flag
    ADC1->SR &= ~ADC_SR_OVR; 
  }
}

