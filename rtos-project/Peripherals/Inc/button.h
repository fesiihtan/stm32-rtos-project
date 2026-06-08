/*
 * button.h
 *
 *  Created on: Jun 8, 2026
 *      Author: Fesih TAN
 *      @brief: Interface for initializing and managing the User button for IWDG acknowledgement.
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>

/**
 * Time interval in milliseconds for LED blinking while waiting for button acknowledgement
 */
#define BUTTON_ACK_BLINK_INTERVAL     ((uint32_t)100)


/**
 * Sets up the semaphore and configures external interrupts for the user button
 */
void button_init(void);

/**
 * Handles an Independent Watchdog Event (IWDG) reset event
 * It checks for event, requires user acknowledgement through button press, and clear the IWDG flags
 */
void button_check_and_acknowledge_iwdg_event(void);



#endif /* INC_BUTTON_H_ */
