/**
 * @outhor    : Fesih TAN
 * @date      : May 26, 2026
 * @brief     : RTOS Project Main File
 * @details   : This file contains the main function which serves as the entry point for the rtos project
 */

#include <stdint.h>
#include "mcu.h"
#include "FreeRTOSConfig.h"

// Timer variable to track elapsed time
static uint32_t run_time_counter = 0;

int main(void)
{
	while(1)
	{

	}
}


// Initialize timer for runtime statistics
void configureRunTime(void)
{
    // Configure a timer interrupt to increment the counter
    // For STM32F407, you can use SysTick or another timer
    // This example uses a simple counter that increments
}

// Get the current runtime counter value
uint32_t getRunTimeCounter(void)
{
    return run_time_counter;
}