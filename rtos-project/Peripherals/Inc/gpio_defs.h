/*
 * gpio_defs.h
 * @author    : Fesih TAN
 * @date      : May 31, 2026
 * @brief     : Defines GPIO ports and pins for all hardware components used in the system
 *
 */

#ifndef INC_GPIO_DEFS_H_
#define INC_GPIO_DEFS_H_

#include "mcu.h"
#include "gpio.h"

// User interface
#define USER_LED_PORT       GPIOD
#define USER_LED_PIN        GPIO_PIN_13

#define USER_BUTTON_PORT    GPIOA
#define USER_BUTTON_PIN     GPIO_PIN_0

// Sensirion sensors
#define SENSIRION_SCL_PORT  GPIOB
#define SENSIRION_SCL_PIN   GPIO_PIN_8
#define SENSIRION_SDA_PORT  GPIOB
#define SENSIRION_SDA_PIN   GPIO_PIN_9


#endif /* INC_GPIO_DEFS_H_ */
