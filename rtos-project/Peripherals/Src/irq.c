/*
 * irq.c
 *
 *  Created on: Jun 6, 2026
 *      Author: Fesih TAN
 *      @brief: Configures IRQ priority levels for the system by setting priority levels in the
 *      NVIC (Nested Vector Interrupt Controller) for specific interrupts
 */

#include "irq.h"

void irq_set_priorities(void)
{
  // Internal temperature sensor
  NVIC_SetPriority(ADC_IRQn, IRQ_ADC_PRIORITY);

  // Button EXTI
  NVIC_SetPriority(EXTI0_IRQn, IRQ_EXTI0_PRIORITY);
}

