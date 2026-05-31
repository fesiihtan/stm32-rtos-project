/**
 * @outhor    : Fesih TAN
 * @date      : May 26, 2026
 * @brief     : RTOS Project Main File
 * @details   : This file contains the main function which serves as the entry point for the rtos project
 */

#include <stdint.h>
#include "rcc.h"
#include "mcu.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOSTasks.h"


// Startup Task Prototype
static void startup(void);

// Run Time stats configuration prototype
void configureRunTime(void);

// Run Time stats get counter value prototype
uint32_t getRunTimeCounter(void);


int main(void)
{
  // Initial RCC configurations and clock frequency tests
  uint32_t system_clock = 0;
  uint32_t hclk         = 0;
  uint32_t apb1_clock   = 0;
  uint32_t apb2_clock   = 0;

  rcc_init();

  system_clock = rcc_get_sysclk_freq();
  hclk         = rcc_get_hclk_freq();
  apb1_clock   = rcc_get_pclk1_freq();
  apb2_clock   = rcc_get_pclk2_freq();

  (void)system_clock;
  (void)hclk;
  (void)apb1_clock;
  (void)apb2_clock;

  // Update the SystemCoreClock variable required by FreeRTOSConfig.h
  SystemCoreClockUpdate();

  // Create the startup task
  startup();

  // Start the FreeRTOS scheduler
  vTaskStartScheduler();

  
	while(1)
	{

	}
}

/**
 * @brief  Startup task used for the required FreeRTOS initializations on startup
 */
static void startup_task(void *param)
{
    // Delete the startup task
    vTaskDelete(NULL);
}

/**
 *  Creates the startup task.
 */
static void startup(void)
{
  configASSERT(pdPASS == xTaskCreate(startup_task, "Startup Task", STARTUP_TASK_STACK_SIZE, NULL, STARTUP_TASK_PRIORITY, NULL));
}


// Run Time stats configuration prototype
void configureRunTime(void)
{

}


// Run Time stats get counter value prototype
uint32_t getRunTimeCounter(void)
{
  return 1;
}
