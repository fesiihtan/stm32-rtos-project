/*
 * irq.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Fesih TAN
 *      @brief: Contains IRQ priority definitons and initialization function prototype
 */

#ifndef INC_IRQ_H_
#define INC_IRQ_H_

#include "mcu.h"
#include "FreeRTOSConfig.h"

// ADC İnterrupt priortiy, criticcal for temperature sensing
#define IRQ_ADC_PRIORITY    ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 0))

// External interrupt priority for the user button
#define IRQ_EXTI0_PRIORITY  ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 0))

// I2C event and timer interrupt priorities for Sensirion Sensor Operations
#define IRQ_I2C1_EV_PRIORITY  ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1))
#define IRQ_TIM5_PRIORITY     ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2))

/**
 * Configures the priority levels for various IRQ in the system by setting the
 * Priority levels in the NVIC (Nested Vector Interrupt Controller) for specific interrupts
 */
void irq_set_priorities(void);

#endif /* INC_IRQ_H_ */
